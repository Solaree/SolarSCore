/*
* Crypto.c - The SolarSCore
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

#include "include/Core/Crypto.h"

typedef struct {
    RC4_KEY RC4_Key;
    unsigned char Key[39];
    unsigned char Nonce[6];
} ARC4;
ARC4 Crypto;

size_t cslen(const unsigned char* data) {
    size_t length = 0;
    while (data[length] != '\0') {
        ++length;
    }
    return length;
}

void RC4__init() {
    strcpy((char*)(Crypto.Key), "fhsd6f86f67rt8fw78fw789we78r9789wer6re");
    strcpy((char*)(Crypto.Nonce), "nonce");
    RC4_set_key(&Crypto.RC4_Key, 38, Crypto.Key);
}

void RC4__encrypt(unsigned char *data) {
    RC4__init();
    RC4(&Crypto.RC4_Key, cslen(data), data, data);
}