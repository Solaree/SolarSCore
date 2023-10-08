#ifndef KEEPALIVEOKMESSAGE_HPP
#define KEEPALIVEOKMESSAGE_HPP

#include "include/Stream/ByteStream.hpp"

class KeepAliveOkMessage {
public:
	KeepAliveOkMessage(int32_t sock);  /* Message init */
	static void encode(int32_t sock);  /* Message encoding */
	static const uint16_t getMessageType(); /* Message Id */
};

#endif // !KEEPALIVEOKMESSAGE_HPP