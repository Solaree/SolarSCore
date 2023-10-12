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

#ifdef linux
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

class ByteStream {
public:
	static vector<uint8_t> buffer; /* Main buffer (we switch between dataBuf and headBuf when send packet content) */
	static vector<uint8_t> headBuf; /* Header buffer */

	static void setBuffer(vector<uint8_t>& buf); /* Sets argument vector to the stream buffer */

	void writeUInt8(uint8_t val); /* Writes 1-byte 'uint8' in range from 0 to 255 via 'unsigned char' */
	uint8_t readUInt8(); /* Reads 1-byte 'uint8' */

	void writeBool(bool val); /* Writes 1-byte 'bool' with 'uint8' (uses 0 for 'false', 1 for 'true') */
	bool readBool(); /* Reads 1-byte 'bool' using 'uint8' */

	void writeShort(int16_t val); /* Writes 2-bytes 'short' */
	int16_t readShort(); /* Reads 2-bytes 'short' */

	void writeInt(int32_t val); /* Writes 4-bytes 'int' */
	int32_t readInt(); /* Reads 4-bytes 'int' */

	void writeLong(int32_t hiByte, int32_t loByte); /* Writes 8-bytes 'long' using 2-times 'int' writing */
	pair<int32_t, int32_t> readLong(); /* Reads 8-bytes 'long' using 2-times 'int' reading */

	void writeVInt(int32_t val); /* Writes 7-bits 'vint' (VariableInteger) */
	int32_t readVInt(); /* Reads 7-bits 'vint' (VariableInteger) */

	void writeArrayVInt(int32_t* val, int32_t count); /* Writes array of 'vint' (VariableInteger) */

	void writeLogicLong(int32_t hiByte, int32_t loByte); /* Writes 14-bits 'long' using 2-times 'vint' writing */
	pair<int32_t, int32_t> readLogicLong(); /* Reads 14-bits 'long' using 2-times 'vint' writing */

	void writeBytes(const string& val = ""); /* Writes bytes with 'string' type */

	void writeString(const string& s = ""); /* Writes 'string' */
	string readString(); /* Reads 'string' */

	void writeStringRef(const string& s = ""); /* Writes 'stringref' (StringReferance) */

	void writeHex(const string& hexa = ""); /* Writes raw hex data */

	vector<uint8_t> hexStringToBytes(const string& hexStr); /* Util used for 'writeHex() function */

	void writePacket(const uint16_t id, int32_t sock, uint16_t ver = 0); /* Writes encrypted packet to buffer */

private:
	template<typename Temp>
	Temp readInteger(size_t length); /* Generic function to read an integer of specified length from the buffer */

	template<typename Temp>
	void writeData(const Temp& data);
}; /* ByteStream Class */
extern ByteStream Stream; // ByteStream Init

#endif // !BYTESTREAM_HPP