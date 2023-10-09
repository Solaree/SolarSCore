/*
* ByteStream.cpp - The SolarSCore
* Copyright (C) 2023 Solar
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*/

#include "include/Stream/ByteStream.hpp"

void ByteStream::writeUInt8(uint8_t val) {
	buffer.push_back(val);
}

uint8_t ByteStream::readUInt8() {
	uint8_t byte = buffer[0];

	buffer.erase(buffer.begin());
	return byte;
}

void ByteStream::writeBool(bool val) {
	int32_t bitPosition = buffer.size() % 8;

	if (bitPosition == 0) {
		buffer.push_back(0);
	} if (val) {
		buffer.back() |= (1 << bitPosition);
	}
}

bool ByteStream::readBool() {
	if (readUInt8() == 1) {
		return true;
	} else {
		return false;
	}
}

void ByteStream::writeShort(int16_t val) {
	for (int16_t i = 1; i >= 0; i--) {
		int16_t byte = (val >> (i * 8)) & 0xFF;
		buffer.push_back(byte);
	}
}

int16_t ByteStream::readShort() {
	int16_t byte = 0;

	for (int16_t i = 0; i <= 1; i++) {
		byte |= (buffer[0] << (8 * (1 - i)));
		buffer.erase(buffer.begin());
	}
	return byte;
}

int16_t ByteStream::readLen() {
	int16_t byte = 0;

	for (int16_t i = 0; i <= 2; i++) {
		byte |= (buffer[0] << (8 * (2 - i)));
		buffer.erase(buffer.begin());
	}
	return byte;
}

void ByteStream::writeInt(int32_t val) {
	for (int32_t i = 3; i >= 0; i--) {
		int32_t byte = (val >> (i * 8)) & 0xFF;
		buffer.push_back(byte);
	}
}

int32_t ByteStream::readInt() {
	int32_t byte = 0;

	for (int32_t i = 0; i <= 3; i++) {
		byte |= (buffer[0] << (8 * (3 - i)));
		buffer.erase(buffer.begin());
	}
	return byte;
}

void ByteStream::writeIntLittleEndian(int32_t val) {
	for (int32_t i = 0; i <= 3; i++) {
		int32_t byte = (val >> (i * 8)) & 0xFF;
		buffer.push_back(byte);
	}
}

int32_t ByteStream::readIntLittleEndian() {
	int32_t byte = 0;

	for (int32_t i = 0; i <= 3; i++) {
		byte |= (buffer[0] << (8 * i));
		buffer.erase(buffer.begin());
	}
	return byte;
}

void ByteStream::writeLong(int32_t highByte, int32_t lowByte) {
	writeInt(highByte);
	writeInt(lowByte);
}

pair<int32_t, int32_t> ByteStream::readLong() {
    int32_t hiWord = readInt();
    int32_t loWord = readInt();
    return make_pair(hiWord, loWord);
}

void ByteStream::writeVInt(int32_t val) {
	bool rotation = true;

	if (val == 0) {
		writeInt(1);
		return;
	}

	val = (val << 1) ^ (val >> 31);

	while (val) {
		int32_t tmp = val & 0x7F;

		if (val >= 0x80) {
			tmp |= 0x80;
		} if (rotation == true) {
			rotation = false;

			int32_t l = tmp & 0x1;
			int32_t byte = (tmp & 0x80) >> 7;

			tmp >>= 1;
			tmp = tmp & ~0xC0;
			tmp = tmp | (byte << 7) | (l << 6);
		}
		buffer.push_back(tmp & 0xFF);
		val >>= 7;
	}
}

int32_t ByteStream::readVInt() {
	int32_t result = 0;
	int32_t shift = 0;
	int32_t rotation, msb, seven_bit;

	while (true) {
		int32_t byte = readInt();

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

void ByteStream::writeArrayVInt(int32_t* val, int32_t count) {
    for (int32_t i = 0; i < count; ++i) {
        writeVInt(val[i]);
    }
}

void ByteStream::writeLogicLong(int32_t highByte, int32_t lowByte) {
	writeVInt(highByte);
	writeVInt(lowByte);
}

pair<int32_t, int32_t> ByteStream::readLogicLong() {
    int32_t hiWord = readVInt();
    int32_t loWord = readVInt();
    return make_pair(hiWord, loWord);
}

void ByteStream::writeBytes(const string& val) {
    if (val.empty()) {
        writeInt(-1);
    } else {
        for (uint8_t c : val) {
            writeUInt8(c);
        }
    }
}

void ByteStream::writeString(string s) {
	if (s.empty()) {
		writeInt(-1);
	} else {
		writeInt((int32_t)s.length());
		writeBytes(s.data());
	}
}

string ByteStream::readString() {
	int32_t len = readInt();

	if (len == -1 || len == 65535) {
		return "";
	}
	string str(buffer.begin(), buffer.begin() + len);
	buffer.erase(buffer.begin(), buffer.begin() + len);
	return str;
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

vector<uint8_t> ByteStream::hexStringToBytes(const string& hexString) {
	vector<uint8_t> binaryData;

	for (size_t i = 0; i < hexString.length(); i += 2) {
		string byteString = hexString.substr(i, 2);

		uint8_t byte = (uint8_t)(stoul(byteString, nullptr, 16));
		binaryData.push_back(byte);
	}
	return binaryData;
}

void ByteStream::writePacket(int32_t id, int32_t sock, int32_t version /* = 0 */) {
	vector<char> packet;
	char header[7];

	packet.resize(buffer.size());
	memcpy(packet.data(), buffer.data(), 7); // Copy buffer to new var so we can clear it
	buffer.clear();

	string data(packet.begin(), packet.end());
	string encrypted = Crypto::encrypt(data);

	for (int32_t i = 0; i < 2; i++) {
		header[i] = (char)((id >> (8 * (1 - i))) & 0xFF);
	} // Short id

	for (int32_t i = 2; i < 5; i++) {
		header[i] = (char)((encrypted.size() >> (8 * (4 - i))) & 0xFF);
	} // 3-bytes length

	if (version != 0) {
		for (int32_t i = 5; i < 7; i++) {
			header[i] = (char)((version >> (8 * (3 - i))) & 0xFF);
		} // Short version
	}

	string finalHeader(header, 7);
	string finalPacket = finalHeader + encrypted;

	send(sock, finalPacket.c_str(), finalPacket.size(), 0);

	cout << "[*] Sent packet with Id: " << id << " || Length: " << finalPacket.size() << " || Version: " << version << " || Content: " << "b\"";

	for (size_t i = 0; i < finalPacket.size(); ++i) {
		cout << "\\x" << uppercase << hex << setw(2) << setfill('0') << ((size_t)finalPacket[i] & 0xFF);
	}
	cout << "\"" << dec << endl << endl;
}

ByteStream Stream;