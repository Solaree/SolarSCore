#ifndef KEEPALIVEMESSAGE_HPP
#define KEEPALIVEMESSAGE_HPP

#include "include/Packets/Server/KeepAliveOkMessage.hpp"

class KeepAliveMessage {
public:
	KeepAliveMessage(int32_t sock); /* Message init */
	static void decode(int32_t sock); /* Message decoding */
	static const uint16_t getMessageType(); /* Message Id */
};

#endif // !KEEPALIVEMESSAGE_HPP