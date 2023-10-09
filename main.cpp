/*
* main.cpp - The SolarSCore
* Copyright (C) 2023 Solar
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*/

#include <ifaddrs.h>

#include <thread>

#include "include/Core/Crypto.hpp"
#include "include/Stream/ByteStream.hpp"
#include "include/Packets/LogicScrollMessageFactory.hpp"

void exec(int clientSocket) {
    LogicScrollMessageFactory::sock = clientSocket;

    while (true) {
        Stream.buffer.resize(7);

        string header((const char*)Stream.buffer.data(), 7);
        string decryptedStr = Crypto::decrypt(header);
        const char *decrypted = decryptedStr.c_str();

        if (recv(clientSocket, (char*)decrypted, 7, 0) > 0) {
            uint16_t packetId = Stream.readShort();
            uint16_t packetLen = Stream.readLen();
            uint16_t packetVer = Stream.readShort();

            cout << "[*] Got packet with Id: " << packetId << " || Length: " << packetLen << " || Version: " << packetVer << " || Content: " << "b\"";

            for (size_t i = 0; i < decryptedStr.size(); ++i) {
                cout << "\\x" << uppercase << hex << setw(2) << setfill('0') << ((int)decryptedStr[i] & 0xFF);
            }
            cout << "\"" << dec << endl << endl;

            if (recv(clientSocket, Stream.buffer.data(), packetLen, 0)) {
                memcpy(LogicScrollMessageFactory::buffer, Stream.buffer.data(), packetLen);

                LogicScrollMessageFactory::createMessageByType(packetId);
                memset(LogicScrollMessageFactory::buffer, 0, 512);
                Stream.buffer.clear();
            }
        }
        Stream.buffer.clear();
    }
}

void getipinfo() {
    struct ifaddrs *ifaddr, *ifa;

    getifaddrs(&ifaddr);

    for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next) {
        if (ifa->ifa_addr == NULL)
            continue;
        int family = ifa->ifa_addr->sa_family;

        if (family == AF_INET) { // Check for IPv4 address
            char ipAddr[INET_ADDRSTRLEN];
            struct sockaddr_in *addr = (struct sockaddr_in*)ifa->ifa_addr;

            inet_ntop(AF_INET, &(addr->sin_addr), ipAddr, INET_ADDRSTRLEN);

            if (strncmp(ipAddr, "192.", 3) == 0)
                cout << "[*] Local IP Address: " << ipAddr << endl;
        }
    }
    freeifaddrs(ifaddr);
}

int32_t main() {
    int32_t sockopt = 1;
    int32_t port = 9339;

    int32_t serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &sockopt, sizeof(int32_t));

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(port);

    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        cerr << "[*] Failed to bind socket" << endl;
        return EXIT_FAILURE;
    }

    if (listen(serverSocket, 1) == -1) {
        cerr << "[*] Listen failed" << endl;
        return EXIT_FAILURE;
    }

    cout << endl << "SolarSCore v1.4 [RELEASE]" << endl << endl << "[*] Server listening at 0.0.0.0:" << port << endl;

    getipinfo();
    
    cout << "[*] PID: " << getpid() << endl << endl;

    while (true) {
        int clientSocket = accept(serverSocket, nullptr, nullptr);

        if (clientSocket == -1) {
            cerr << "[*] Accept failed" << endl;
            continue;
        }

        cout << "[*] Connection from " << inet_ntoa(serverAddr.sin_addr) << ":" << ntohs(serverAddr.sin_port) << endl;

        thread th(exec, clientSocket);
        th.detach();
    }
    close(serverSocket);
    return EXIT_SUCCESS;
}