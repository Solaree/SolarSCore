#include "include/Packets/Client/KeepAliveMessage.hpp"

KeepAliveMessage::KeepAliveMessage(int32_t sock) {
	decode(sock);
	KeepAliveOkMessage::encode(sock);
}

void KeepAliveMessage::decode(int32_t sock) {
	/* ... */
}

const uint16_t KeepAliveMessage::getMessageType() {
	return 10108;
}