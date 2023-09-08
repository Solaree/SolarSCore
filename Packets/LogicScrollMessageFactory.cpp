/*
* LogicScrollMessageFactory.cpp by Solar *
* https://github.com/Solaree *
*/

#include <iostream>
#include "../include/Packets/Client/ClientHelloMessage.hpp"
#include "../include/Packets/Client/LoginMessage.hpp"
#include "../include/Packets/Client/KeepAliveMessage.hpp"
#include "../include/Packets/LogicScrollMessageFactory.hpp"

int sock;
char buffer[512];

void LogicScrollMessageFactory::createMessageByType(int id) {
	ClientHelloMessage ClientHello;
	LoginMessage Login;
	KeepAliveMessage KeepAlive;

	switch (id) {
		case ClientHello.getMessageType:
			ClientHello.ClientHelloMessage(sock);
			break;
		case Login.getMessageType:
			Login.LoginMessage(sock);
			break;
		case KeepAlive.getMessageType:
			KeepAlive.KeepAliveMessage(sock);
			break;
		default:
			cout << "[*] Unsupported message type: " << id << endl;
			break;
	}
}