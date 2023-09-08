/*
* ByteStream.cpp by Solar *
* https://github.com/Solaree *
*/

#pragma once
#include <vector>
#include <string>
#include <iomanip>
#include <iostream>
#include <Windows.h>
#include <WinSock2.h>
#include "../include/Core/Crypto.hpp"
#include "../include/Stream/ByteStream.hpp"

using namespace std;

vector<char> buffer;

void ByteStream::writeUInt8(uint8_t val) {
	unsigned char byte = (unsigned char)val;
	buffer.push_back(byte);
}

int ByteStream::readUInt8() {
	uint8_t byte = buffer[0];

	buffer.erase(buffer.begin());
	return byte;
}

void ByteStream::writeBool(bool val) {
	if (val == true) {
		writeUInt8(1);
	} else {
		writeUInt8(0);
	}
}

bool ByteStream::readBool() {
	if (readUInt8() == 1) {
		return true;
	} else {
		return false;
	}
}

void ByteStream::writeShort(short val) {
	for (size_t i = 1; i => 0; i--) {
		short byte = (val >> (i * 8)) & 0xFF;
		buffer.push_back(byte);
	}
}

short ByteStream::readShort() {
	short byte = 0;

	for (size_t i = 0; i <= 1; i++) {
		byte |= (buffer[0] << (8 * (1 - i)));
		buffer.erase(buffer.begin());
	}
	return byte;
}

void ByteStream::writeInt(int val) {
	for (size_t i = 3; i => 0; i--) {
		int byte = (val >> (i * 8)) & 0xFF;
		buffer.push_back(byte);
	}
}

int ByteStream::readInt() {
	int byte = 0;

	for (size_t i = 0; i <= 3; i++) {
		byte |= (buffer[0] << (8 * (3 - i)));
		buffer.erase(buffer.begin());
	}
	return byte;
}

void ByteStream::writeIntLittleEndian(int val) {
	for (size_t i = 0; i <= 3; i++) {
		int byte = (val >> (i * 8)) & 0xFF;
		buffer.push_back(byte);
	}
}

int ByteStream::readIntLittleEndian() {
	int byte = 0;

	for (size_t i = 0; i <= 3; i++) {
		byte |= (buffer[0] << (8 * i));
		buffer.erase(buffer.begin());
	}
	return byte;
}

void ByteStream::writeLong(int highByte, int lowByte) {
	writeInt(highByte);
	writeInt(lowByte);
}

long ByteStream::readLong() {
	readInt();
	readInt();
}

void ByteStream::writeVInt(int val) {
	bool rotation = true;

	if (val == 0) {
		writeInt(1);
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

int ByteStream::readVInt() {
	int result = 0;
	int shift = 0;
	int rotation, msb, seven_bit;

	while (true) {
		int byte = readInt(1);

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

void ByteStream::writeArrayVInt(int val) {
	for (size_t x : val) {
		writeInt(x);
	}
}

void ByteStream::writeLogicLong(int highByte, int lowByte) {
	writeVInt(highByte);
	writeVInt(lowByte);
}

long ByteStream::readLogicLong() {
	readVInt();
	readVInt();
}

void ByteStream::writeBytes(string val) {
	if (val.empty()) {
		writeInt(-1);
	} else {
		buffer.insert(buffer.end(), val, val + strlen(val));
	}
}

void ByteStream::writeString(string s) {
	if (s.empty()) {
		writeInt(-1);
	} else {
		writeInt((int)s.length());
		writeBytes(s.data());
	}
}

string ByteStream::readString() {
	int len = readInt();

	if (len == -1 || len == 65535) {
		return "";
	}
	string s(buffer.begin(), buffer.begin() + len);
	buffer.erase(buffer.begin(), buffer.begin() + len);
	return s;
}

void ByteStream::writeStringRef(string s) {
	if (s.empty()) {
		writeInt(-1);
	} else {
		writeLong(2, 0);
		writeVInt(s.length());
		writeBytes(s.data());
	}
}

void ByteStream::writeHex(string hexa) {
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

vector<uint8_t> hexStringToBytes(const string& hexString) {
	vector<uint8_t> binaryData;

	for (size_t i = 0; i < hexString.length(); i += 2) {
		string byteString = hexString.substr(i, 2);

		uint8_t byte = static_cast<uint8_t>(stoul(byteString, nullptr, 16));
		binaryData.push_back(byte);
	}
	return binaryData;
}

void ByteStream::packetWrite(int id, int sock, int version = 0) {
    vector<char> packet;
    vector<char> finalPacket;

    vector<char> packetId(2);
    vector<char> packetLen(3);
    vector<char> packetVer(2);

    packet.resize(buffer.size());
	memcpy(packet.data(), buffer.data(), buffer.size());

	buffer.clear();

	string dataStr(packet.begin(), packet.end());
	vector<char> encrypted = RC4Encrypt(dataStr.begin(), dataStr.end());

    packetId[0] = ((char)(id >> 8) & 0xFF);
    packetId[1] = ((char)id & 0xFF);

    packetLen[0] = ((char)(encrypted.size() >> 16) & 0xFF);
    packetLen[1] = ((char)(encrypted.size() >> 8) & 0xFF);
    packetLen[2] = ((char)encrypted.size() & 0xFF);

    packetVer[0] = ((char)(version >> 8) & 0xFF);
    packetVer[1] = ((char)version & 0xFF);

    finalPacket.insert(finalPacket.end(), packetId.begin(), packetId.end());
    finalPacket.insert(finalPacket.end(), packetLen.begin(), packetLen.end());
    finalPacket.insert(finalPacket.end(), packetVer.begin(), packetVer.end());
    finalPacket.insert(finalPacket.end(), encrypted.begin(), encrypted.end());

    cout << "[*] Sent packet with Id: " << id << " || Length: " << finalPacket.size() << " || Version: " << version << " || Content: ";

    cout << "b'";
    for (size_t i = 0; i < finalPacket.size(); ++i) {
        cout << "\\x" << uppercase << hex << setw(2) << setfill('0') << ((int)finalPacket[i] & 0xFF);
    }
    cout << "'" << dec << endl << endl;

	finalPacket.clear();
}
