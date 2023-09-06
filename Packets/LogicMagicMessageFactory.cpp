#include <iostream>
#include "Client/ClientHelloMessage.cpp"
#include "Client/LoginMessage.cpp"
#include "Client/KeepAliveMessage.cpp"

class LogicMagicMessageFactory {
public:
	int sock;
	char buffer[512];

	ClientHelloMessage ClientHello;
	LoginMessage Login;
	KeepAliveMessage KeepAlive;

	createMessageByType(int id) {
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
};