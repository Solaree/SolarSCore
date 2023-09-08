#ifndef LOGINOKMESSAGE_HPP
#define LOGINOKMESSAGE_HPP

class LoginOkMessage {
public:
	void LoginOkMessage(int sock);  /* Message init */
	void encode(int sock);  /* Message encoding */
	short getMessageType(); /* Message Id */
};

#endif // !LOGINOKMESSAGE_HPP