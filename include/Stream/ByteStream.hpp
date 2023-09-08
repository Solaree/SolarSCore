/* 
* ByteStream.hpp by Solar *
* https://github.com/Solaree *
*/

#ifndef BYTESTREAM_HPP
#define BYTESTREAM_HPP

#include <vector>
#include <string>
#include <iomanip>
#include <iostream>
#include <sys/socket.h>

using namespace std;


class ByteStream {
public:
	vector<char>buffer; /* Stream buffer */

	void writeUInt8(uint8_t val); /* Writes 1-byte 'uint8' in range from 0 to 255 via 'unsigned char' */
	int readUInt8(); /* Reads 1-byte 'uint8' */

	void writeBool(bool val); /* Writes 1-byte 'bool' with 'uint8' (uses 0 for 'false', 1 for 'true') */
	bool readBool(); /* Reads 1-byte 'bool' using 'uint8' */

	void writeShort(short val); /* Writes 2-bytes 'short' */
	short readShort(); /* Reads 2-bytes 'short' */

	void writeInt(int val); /* Writes 4-bytes 'int' */
	int readInt(); /* Reads 4-bytes 'int' */

	void writeIntLittleEndian(int val); /* Writes 4-bytes 'int' in little-endian order */
	int readIntLittleEndian(); /* Reads 4-bytes 'int' in little-endian order */

	void writeLong(int highByte, int lowByte); /* Writes 8-bytes 'long' using 2-times 'int' writing */
	long readLong(); /* Reads 8-bytes 'long' using 2-times 'int' reading */

	void writeVInt(int val); /* Writes 7-bits 'vint' (VariableInteger) */
	int readVInt(); /* Reads 7-bits 'vint' (VariableInteger) */

	void writeArrayVInt(int val); /* Writes array of 'vint' (VariableInteger) */

	void writeLogicLong(int highByte, int lowByte); /* Writes 14-bits 'long' using 2-times 'vint' writing */
	long readLogicLong(); /* Reads 14-bits 'long' using 2-times 'vint' writing */

	void writeBytes(string val = ""); /* Writes bytes with 'string' type */

	void writeString(string s = ""); /* Writes 'string' */
	string readString(); /* Reads 'string' */

	void writeStringRef(string s = ""); /* Writes 'stringref' (StringReferance) */

	void writeHex(string hexa = ""); /* Writes raw hex data */

	void packetWrite(int id, int sock, int version = 0); /* Saves encrypted packet to buffer */
}; /* ByteStream Class */

#endif // !BYTESTREAM_HPP