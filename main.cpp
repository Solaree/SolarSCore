#include <string>
#include <thread>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "../include/Core/Crypto.hpp"
#include "../include/Stream/ByteStream.hpp"
#include "../include/Packets/LogicMagicMessageFactory.hpp"

using namespace std;

void exec(int client) {
	LogicMagicMessageFactory LogicMessageFactory;
	LogicMessageFactory.sock = client;
	ByteStream Stream;

	while (true) {
		Stream.buffer.resize(7);

		string dataStr(Stream.buffer.data());
		char* decrypted = RC4Decrypt(dataStr);

		if (recv(client, decrypted 7, 0) > 0) {
			unsigned short id = Stream.readShort();
			unsigned int len = Stream.readInt();
			unsigned char ver = Stream.readUInt8();

			cout << "[*] Got packet with Id: " << id << " || Length: " << len << " || Version: " << ver << endl;

			Stream.buffer.resize(len);
			recv(client, decrypted, len, 0);

			memcpy(LogicMessageFactory.buffer, decrypted, len);

			LogicMessageFactory.createMessageByType(id);

			memset(LogicMessageFactory.buffer, 0, 512);
			Stream.buffer.clear();
		}
		Stream.buffer.clear();
	}
}

int main() {
	int sockopt = 1;
	int port = 9339;
	struct sockaddr_in socks;
	int socks_size = sizeof(socks);
	
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &sockopt, sizeof(sockopt));

	socks.sin_family = AF_INET;
	socks.sin_addr.s_addr = INADDR_ANY;
	socks.sin_port = htons(port);

	bind(sock, (struct sockaddr *)&socks, sizeof(socks));
	cout << "[*] Server running at 0.0.0.0:" << port << endl;

	while (true) {
		int client = accept(sock, (struct sockaddr*)&socks, (socklen_t*)&socks_size);

		listen(sock, 1);

		cout << "[*] Connection from " << client[0] << ":" << client[1] << endl;

		thread th(exec, client);
		th.detach();
	}
}