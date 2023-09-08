#ifndef CLIENTHELLOMESSAGE_HPP
#define CLIENTHELLOMESSAGE_HPP

class ClientHelloMessage {
public:
	void ClientHelloMessage(int sock); /* Message init */
	void decode(int sock); /* Message decoding */
	short getMessageType(); /* Message Id */
};

#endif // !CLIENTHELLOMESSAGE_HPP
