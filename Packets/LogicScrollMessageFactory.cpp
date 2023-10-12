/*
* LogicScrollMessageFactory.cpp - The SolarSCore
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

#include "include/Packets/LogicScrollMessageFactory.hpp"

int32_t LogicScrollMessageFactory::sock;

void LogicScrollMessageFactory::createMessageByType(const uint16_t id) {
    if (id == ClientHelloMessage::getMessageType()) {
        ClientHelloMessage ClientHello(sock);
    } else if (id == LoginMessage::getMessageType()) {
        LoginMessage Login(sock);
    } else if (id == KeepAliveMessage::getMessageType()) {
        KeepAliveMessage KeepAlive(sock);
    } else {
    	cout << "[*] Unsupported message type: " << id << endl;
    }
}