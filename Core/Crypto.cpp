/*
* Crypto.cpp by Solar *
* https://github.com/Solaree *
*/

#include "Core/arc4/arc4.hpp"
#include "include/Core/Crypto.hpp"

ARC4 RC4;

string key = "fhsd6f86f67rt8fw78fw789we78r9789wer6re";
string nonce = "nonce";

string Crypto::encrypt(const string& data) {
    string plainData(nonce + data);

    RC4.setKey((unsigned char*)key.c_str(), key.length());
    RC4.encrypt((unsigned char*)plainData.c_str(), (unsigned char*)plainData.c_str(), plainData.length());

    return plainData;
}

string Crypto::decrypt(const string& data) {
    string plainData(data);

    RC4.setKey((unsigned char*)key.c_str(), key.length());
    RC4.encrypt((unsigned char*)plainData.c_str(), (unsigned char*)plainData.c_str(), plainData.length());

    return plainData;
}