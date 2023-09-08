#ifndef SERVERHELLOMESSAGE_HPP
#define SERVERHELLOMESSAGE_HPP

class ServerHelloMessage {
public:
	void ServerHelloMessage(int sock);  /* Message init */
	void encode(int sock);  /* Message encoding */
	short getMessageType(); /* Message Id */
};

#endif // !SERVERHELLOMESSAGE_HPP