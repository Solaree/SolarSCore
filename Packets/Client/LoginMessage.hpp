#ifndef LOGINMESSAGE_HPP
#define LOGINMESSAGE_HPP

#include <string>
#include <iostream>
#include "../Server/LoginOkMessage.hpp"
#include "../Server/LoginFailedMessage.hpp"
#include "../include/Stream/ByteStream.hpp"

using namespace std;

class LoginMessage {
public:
    ByteStream Stream;
    char buffer[256];

    void decode(int sock) {
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
        if (MajorVersion != 50) {
            LoginFailedMessage LoginFailed;
            LoginFailed.encode(sock, "Unsupported version!");
            return;
        }
        LoginOkMessage LoginOk;
        LoginOk.encode(sock);

        cout << "[*] Received Authentication Data:" << endl << "HighId: " << HighId << endl << "LowId: " << LowId << endl << "Token: " << Token << "GameVersion: " << MajorVersion << "." << ContentVersion << "." << BuildVersion << endl << "ResourceSha: " << ResourceSha << endl;
    }
};

#endif // !LOGINMESSAGE_HPP