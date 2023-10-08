#include "include/Packets/Client/ClientHelloMessage.hpp"

char ClientHelloMessage::buffer[256];

ClientHelloMessage::ClientHelloMessage(int32_t sock) {
	decode(sock);
	ServerHelloMessage::encode(sock);
}

void ClientHelloMessage::decode(int32_t sock) {
	Stream.buffer.insert(Stream.buffer.end(), begin(buffer), end(buffer));

	int32_t Protocol = Stream.readInt();
	int32_t KeyVersion = Stream.readInt();
	int32_t MajorVersion = Stream.readInt();
	int32_t BuildVersion = Stream.readInt();
	int32_t ContentVersion = Stream.readInt();

	string ResourceSha = Stream.readString();

	int32_t Device = Stream.readInt();
	int32_t Store = Stream.readInt();

	cout << "[*] Received Session Data:" << endl << "Protocol: " << Protocol << endl << "KeyVersion: " << KeyVersion << endl << "GameVersion: " << MajorVersion << "." << ContentVersion << "." << BuildVersion << endl << "ResourceSha: " << ResourceSha.c_str() << endl << "Device: " << Device << endl << "Store: " << Store << endl;
}

const uint16_t ClientHelloMessage::getMessageType() {
	return 10100;
}