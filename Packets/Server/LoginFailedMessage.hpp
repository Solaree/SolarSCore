#ifndef LOGINFAILEDMESSAGE_HPP
#define LOGINFAILEDMESSAGE_HPP

#include <string>
#include "../include/Stream/ByteStream.hpp"

using namespace std;

class LoginFailedMessage {
public:
	ByteStream Stream;

	void encode(int sock, string error) {
		Stream.writeLogicLong(4, 8); // Error Code

		Stream.writeString();
		Stream.writeString();
		Stream.writeString(); // Patch Url
		Stream.writeString(); // Update Url
		Stream.writeString(error); // Error Message

		Stream.writeLogicLong(4, 3600);
		Stream.writeLogicLong(1, 0);

		process(sock);
	}

	void process(int sock) {
		Stream.send(20103, sock);
	}
};

#endif // !LOGINFAILEDMESSAGE_HPP