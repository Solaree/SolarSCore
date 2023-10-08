/*
* LogicScrollMessageFactory.cpp by Solar *
* https://github.com/Solaree *
*/

#include "include/Packets/LogicScrollMessageFactory.hpp"

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