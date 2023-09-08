#include <iostream>
#include <thread>
#include <WinSock2.h>
#include "../include/Core/Crypto.hpp"
#include "../include/Stream/ByteStream.hpp"
#include "../include/Packets/LogicScrollMessageFactory.hpp"

using namespace std;

void exec(SOCKET client) {
    LogicScrollMessageFactory LogicMessageFactory;
    LogicMessageFactory.sock = client;
    ByteStream Stream;

    while (true) {
        Stream.buffer.resize(7);

        string header(Stream.buffer.data());
        char* decrypted = RC4Decrypt(header);
        string decryptedStr(*decrypted);

        if (recv(client, decrypted, 7, 0) > 0) {
            unsigned short packetId = Stream.readShort();
            unsigned short packetLen = Stream.readLen();
            unsigned short packetVer = Stream.readShort();

            cout << "[*] Got packet with Id: " << packetId << " || Length: " << packetLen << " || Version: " << packetVer << " || Content: " << "b\"";

            for (size_t i = 0; i < decryptedStr.size(); ++i) {
                cout << "\\x" << uppercase << hex << setw(2) << setfill('0') << ((int)decryptedStr[i] & 0xFF);
            }
            cout << "\"" << dec << endl << endl;

            char* buffer = new char[packetLen];

            if (recv(client, buffer, packetLen, 0) == packetLen) {
                memcpy(LogicMessageFactory.buffer, buffer, packetLen);

                LogicMessageFactory.createMessageByType(packetId);
                memset(LogicMessageFactory.buffer, 0, 512);

                delete[] buffer;
                Stream.buffer.clear();
            }
        }
        Stream.buffer.clear();
    }
}

int main() {
    int sockopt = 1;
    int port = 9339;
    WSADATA wsaData;

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        cerr << "[*] Failed to initialize Winsock" << endl;
        return 1;
    }

    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (const char*)&sockopt, sizeof(int));

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(port);

    if (bind(sock, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        cerr << "[*] Failed to bind socket" << endl;
        return 1;
    }

    if (listen(sock, 1) == SOCKET_ERROR) {
        cerr << "[*] Listen failed" << endl;
        return 1;
    }

    cout << "[*] SolarSCore v1.3 [RELEASE]" << endl << "Server listening at 0.0.0.0:" << port << endl;

    while (true) {
        SOCKET client = accept(sock, nullptr, nullptr);

        if (client == INVALID_SOCKET) {
            cerr << "[*] Accept failed" << endl;
            continue;
        }

        cout << "[*] Connection from " << inet_ntoa(serverAddr.sin_addr) << ":" << ntohs(serverAddr.sin_port) << endl;

        thread th(exec, client);
        th.detach();
    }

    closesocket(sock);
    WSACleanup();
    return 0;
}