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
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*/

#include "include/Packets/Client/LoginMessage.hpp"

LoginMessage::LoginMessage(int32_t sock) {
	decode();
	Stream.buffer.clear();
	LoginOkMessage LoginOk(sock);
	OwnHomeDataMessage OwnHomeData(sock);
}

void LoginMessage::decode() {
	int32_t HighId = Stream.readInt();
	int32_t LowId = Stream.readInt();

	string Token = Stream.readString();

	int32_t MajorVersion = Stream.readInt();
	int32_t ContentVersion = Stream.readInt();
	int32_t BuildVersion = Stream.readInt();

	string ResourceSha = Stream.readString();

	cout << "[*] Received Authentication Data" << endl << "HighId: " << HighId << endl << "LowId: " << LowId << endl << "Token: " << Token << endl
		<< "GameVersion: " << MajorVersion << "." << ContentVersion << "." << BuildVersion << endl << "ResourceSha: " << ResourceSha << endl << endl;
}

const uint16_t LoginMessage::getMessageType() {
	return 10101;
}