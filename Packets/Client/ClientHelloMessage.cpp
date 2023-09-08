#include <string>
#include <iostream>
#include "../include/Stream/ByteStream.hpp"
#include "../include/Packets/Client/ClientHelloMessage.hpp"
#include "../include/Packets/Server/ServerHelloMessage.hpp"

using namespace std;

char buffer[256];
ByteStream Stream;
ServerHelloMessage ServerHello;

void ClientHelloMessage::ClientHelloMessage(int sock) {
	decode(sock);
	ServerHello.encode(sock);
}

void decode(int sock) {
	int Protocol = Stream.readInt();
	int KeyVersion = Stream.readInt();
	int MajorVersion = Stream.readInt();
	int BuildVersion = Stream.readInt();
	int ContentVersion = Stream.readInt();
	string ResourceSha = Stream.readString();
	int Device = Stream.readInt();
	int Store = Stream.readInt();

	process(sock, Protocol, KeyVersion, MajorVersion, BuildVersion, ContentVersion, ResourceSha, Device, Store);
}

void process(int sock, int Protocol, int KeyVersion, int MajorVersion, int BuildVersion, int ContentVersion, const string& ResourceSha, int Device, int Store) {
	cout << "[*] Received Session Data:" << endl << "Protocol: " << Protocol << endl << "KeyVersion: " << KeyVersion << endl << "GameVersion: " << MajorVersion << "." << ContentVersion << "." << BuildVersion << endl << "ResourceSha: " << ResourceSha << endl << "Device: " << Device << endl << "Store: " << Store << endl;
}

short getMessageType() {
	return 10100;
}