/*
* LogicMagicMessageFactory.cpp by Solar *
* https://github.com/Solaree *
*/

#include <iostream>
#include "../Client/ClientHelloMessage.hpp"
#include "../Client/LoginMessage.hpp"
#include "../Client/KeepAliveMessage.hpp"
#include "../include/Packets/LogicMagicMessageFactory.hpp"

LogicMagicMessageFactory::createMessageByType(int id) {
	ClientHelloMessage ClientHello;
	LoginMessage Login;
	KeepAliveMessage KeepAlive;

	int sock;
	char buffer[512];

	switch (id) {
		case 10100:
			ClientHello.decode(sock);
			break;
		case 10101:
			Login.decode(sock);
			break;
		case 10108:
			KeepAlive.decode(sock);
			break;
		default:
			cout << "[*] Unsupported message type: " << id << endl;
			break;
	}
}