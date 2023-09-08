#include "../include/Stream/ByteStream.hpp"
#include "../include/Packets/Server/KeepAliveOkMessage.hpp"

ByteStream Stream;

void KeepAliveOkMessage::KeepAliveOkMessage(int sock) {
	encode();
	Stream.writePacket(getMessageType, sock);
}

void KeepAliveOkMessage::encode(int sock) {
	/* ... */
}

short KeepAliveOkMessage::getMessageType() {
	return 20108;
}