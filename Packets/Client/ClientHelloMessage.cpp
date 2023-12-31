/*
* ClientHelloMessage.cpp - The SolarSCore
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

#include "include/Packets/Client/ClientHelloMessage.hpp"

char ClientHelloMessage::buffer[256];

ClientHelloMessage::ClientHelloMessage(int32_t sock) {
	decode();
	Stream.buffer.clear();
	ServerHelloMessage ServerHello(sock);
}

void ClientHelloMessage::decode() {
	Stream.buffer.insert(Stream.buffer.end(), begin(buffer), end(buffer));

	int32_t Protocol = Stream.readInt();
	int32_t KeyVersion = Stream.readInt();
	int32_t MajorVersion = Stream.readInt();
	int32_t BuildVersion = Stream.readInt();
	int32_t ContentVersion = Stream.readInt();

	string ResourceSha = Stream.readString();

	int32_t Device = Stream.readInt();
	int32_t Store = Stream.readInt();

	cout << "[*] Received Session Data" << endl << "Protocol: " << Protocol << endl
		<< "KeyVersion: " << KeyVersion << endl << "GameVersion: " << MajorVersion << "." << ContentVersion << "." << BuildVersion << endl
		<< "ResourceSha: " << ResourceSha << endl << "Device: " << Device << endl << "Store: " << Store << endl << endl;
}

const uint16_t ClientHelloMessage::getMessageType() {
	return 10100;
}