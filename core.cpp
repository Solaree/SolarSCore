/*
* core.cpp - The SolarSCore
* Copyright (C) 2023 Solar
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*/

#ifdef linux
    #include <ifaddrs.h>
#elif defined(_WIN32)
    #include <winsock2.h>
    #include <ws2tcpip.h>
#endif

#include "include/Core/Crypto.h"
#include "include/Packets/LogicScrollMessageFactory.hpp"

void getipinfo() {
#ifdef linux
    struct ifaddrs *ifaddr, *ifa;

    getifaddrs(&ifaddr);

    for (ifa = ifaddr; ifa != nullptr; ifa = ifa->ifa_next) {
        if (ifa->ifa_addr == nullptr)
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
#elif defined(_WIN32)
    ULONG outBufLen = 15000; // Initial buffer size
    ULONG flags = GAA_FLAG_INCLUDE_PREFIX;
    PIP_ADAPTER_ADDRESSES pAddresses = nullptr;
    PIP_ADAPTER_ADDRESSES pCurrAddresses = nullptr;

    do {
        pAddresses = (IP_ADAPTER_ADDRESSES*)(malloc(outBufLen));

        if (pAddresses == nullptr) {
            cerr << "[*] Memory allocation failed for IP_ADAPTER_ADDRESSES" << endl;
            return;
        }

        DWORD ret = GetAdaptersAddresses(AF_UNSPEC, flags, nullptr, pAddresses, &outBufLen);
        if (ret == ERROR_BUFFER_OVERFLOW) {
            free(pAddresses);
            pAddresses = nullptr;
        } else if (ret == ERROR_SUCCESS) {
            break;
        } else {
            cerr << "[*] GetAdaptersAddresses failed with error code: " << ret << endl;
            free(pAddresses);
            return;
        }
    } while (pAddresses == nullptr);

    pCurrAddresses = pAddresses;

    while (pCurrAddresses) {
        if (pCurrAddresses->OperStatus == IfOperStatusUp && pCurrAddresses->FirstUnicastAddress != nullptr) {
            sockaddr* sockaddrPtr = pCurrAddresses->FirstUnicastAddress->Address.lpSockaddr;

            if (sockaddrPtr->sa_family == AF_INET) {
                sockaddr_in* addr = (sockaddr_in*)(sockaddrPtr);
                char ipAddr[INET_ADDRSTRLEN];

                inet_ntop(AF_INET, &(addr->sin_addr), ipAddr, INET_ADDRSTRLEN);

                if (strncmp(ipAddr, "192.", 3) == 0) {
                    cout << "[*] Local IP Address: " << ipAddr << endl;
                    break;
                }
            }
        }
        pCurrAddresses = pCurrAddresses->Next;
    }

    if (pAddresses) {
        free(pAddresses);
    }
#endif
}

void clientThread(int32_t clientsock, sockaddr_in clientaddr) {
    LogicScrollMessageFactory::sock = clientsock;

    while (true) {
        unsigned char headerBuf[7];

        if (recv(clientsock, headerBuf, 7, 0) <= 0) {
            cerr << "[*] Connection closed from " << inet_ntoa(clientaddr.sin_addr) << ":" << ntohs(clientaddr.sin_port) << endl;
            close(clientsock);
            break;
        }

        uint16_t packetId  = headerBuf[0] <<  8 |  headerBuf[1];
        uint32_t packetLen = headerBuf[2] << 16 | (headerBuf[3] << 8) | headerBuf[4];
        uint16_t packetVer = headerBuf[5] <<  8 |  headerBuf[6];

        unsigned char packetBuf[packetLen];
    
        recv(clientsock, packetBuf, packetLen, 0);
        // RC4__encrypt(packetBuf);

        vector<uint8_t> packetData(packetBuf, packetBuf + packetLen);

        cout << "[*] Got packet with Id: " << packetId << " || Length: " << packetLen
            << " || Version: " << packetVer << " || Content: ";

        for (size_t i = 0; i < 7; ++i)
            cout << uppercase << hex << setw(2) << setfill('0') << (int)headerBuf[i];
        for (size_t i = 0; i < packetLen; ++i)
            cout << uppercase << hex << setw(2) << setfill('0') << (int)packetData[i];
        cout << dec << endl << endl;

        Stream.setBuffer(packetData);
        LogicScrollMessageFactory::createMessageByType(packetId);
    }
}

int serverThread() {
    int32_t sockopt = 1;
    int32_t port = 9339;

#ifdef _WIN32
    WSADATA wsaData;

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        cerr << "[*] Failed to initialize Winsock" << endl;
        return EXIT_FAILURE;
    }
#endif

    int32_t sockfd = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, reinterpret_cast<const char*>(&sockopt), sizeof(int32_t));

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(port);

    if (bind(sockfd, (struct sockaddr*)(&serverAddr), sizeof(serverAddr)) == -1) {
        cerr << "[*] Failed to bind socket" << endl;

#ifdef _WIN32
        WSACleanup();
#endif
        return EXIT_FAILURE;
    }

    if (listen(sockfd, 1) == -1) {
        cerr << "[*] Listen failed" << endl;
#ifdef _WIN32
        WSACleanup();
#endif
        return EXIT_FAILURE;
    }

    cout << endl << "SolarSCore v1.5 [RELEASE]" << endl << endl << "[*] Server listening at 0.0.0.0:" << port << endl;

    getipinfo();
    
    cout << "[*] PID: " << getpid() << endl << endl;

    while (true) {
        sockaddr_in clientaddr;
        socklen_t clientaddrlen = sizeof(clientaddr);

        int clientsock = accept(sockfd, (struct sockaddr*)&clientaddr, &clientaddrlen);

        if (clientsock == -1) {
            cerr << "[*] Accept failed" << endl;
            continue;
        }
        cout << "[*] Connection from " << inet_ntoa(clientaddr.sin_addr) << ":" << ntohs(clientaddr.sin_port) << endl;

        clientThread(clientsock, clientaddr);
        close(clientsock);
    }
    close(sockfd);
#ifdef _WIN32
    WSACleanup();
#endif
    return EXIT_SUCCESS;
}

int main() {
    serverThread();
    return EXIT_SUCCESS;
}