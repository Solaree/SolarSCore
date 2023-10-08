#ifndef LOGINOKMESSAGE_HPP
#define LOGINOKMESSAGE_HPP

#include "include/Stream/ByteStream.hpp"

class LoginOkMessage {
public:
	LoginOkMessage(int32_t sock);  /* Message init */
	static void encode(int32_t sock);  /* Message encoding */
	static const uint16_t getMessageType(); /* Message Id */
};

#endif // !LOGINOKMESSAGE_HPP