/*
* ByteStream.hpp - The SolarSCore
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

#ifndef BYTESTREAM_HPP
#define BYTESTREAM_HPP

#ifdef __unix__
    #include <unistd.h>
    #include <arpa/inet.h>
	#include <sys/socket.h>
#elif defined(_WIN32)
    #include <winsock2.h>
#endif

#include <vector>
#include <cstring>
#include <cstdint>
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <algorithm>
#include <stdexcept>

#include "include/Core/Crypto.h"

using namespace std;

/* ByteStream Class */
class ByteStream {
public:
	/* Main buffer */
	static vector<uint8_t> buffer;
	/* Header buffer */
	static vector<uint8_t> headBuf;

	/* Sets argument vector to the stream buffer */
	static void setBuffer(vector<uint8_t>& buf);

	/* Writes 1-byte 'uint8' in range from 0 to 255 via 'unsigned char' */
	void writeUInt8(uint8_t val);
	/* Reads 1-byte 'uint8' */
	uint8_t readUInt8();

	/* Writes 1-byte 'bool' with 'uint8' (uses 0 for 'false', 1 for 'true') */
	void writeBool(bool val);
	/* Reads 1-byte 'bool' using 'uint8' */
	bool readBool();

	/* Writes 2-bytes 'short' */
	void writeShort(int16_t val);
	/* Reads 2-bytes 'short' */
	int16_t readShort();

	/* Writes 4-bytes 'int' */
	void writeInt(int32_t val);
	/* Reads 4-bytes 'int' */
	int32_t readInt();

	/* Writes 8-bytes 'long' using 2-times 'int' writing */
	void writeLong(int32_t hiByte, int32_t loByte);
	/* Reads 8-bytes 'long' using 2-times 'int' reading */
	pair<int32_t, int32_t> readLong();

	/* Writes 7-bits 'vint' (VariableInteger) */
	void writeVInt(int32_t val);
	/* Reads 7-bits 'vint' (VariableInteger) */
	int32_t readVInt();

	/* Writes array of 'vint' (VariableInteger) */
	void writeArrayVInt(int32_t* val, int32_t count);

	/* Writes 14-bits 'long' using 2-times 'vint' writing */
	void writeLogicLong(int32_t hiByte, int32_t loByte);
	/* Reads 14-bits 'long' using 2-times 'vint' writing */
	pair<int32_t, int32_t> readLogicLong();

	/* Writes bytes with 'string' type */
	void writeBytes(const string& val = "");

	/* Writes 'string' */
	void writeString(const string& s = "");
	/* Reads 'string' */
	string readString();

	/* Writes 'stringref' (StringReferance) */
	void writeStringRef(const string& s = "");

	/* Writes raw hex data */
	void writeHex(const string& hexa = "");

	/* Util used for 'writeHex()' function */
	vector<uint8_t> hexStringToBytes(const string& hexStr);

	/* Writes encrypted packet to the buffer and sends it */
	void writePacket(const uint16_t id, int32_t sock, uint16_t ver = 0);

private:
	template<typename Temp>
	/* Generic function to read an integer of specified length from the buffer */
	Temp readInteger(size_t length);

	/* Generic function to write data to the buffer */
	template<typename Temp>
	void writeData(const Temp& data);
};
// ByteStream Init
extern ByteStream Stream;

#endif // !BYTESTREAM_HPP