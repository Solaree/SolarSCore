#include "Server/KeepAliveOkMessage.cpp"

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
