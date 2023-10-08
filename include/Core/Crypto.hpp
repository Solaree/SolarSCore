/*
* Crypto.hpp by Solar *
* https://github.com/Solaree *
*/

#ifndef CRYPTO_HPP
#define CRYPTO_HPP

#include <string>

using namespace std;

class Crypto {
public:
	static string encrypt(const string& data); /* ARC4 Encryption */
	static string decrypt(const string& data); /* ARC4 Decryption */
};

#endif // !CRYPTO_HPP