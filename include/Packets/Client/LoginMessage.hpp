#ifndef LOGINMESSAGE_HPP
#define LOGINMESSAGE_HPP

#include "include/Stream/ByteStream.hpp"
#include "include/Packets/Server/LoginOkMessage.hpp"
#include "include/Packets/Server/LoginFailedMessage.hpp"

class LoginMessage {
public:
	static char buffer[256]; /* Main buffer */

	LoginMessage(int32_t sock); /* Message init */
	static void decode(int32_t sock); /* Message decoding */
	static const uint16_t getMessageType(); /* Message Id */
};

#endif // !LOGINMESSAGE_HPP