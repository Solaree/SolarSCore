/*
* LogicScrollMessageFactory.hpp by Solar *
* https://github.com/Solaree *
*/

#ifndef LOGICSCROLLMESSAGEFACTORY_HPP
#define LOGICSCROLLMESSAGEFACTORY_HPP

#include "include/Packets/Client/ClientHelloMessage.hpp"
#include "include/Packets/Client/LoginMessage.hpp"
#include "include/Packets/Client/KeepAliveMessage.hpp"

class LogicScrollMessageFactory {
public:
	int32_t sock; /* Socket */
	char buffer[512]; /* Main buffer */
	void createMessageByType(const uint16_t id); /* Creates Server-Side Message */
};

#endif // !LOGICSCROLLMESSAGEFACTORY_HPP