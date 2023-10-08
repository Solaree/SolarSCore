#include "include/Packets/Server/ServerHelloMessage.hpp"

ServerHelloMessage::ServerHelloMessage(int32_t sock) {
	encode(sock);
	Stream.writePacket(getMessageType(), sock);
}

void ServerHelloMessage::encode(int32_t sock) {
	Stream.writeInt(24);

	for (int i = 0; i <= 24; i++)
		Stream.writeUInt8(255); // SessionKey (0xFF)
}

const uint16_t ServerHelloMessage::getMessageType() {
	return 20100;
}