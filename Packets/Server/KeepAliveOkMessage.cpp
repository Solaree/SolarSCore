#include "Stream/ByteStream.cpp"

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