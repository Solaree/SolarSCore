/*
* ServerHelloMessage.cpp - The SolarSCore
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