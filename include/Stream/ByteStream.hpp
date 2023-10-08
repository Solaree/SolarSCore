/* 
* ByteStream.hpp by Solar *
* https://github.com/Solaree *
*/

#ifndef BYTESTREAM_HPP
#define BYTESTREAM_HPP

#include <unistd.h>
#include <arpa/inet.h>

#include <vector>
#include <cstring>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <algorithm>
#include "include/Core/Crypto.hpp"

using namespace std;

class ByteStream {
public:
	vector<uint8_t> buffer; /* Main buffer */

	void writeUInt8(uint8_t val); /* Writes 1-byte 'uint8' in range from 0 to 255 via 'unsigned char' */
	uint8_t readUInt8(); /* Reads 1-byte 'uint8' */

	void writeBool(bool val); /* Writes 1-byte 'bool' with 'uint8' (uses 0 for 'false', 1 for 'true') */
	bool readBool(); /* Reads 1-byte 'bool' using 'uint8' */

	void writeShort(int16_t val); /* Writes 2-bytes 'short' */
	int16_t readShort(); /* Reads 2-bytes 'short' */

	int16_t readLen(); /* Reads 3-bytes, used for packet length reading */

	void writeInt(int32_t val); /* Writes 4-bytes 'int' */
	int32_t readInt(); /* Reads 4-bytes 'int' */

	void writeIntLittleEndian(int32_t val); /* Writes 4-bytes 'int' in little-endian order */
	int32_t readIntLittleEndian(); /* Reads 4-bytes 'int' in little-endian order */

	void writeLong(int32_t highByte, int32_t lowByte); /* Writes 8-bytes 'long' using 2-times 'int' writing */
	pair<int32_t, int32_t> readLong(); /* Reads 8-bytes 'long' using 2-times 'int' reading */

	void writeVInt(int32_t val); /* Writes 7-bits 'vint' (VariableInteger) */
	int32_t readVInt(); /* Reads 7-bits 'vint' (VariableInteger) */

	void writeArrayVInt(int32_t* val, int32_t count); /* Writes array of 'vint' (VariableInteger) */

	void writeLogicLong(int32_t highByte, int32_t lowByte); /* Writes 14-bits 'long' using 2-times 'vint' writing */
	pair<int32_t, int32_t> readLogicLong(); /* Reads 14-bits 'long' using 2-times 'vint' writing */

	void writeBytes(const string& val = ""); /* Writes bytes with 'string' type */

	void writeString(string s = ""); /* Writes 'string' */
	string readString(); /* Reads 'string' */

	void writeStringRef(string s = ""); /* Writes 'stringref' (StringReferance) */

	void writeHex(string hexa = ""); /* Writes raw hex data */

	vector<uint8_t> hexStringToBytes(const string& hexString); /* Util used for 'writeHex() function */

	void writePacket(int32_t id, int32_t sock, int32_t version = 0); /* Writes encrypted packet to buffer */
}; /* ByteStream Class */

extern ByteStream Stream; // ByteStream Init

#endif // !BYTESTREAM_HPP