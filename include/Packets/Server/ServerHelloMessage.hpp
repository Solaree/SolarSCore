#ifndef SERVERHELLOMESSAGE_HPP
#define SERVERHELLOMESSAGE_HPP

#include "include/Stream/ByteStream.hpp"

class ServerHelloMessage {
public:
	ServerHelloMessage(int32_t sock);  /* Message init */
	static void encode(int32_t sock);  /* Message encoding */
	static const uint16_t getMessageType(); /* Message Id */
};

#endif // !SERVERHELLOMESSAGE_HPP