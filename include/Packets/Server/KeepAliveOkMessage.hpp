#ifndef KEEPALIVEOKMESSAGE_HPP
#define KEEPALIVEOKMESSAGE_HPP

class KeepAliveOkMessage {
public:
	void KeepAliveOkMessage(int sock);  /* Message init */
	void encode(int sock);  /* Message encoding */
	short getMessageType(); /* Message Id */
};

#endif // !KEEPALIVEOKMESSAGE_HPP