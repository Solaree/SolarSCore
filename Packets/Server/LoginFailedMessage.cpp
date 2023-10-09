/*
* LoginFailedMessage.cpp - The SolarSCore
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