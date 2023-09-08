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

string Crypto::encrypt(string& data) {
    string plainData(nonce + data);

    RC4.setKey((unsigned char*)key.c_str(), key.length());
    RC4.encrypt((unsigned char*)plainData.c_str(), (unsigned char*)plainData.c_str(), plainData.length());

    return plainData;
}

string Crypto::decrypt(string& data) {
    string plainData(data);

    RC4.setKey((unsigned char*)key.c_str(), key.length());
    RC4.encrypt((unsigned char*)plainData.c_str(), (unsigned char*)plainData.c_str(), plainData.length());

    return plainData;
}