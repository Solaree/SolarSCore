/*
* Crypto.cpp - The SolarSCore
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