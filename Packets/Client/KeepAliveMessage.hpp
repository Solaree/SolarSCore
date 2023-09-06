#ifndef KEEPALIVEMESSAGE_HPP
#define KEEPALIVEMESSAGE_HPP

#include "../Server/KeepAliveOkMessage.hpp"

class KeepAliveMessage {
public:
	char buffer[256];

	void decode(int sock) {
		process(sock);
	}

	void process(int sock) {
		KeepAliveOkMessage KeepAliveOk;
		KeepAliveOk.encode(sock);
	}
};

#endif // !KEEPALIVEMESSAGE_HPP