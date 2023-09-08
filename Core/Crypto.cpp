/*
* Crypto.cpp by Solar *
* https://github.com/Solaree *
*/

#include <string>
#include <cstring>
#include <cstdlib>
#include "../include/arc4.h"
#include "../include/Core/Crypto.hpp"

using namespace std;

ARC4 RC4;

string key = "fhsd6f86f67rt8fw78fw789we78r9789wer6re";
string nonce = "nonce";

char* Crypto::encrypt(string& data) {
	unsigned char* plainData = new unsigned char[nonce.length() + data.length()];

	memcpy(plainData, nonce.c_str(), nonce.length());
	memcpy(plainData + nonce.length(), data.c_str(), data.length());

	RC4.setKey((unsigned char*)key.c_str(), key.length());
	RC4.encrypt(plainData, plainData, nonce.length() + data.length());

	string encrypted(*plainData);

	return encrypted;
	delete[] plainData;
}

char* Crypto::decrypt(string& data) {
	unsigned char* plainData = new unsigned char[data.length()];

	memcpy(plainData, data.c_str(), data.length());

	RC4.setKey((unsigned char*)key.c_str(), key.length());
	RC4.encrypt(plainData, plainData, data.length());

	string decrypted(*plainData);

	return decrypted;
	delete[] plainData;
}