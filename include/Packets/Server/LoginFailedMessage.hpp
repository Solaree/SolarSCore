#ifndef LOGINFAILEDMESSAGE_HPP
#define LOGINFAILEDMESSAGE_HPP

class LoginFailedMessage {
public:
	void LoginFailedMessage(int sock);  /* Message init */
	void encode(int sock, string error);  /* Message encoding */
	short getMessageType(); /* Message Id */
};

#endif // !LOGINFAILEDMESSAGE_HPP