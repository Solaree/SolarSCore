#include "include/Packets/Server/LoginOkMessage.hpp"

LoginOkMessage::LoginOkMessage(int32_t sock) {
	encode(sock);
	Stream.writePacket(getMessageType(), sock);
}

void LoginOkMessage::encode(int32_t sock) {
	Stream.writeLogicLong(0, 1); // AccountID
	Stream.writeLogicLong(0, 1); // HomeID

	Stream.writeString("Solar"); // PassToken
	Stream.writeString(); // FacebookID
	Stream.writeString(); // GameCenterID

	Stream.writeVInt(0); // MajorVersion
	Stream.writeVInt(0); // ServerBuild
	Stream.writeVInt(0); // ContentVersion

	Stream.writeString("dev"); // ServerEnvironment

	Stream.writeVInt(0); // SessionCount
	Stream.writeVInt(0); // PlayTimeSeconds
	Stream.writeVInt(0); // DaysSinceStartedPlaying

	Stream.writeString(); // FacebookAppId
	Stream.writeString(); // ServerTime
	Stream.writeString(); // AccountCreatedDate

	Stream.writeVInt(0); // Tier

	Stream.writeString(); // GoogleServiceID
}

const uint16_t LoginOkMessage::getMessageType() {
	return 20108;
}