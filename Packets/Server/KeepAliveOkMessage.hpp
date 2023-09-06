#ifndef KEEPALIVEOKMESSAGE_HPP
#define KEEPALIVEOKMESSAGE_HPP

#include "../include/Stream/ByteStream.hpp"

class KeepAliveOkMessage {
public:
	ByteStream Stream;

	void encode(int sock) {
		process(sock);
	}

	void process(int sock) {
		Stream.send(20108, sock);
	}
};

#endif // !KEEPALIVEMESSAGE_HPP