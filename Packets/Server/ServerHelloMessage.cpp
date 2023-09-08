#include "../include/Stream/ByteStream.hpp"
#include "../include/Packets/Server/ServerHelloMessage.hpp"

ByteStream Stream;

void ServerHelloMessage::ServerHelloMessage(int sock) {
	encode();
	Stream.packetWrite(getMessageType, sock);
}

void ServerHelloMessage::encode(int sock) {
	Stream.writeInt(24);

	for (int i = 0; i <= 24, i++)
		Stream.writeUInt8(255); // SessionKey
}

short ServerHelloMessage::getMessageType() {
	return 20100;
}