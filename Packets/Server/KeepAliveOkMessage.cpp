#include "include/Packets/Server/KeepAliveOkMessage.hpp"

KeepAliveOkMessage::KeepAliveOkMessage(int32_t sock) {
	encode(sock);
	Stream.writePacket(getMessageType(), sock);
}

void KeepAliveOkMessage::encode(int32_t sock) {
	/* ... */
}

const uint16_t KeepAliveOkMessage::getMessageType() {
	return 20108;
}