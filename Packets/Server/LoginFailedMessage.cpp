#include <string>
#include "../include/Stream/ByteStream.hpp"
#include "../include/Packets/Server/LoginFailedMessage.hpp"

using namespace std;

ByteStream Stream;

void LoginFailedMessage::LoginFailedMessage(int sock) {
	encode();
	Stream.writePacket(getMessageType, sock);
}

void LoginFailedMessage::encode(int sock, string error) {
	Stream.writeVInt(0); // Error Code

	Stream.writeString();
	Stream.writeString();
	Stream.writeString(); // Patch Url
	Stream.writeString(); // Update Url
	Stream.writeString(error); // Error Message

	Stream.writeVInt(0);
}

short LoginFailedMessage::getMessageType() {
	return 20103;
}