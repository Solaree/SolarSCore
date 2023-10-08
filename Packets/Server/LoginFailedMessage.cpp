#include "include/Packets/Server/LoginFailedMessage.hpp"

LoginFailedMessage::LoginFailedMessage(int32_t sock) {
	encode(sock);
	Stream.writePacket(getMessageType(), sock);
}

void LoginFailedMessage::encode(int32_t sock /* , string error */) {
	Stream.writeVInt(0); // Error Code

	Stream.writeString();
	Stream.writeString();
	Stream.writeString(); // Patch Url
	Stream.writeString(); // Update Url
	Stream.writeString("Connection failed"); // Error Message

	Stream.writeVInt(0);
}

const uint16_t LoginFailedMessage::getMessageType() {
	return 20103;
}