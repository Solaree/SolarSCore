/* 
* ByteStream.hpp by Solar *
* https://github.com/Solaree *
*/

#ifndef BYTESTREAM_HPP
#define BYTESTREAM_HPP

class ByteStream {
public:
	void writeUInt8(const uint8_t val); /* Writes 1-byte 'uint8' in range from 0 to 255 via 'unsigned char' */
	int readUInt8(); /* Reads 1-byte 'uint8' */

	void writeBool(const bool val); /* Writes 1-byte 'bool' with 'uint8' (uses 0 for 'false', 1 for 'true') */
	bool readBool(); /* Reads 1-byte 'bool' using 'uint8' */

	void writeShort(const short val); /* Writes 2-bytes 'short' */
	short readShort(); /* Reads 2-bytes 'short' */

	void writeInt(const int val); /* Writes 4-bytes 'int' */
	int readInt(); /* Reads 4-bytes 'int' */

	void writeLong(const int highByte, const int lowByte); /* Writes 8-bytes 'long' using 2-times 'int' writing */
	long readLong(); /* Reads 8-bytes 'long' using 2-times 'int' reading */

	void writeVInt(const int val); /* Writes 7-bits 'vint' (VariableInteger) */
	int readVInt(); /* Reads 7-bits 'vint' (VariableInteger) */

	void writeArrayVInt(const int val); /* Writes array of 'vint' (VariableInteger) */

	void writeLogicLong(const int highByte, const int lowByte); /* Writes 14-bits 'long' using 2-times 'VInt' writing */
	long readLogicLong(); /* Reads 14-bits 'long' using 2-times 'VInt' writing */

	void writeBytes(const char* val); /* Writes raw bytes */

	void writeString(const string& s); /* Writes 'string' */
	string readString(); /* Reads 'string' */

	void writeStringRef(const string& s); /* Writes 'stringref' (StringReferance) */

	void writeHex(const string& hexa); /* Writes raw hex data */

	void send(int id, int sock); /* Sends packet to client */
}; /* ByteStream Class */

#endif // !BYTESTREAM_HPP