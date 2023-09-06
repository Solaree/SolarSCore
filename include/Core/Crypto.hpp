/*
* Crypto.hpp by Solar *
* https://github.com/Solaree *
*/

#ifndef CRYPTO_HPP
#define CRYPTO_HPP

class Crypto {
public:
	char* encrypt(const string& data); /* ARC4 Encryption */
	char* decrypt(const string& data); /* ARC4 Decryption */
};

#define RC4Encrypt Crypto::encrypt /* ARC4 Encryption */
#define RC4Decrypt Crypto::decrypt /* ARC4 Decryption */

#endif // !CRYPTO_HPP