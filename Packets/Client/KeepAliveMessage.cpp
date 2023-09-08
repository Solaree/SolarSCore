#include "../include/Packets/Client/KeepAliveMessage.hpp"
#include "../include/Packets/Server/KeepAliveOkMessage.hpp"

char buffer[256];
KeepAliveOkMessage KeepAliveOk;

void KeepAliveMessage::KeepAliveMessage(int sock) {
	decode(sock);
	KeepAliveOk.encode(sock);
}

void KeepAliveMessage::decode(int sock) {
	process(sock);
}

void process(int sock) {
	/* ... */
}

short KeepAliveMessage::getMessageType() {
	return 10108;
}