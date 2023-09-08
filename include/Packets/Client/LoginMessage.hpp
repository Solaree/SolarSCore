#ifndef LOGINMESSAGE_HPP
#define LOGINMESSAGE_HPP
#include <string>

using namespace std;

class LoginMessage {
public:
	void LoginMessage(int sock); /* Message init */
	void decode(int sock); /* Message decoding */
	short getMessageType() /* Message Id */
};

#endif // !LOGINMESSAGE_HPP