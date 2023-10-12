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
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*/

#include "include/Stream/ByteStream.hpp"

vector<uint8_t> ByteStream::buffer;
vector<uint8_t> ByteStream::headBuf;

void ByteStream::setBuffer(vector<uint8_t>& buf) {
    buffer = buf;
}

void ByteStream::writeUInt8(uint8_t val) {
	buffer.push_back(val);
}

uint8_t ByteStream::readUInt8() {
	return readInteger<uint8_t>(1);
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
    writeData<int16_t>(val);
}

int16_t ByteStream::readShort() {
    return readInteger<int16_t>(2);
}

void ByteStream::writeInt(int32_t val) {
    writeData<int32_t>(val);
}

int32_t ByteStream::readInt() {
	return readInteger<int32_t>(4);
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
		buffer.push_back(tmp & 255);
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

void ByteStream::writeLogicLong(int32_t hiByte, int32_t loByte) {
	writeVInt(hiByte);
	writeVInt(loByte);
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

void ByteStream::writeString(const string& s) {
    writeData<int32_t>(s.size());
    buffer.insert(buffer.end(), s.begin(), s.end());
}

string ByteStream::readString() {
	int32_t len = readInt();

	if (len == -1 || len == 65535) {
		return "";
	}
	string s(buffer.begin(), buffer.begin() + len);
	buffer.erase(buffer.begin(), buffer.begin() + len);
	return s;
}

void ByteStream::writeStringRef(const string& s) {
	if (s.empty()) {
		writeInt(-1);
	} else {
		writeLong(2, 0);
		writeVInt(s.length());
		writeBytes(s.data());
	}
}

void ByteStream::writeHex(const string& hexa) {
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

vector<uint8_t> ByteStream::hexStringToBytes(const string& hexStr) {
	vector<uint8_t> binData;

	for (size_t i = 0; i < hexStr.length(); i += 2) {
		string byteStr = hexStr.substr(i, 2);

		uint8_t byte = (uint8_t)(stoul(byteStr, nullptr, 16));
		binData.push_back(byte);
	}
	return binData;
}

template<typename Temp>
Temp ByteStream::readInteger(size_t length) {
    if (length > buffer.size()) {
        throw underflow_error("[*] Insufficient data in buffer to read integer");
    }

    Temp result = 0;

    for (size_t i = 0; i < length; ++i) {
        result = (result << 8) | buffer[i];
    }
    buffer.erase(buffer.begin(), buffer.begin() + length);
    return result;
}

template<typename Temp>
void ByteStream::writeData(const Temp& data) {
    static_assert(is_trivially_copyable<Temp>::value, "[*] Data must be trivially copyable");

    const byte* bytes = (const byte*)(&data);
    size_t dataSize = sizeof(Temp);

    for (size_t i = 0; i < dataSize; ++i) {
        buffer.push_back((uint8_t)(bytes[i]));
    }
}

void ByteStream::writePacket(const uint16_t id, int32_t sock, uint16_t ver /* = 0 */) {
    // RC4__encrypt(buffer.data());

    // Prepare the header
    headBuf.push_back((uint8_t)((id >> 8) & 255)); 				// Header ID (bits 8-15)
    headBuf.push_back((uint8_t)(id & 255)); 						// Header ID (bits 0-7)

    headBuf.push_back((uint8_t)((buffer.size() >> 16) & 255)); 	// Packet Length (bits 16-23)
    headBuf.push_back((uint8_t)((buffer.size() >> 8) & 255)); 	// Packet Length (bits 8-15)
    headBuf.push_back((uint8_t)(buffer.size() & 255)); 			// Packet Length (bits 0-7)

    if (ver != 0 && ver > 0) {
        headBuf.push_back((uint8_t)((ver >> 8) & 255)); 			// Header Version (bits 8-15)
        headBuf.push_back((uint8_t)(ver & 255)); 				// Header Version (bits 0-7)
    }
    headBuf.push_back((uint8_t)((0 >> 8) & 255)); 				// Header Version (bits 8-15)
    headBuf.push_back((uint8_t)(0 & 255)); 						// Header Version (bits 0-7)

    // Combine the header and encrypted data
    vector<uint8_t> packetBuf;
    packetBuf.insert(packetBuf.end(), headBuf.begin(), headBuf.end());
    packetBuf.insert(packetBuf.end(), buffer.begin(), buffer.end());

	// Clean up
	headBuf.clear();
	buffer.clear();

    // Sending the packet over the socket
    send(sock, packetBuf.data(), packetBuf.size(), 0);

    // Logging the sent packet
    cout << "[*] Sent packet with Id: " << id << " || Length: " << packetBuf.size()
        << " || Version: " << ver << " || Content: ";

    // Print packet content in hexadecimal format
    for (size_t i = 0; i < packetBuf.size(); ++i) {
        cout << uppercase << hex << setw(2) << setfill('0') << ((size_t)packetBuf[i] & 255);
    }
    cout << dec << endl << endl;

	// Clean up
	packetBuf.clear();
}
ByteStream Stream;