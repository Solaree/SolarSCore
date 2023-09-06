#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <sys/socket.h>
#include "Core/Crypto.cpp"

using namespace std;

class ByteStream {
public:
	void writeUInt8(const uint8_t val) {
		buffer.push_back((unsigned char)val);
	}

	int readUInt8() {
		uint8_t byte = buffer[0];

		buffer.erase(buffer.begin());
		return byte;
	}

	void writeBool(const bool val) {
		if (val == true) {
			writeUInt8(1);
		}
		else {
			writeUInt8(0);
		}
	}

	bool readBool() {
		if (readUInt8() == 1) {
			return true;
		}
		else {
			return false;
		}
	}

	void writeShort(const short val) {
		for (int i = 1; i >= 0; i--) {
			short byte = (val >> (i * 8)) & 0xFF;
			buffer.push_back(byte);
		}
	}

	short readShort() {
		short byte = 0;

		for (int i = 0; i < 2; i++) {
			byte |= (buffer[0] << (8 * (1 - i)));
			buffer.erase(buffer.begin());
		}

		return byte;
	}

	void writeInt(const int val) {
		for (int i = 3; i >= 0; i--) {
			int byte = (val >> (i * 8)) & 0xFF;
			buffer.push_back(byte);
		}
	}

	int readInt() {
		int byte = 0;

		for (int i = 0; i < 4; i++) {
			byte |= (buffer[0] << (8 * (3 - i)));
			buffer.erase(buffer.begin());
		}
		return byte;
	}

	void writeLong(const int highByte, const int lowByte) {
		writeInt(highByte);
		writeInt(lowByte);
	}

	long readLong() {
		readInt();
		readInt();
	}

	void writeVInt(const int val) {
		bool rotation = true;

		if (val == 0) {
			writeLong(1, 0);
			return;
		}

		val = (val << 1) ^ (val >> 31);

		while (val) {
			int tmp = i & 0x7f;

			if (val >= 0x80) {
				tmp |= 0x80;
			} if (rotation == true) {
				rotation = false;

				int l = tmp & 0x1;
				int byte = (tmp & 0x80) >> 7;

				tmp >>= 1;
				tmp = tmp & ~0xC0;
				tmp = tmp | (byte << 7) | (l << 6);
			}
			buffer.push_back(tmp & 0xFF); val >>= 7;
		}
	}

	int readVInt() {
		int result = 0;
		int shift = 0;
		int rotation, msb, seven_bit;

		while (true) {
			int byte = read(1);

			if (shift == 0) {
				seven_bit = (byte & 0x40) >> 6;
				msb = (byte & 0x80) >> 7;
				rotation = byte << 1;
				rotation = rotation & ~0x181;
				byte = rotation | (msb << 7) | seven_bit;
			}

			result |= (byte & 0x7f) << shift;
			shift += 7;

			if (!(byte & 0x80)) {
				break;
			}
		}
		result = (result >> 1) ^ (-(result & 1));
		return result;
	}

	void writeArrayVInt(const int val) {
		for (int x : val) {
			writeInt(x);
		}
	}

	void writeLogicLong(const int highByte, const int lowByte) {
		writeVInt(highByte);
		writeVInt(lowByte);
	}

	long readLogicLong() {
		readVInt();
		readVInt();
	}

	void writeBytes(const char* val) {
		buffer.insert(buffer.end(), val, val + strlen(val));
	}

	void writeString(const string& s) {
		if (s.empty()) {
			writeInt(-1);
		}
		else {
			writeInt(static_cast<int>(s.length()));
			writeBytes(s.data());
		}
	}

	string readString() {
		string s;
		int len = readInt();

		if (len == -1 || len == 65535) {
			return "";
		}
		string s(buffer.begin(), buffer.begin() + len);
		buffer.erase(buffer.begin(), buffer.begin() + len);
		return s;
	}

	void writeStringRef(const string& s) {
		if (s.empty()) {
			writeInt(-1);
		}
		else {
			writeLong(2, 0);
			writeVInt(s.length());
			writeBytes(s.data());
		}
	}

	void writeHexa(const string& hexa) {
		if (!hexa.empty()) {
			string hexString = hexa;

			if (hexString.substr(0, 2) == "0x") {
				hexString = hexString.substr(2);
			}

			hexString.erase(remove(hexString.begin(), hexString.end(), '-'), hexString.end());
			vector<uint8_t> binaryData = hexStringToBytes(hexString);

			buffer.insert(buffer.end(), binaryData.begin(), binaryData.end());
		}
	}

	void send(int id, int sock) {
		Crypto RC4;
		string dataStr(buffer.begin(), buffer.end());
		char* encrypted = RC4.encrypt((dataStr));
		int version = 0;

		buffer.clear();

		writeLong(2, id);
		writeLong(3, strlen(encrypted));
		writeLong(2, version);

		buffer.insert(buffer.end(), encrypted, strlen(encrypted));

		writeLong(2, 65535);
		writeLong(4, 0);
		writeLong(1, 0);

		send(sock, encrypted, strlen(encrypted), 0);

		cout << "[*] Sent packet with Id: " << id << " || Length: " << dataStr << " || Version: " << version << endl;
	}

private:
	vector<char> buffer;

	vector<uint8_t> hexStringToBytes(const string& hexString) {
		vector<uint8_t> binaryData;

		for (size_t i = 0; i < hexString.length(); i += 2) {
			string byteString = hexString.substr(i, 2);

			uint8_t byte = static_cast<uint8_t>(stoul(byteString, nullptr, 16));
			binaryData.push_back(byte);
		}
		return binaryData;
	}
};