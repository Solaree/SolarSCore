#ifndef CLIENTHELLOMESSAGE_HPP
#define CLIENTHELLOMESSAGE_HPP

#include "include/Stream/ByteStream.hpp"
#include "include/Packets/Server/ServerHelloMessage.hpp"


class ClientHelloMessage {
public:
	static char buffer[256]; /* Main buffer */

	ClientHelloMessage(int32_t sock); /* Message init */
	static void decode(int32_t sock); /* Message decoding */
	static const uint16_t getMessageType(); /* Message Id */
};

#endif // !CLIENTHELLOMESSAGE_HPP
