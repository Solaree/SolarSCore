/*
* LoginMessage.cpp - The SolarSCore
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

#include "include/Packets/Client/LoginMessage.hpp"

char LoginMessage::buffer[256];

LoginMessage::LoginMessage(int32_t sock) {
	decode(sock);
	LoginOkMessage::encode(sock);
}

void LoginMessage::decode(int32_t sock) {
	Stream.buffer.insert(Stream.buffer.end(), begin(buffer), end(buffer));

	int32_t HighId = Stream.readInt();
	int32_t LowId = Stream.readInt();

	string Token = Stream.readString();

	int32_t MajorVersion = Stream.readInt();
	int32_t ContentVersion = Stream.readInt();
	int32_t BuildVersion = Stream.readInt();

	string ResourceSha = Stream.readString();

	cout << "[*] Received Authentication Data:" << endl << "HighId: " << HighId << endl << "LowId: " << LowId << endl << "Token: " << Token.c_str() << "GameVersion: " << MajorVersion << "." << ContentVersion << "." << BuildVersion << endl << "ResourceSha: " << ResourceSha.c_str() << endl;
}

const uint16_t LoginMessage::getMessageType() {
	return 10101;
}