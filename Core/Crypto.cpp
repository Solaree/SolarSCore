#include <string>
#include <cstring>
#include <cstdlib>
#include "include/arc4.cpp"

using namespace std;

class Crypto {
public:
    ARC4 RC4;

    string key = "fhsd6f86f67rt8fw78fw789we78r9789wer6re";
    string nonce = "nonce";

    char* encrypt(const string& data) {
        char* encr = (char*)malloc(data.size() + 1);
        unsigned char* plainData = new unsigned char[nonce.length() + data.length()];

        memcpy(plainData, nonce.c_str(), nonce.length());
        memcpy(plainData + nonce.length(), data.c_str(), data.length());

        RC4.setKey((unsigned char*)key.c_str(), key.length());
        RC4.encrypt(plainData, encr, nonce.length() + data.length());

        delete[] plainData;

        return encr;
        free(encr);
    }

    char* decrypt(const string& data) {
        char* decr = (char*)malloc(data.size() + 1);
        unsigned char* plainData = new unsigned char[data.length()];

        memcpy(plainData, data.c_str(), data.length());

        RC4.setKey((unsigned char*)key.c_str(), key.length());
        RC4.encrypt(plainData, decr, data.length());

        delete[] plainData;

        return decr;
        free(decr);
    }
};
