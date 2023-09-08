#include <string>
#include <iostream>
#include "../include/Stream/ByteStream.hpp"
#include "../include/Packets/Client/LoginMessage.hpp"
#include "../include/Packets/Server/LoginOkMessage.hpp"
#include "../include/Packets/Server/LoginFailedMessage.hpp"

char buffer[256];
ByteStream Stream;
LoginOkMessage LoginOk;
LoginFailedMessage LoginFailed;

using namespace std;

void LoginMessage::LoginMessage(int sock) {
	decode(sock);
	LoginOk.encode(sock);
}

void LoginMessage::decode(int sock) {
	Stream.buffer.insert(Stream.buffer.end(), begin(buffer), end(buffer);

	int HighId = Stream.readInt();
	int LowId = Stream.readInt();

	string Token = Stream.readString();

	int MajorVersion = Stream.readInt();
	int ContentVersion = Stream.readInt();
	int BuildVersion = Stream.readInt();

	string ResourceSha = Stream.readString();

	process(sock, HighId, LowId, Token, MajorVersion, ContentVersion, BuildVersion, ResourceSha);
}

void process(int sock, int HighId, int LowId, const string& Token, int MajorVersion, int ContentVersion, int BuildVersion, const string& ResourceSha) {
	cout << "[*] Received Authentication Data:" << endl << "HighId: " << HighId << endl << "LowId: " << LowId << endl << "Token: " << Token << "GameVersion: " << MajorVersion << "." << ContentVersion << "." << BuildVersion << endl << "ResourceSha: " << ResourceSha << endl;
}

short LoginMessage::getMessageType() {
	return 10101;
}