/*
* LoginOkMessage.cpp - The SolarSCore
* Copyright (C) 2023 Solar
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*/

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