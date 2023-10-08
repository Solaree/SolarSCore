#ifndef LOGINFAILEDMESSAGE_HPP
#define LOGINFAILEDMESSAGE_HPP

#include "include/Stream/ByteStream.hpp"

class LoginFailedMessage {
public:
	LoginFailedMessage(int32_t sock);  /* Message init */
	static void encode(int32_t sock);  /* Message encoding */
	static const uint16_t getMessageType(); /* Message Id */
};

#endif // !LOGINFAILEDMESSAGE_HPP