#ifndef KEEPALIVEMESSAGE_HPP
#define KEEPALIVEMESSAGE_HPPs

class KeepAliveMessage {
public:
	void KeepAliveMessage(int sock); /* Message init */
	void decode(int sock); /* Message decoding */
	short getMessageType(); /* Message Id */
};

#endif // !KEEPALIVEMESSAGE_HPP