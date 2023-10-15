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
*
* BLAKE2B — Fast secure hashing.
* Copyright (C) 2012, Samuel Neves
*
* All the 'BLAKE2B' code is triple-licensed under the CC0, the OpenSSL Licence,
* or the Apache Public License 2.0, at your choosing
*
* TweetNaCl - A crypto library in 100 tweets
* Copyright (C) 2017 D. J. Bernstein, Bernard van Gastel, W. Janssen,
* T. Lange, P. Schwabe, S. Smetsers
*
* Special thanks to Risporce for his BSDS Crypto implementation
* via Python: https://github.com/risporce/BSDS/blob/main/Classes/Crypto.py
*/

#ifndef CRYPTO_H
#define CRYPTO_H

#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <sodium.h>

#define N 256 // 2^8

typedef struct
{
    unsigned char key[38];
    unsigned char nonce[5];
} ARC4;
extern ARC4 RC4;

typedef struct
{
    unsigned char     server_public_key[32];
    unsigned char    server_private_key[32];
    unsigned char     client_public_key[32];
    unsigned char shared_encryption_key[32];

    unsigned char nonce[24];

    unsigned char *encryptNonce;
    unsigned char *decryptNonce;

    unsigned char s[32];
} PepperInit;
extern PepperInit Pepper;

/* ARC4 Swap */
void RC4__swap(unsigned char *a, unsigned char *b);

/* ARC4 KSA */
int32_t RC4__KSA(unsigned char *S);

/* ARC4 PRGA */
int32_t RC4__PRGA(unsigned char *S, unsigned char *plaintext, unsigned char *ciphertext);

/* ARC4 encryption/decryption implementation */
int32_t RC4__encrypt(unsigned char *plaintext, unsigned char *ciphertext);

/* Blake2b Nonce Init */
void Nonce__init(unsigned char nonce[24], unsigned char *client_pk, unsigned char *server_pk);

/* Blake2b Nonce increment */
void Nonce__increment(unsigned char nonce[24]);

/* Pepper Decryption implementation */
void PepperCrypto__decrypt(const int16_t id, unsigned char *payload, uint32_t payloadLen);

/* Pepper Encryption implementation */
void PepperCrypto__encrypt(const int16_t id, unsigned char *payload, uint32_t payloadLen);

/* RC4 Crypto initialization */
void RC4__init();
/* PepperCrypto initialization */
void PepperCrypto__init();

#endif // !CRYPTO_H
