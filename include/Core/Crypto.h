/*
* Crypto.h - The SolarSCore
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

#ifndef CRYPTO_H
#define CRYPTO_H

#include <string.h>
#include <openssl/rc4.h>

size_t cslen(const unsigned char* data); /* Char pointer lenght util */

void RC4__init(); /* RC4 Init */
void RC4__encrypt(unsigned char *data); /* RC4 Encryption */

#endif // !CRYPTO_H