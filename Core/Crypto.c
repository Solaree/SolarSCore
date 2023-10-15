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

#include "include/Core/Crypto.h"

ARC4 RC4;
PepperInit Pepper;

void RC4__swap(unsigned char *a, unsigned char *b)
{
    int32_t tmp = *a;
    *a = *b;
    *b = tmp;
}

int32_t RC4__KSA(unsigned char *S)
{
    int32_t len = strlen((const char*)RC4.key);
    int32_t j = 0;

    for (int32_t i = 0; i < N; i++)
        S[i] = i;

    for (int32_t i = 0; i < N; i++)
    {
        j = (j + S[i] + RC4.key[i % len] + RC4.nonce[i % 5]) % N;
        RC4__swap(&S[i], &S[j]);
    }
    return EXIT_SUCCESS;
}

int32_t RC4__PRGA(unsigned char *S, unsigned char *plaintext, unsigned char *ciphertext)
{
    int32_t i = 0;
    int32_t j = 0;

    for (size_t n = 0, len = strlen((const char*)plaintext); n < len; n++)
    {
        i = (i + 1) % N;
        j = (j + S[i]) % N;

        RC4__swap(&S[i], &S[j]);
        int32_t rnd = S[(S[i] + S[j]) % N];

        ciphertext[n] = rnd ^ plaintext[n];
    }
    return EXIT_SUCCESS;
}

int32_t RC4__encrypt(unsigned char *plaintext, unsigned char *ciphertext)
{
    unsigned char S[N];

    RC4__KSA(S);
    RC4__PRGA(S, plaintext, ciphertext);
    return EXIT_SUCCESS;
}

void Nonce__init(unsigned char nonce[24], unsigned char *client_pk, unsigned char *server_pk)
{
    if (client_pk == NULL)
    {
        randombytes(nonce, crypto_box_NONCEBYTES);
    }
    else
    {
        crypto_generichash_blake2b_state hash;

        crypto_generichash_blake2b_init(&hash, NULL, 0, 24);

        if (nonce != NULL)
            crypto_generichash_blake2b_update(&hash, nonce, 24);
        crypto_generichash_blake2b_update(&hash, client_pk, 32);
        crypto_generichash_blake2b_update(&hash, server_pk, 32);

        crypto_generichash_blake2b_final(&hash, nonce, 24);
    }
}

void Nonce__increment(unsigned char nonce[24])
{
    uint64_t nonceVal = 0;

    for (size_t i = 0; i < 24; ++i)
        nonceVal |= ((uint64_t)nonce[i]) << (8 * i);

    nonceVal += 2;

    for (size_t i = 0; i < 24; ++i) {
        nonce[i] = (uint8_t)(nonceVal & 0xFF);
        nonceVal >>= 8;
    }
}

void PepperCrypto__decrypt(const int16_t id, unsigned char *payload, uint32_t payloadLen)
{
    if (id == 10101 && id != 10100)
    {
        memcpy(Pepper.client_public_key, payload, 32);
        payload += 32;
        payloadLen -= 32;

        if (crypto_scalarmult_curve25519_base(Pepper.server_public_key, Pepper.server_private_key) == EXIT_SUCCESS) {
            unsigned char nonce[24];
            Nonce__init(nonce, Pepper.client_public_key, Pepper.server_public_key);

            if (crypto_box_curve25519xsalsa20poly1305_beforenm(Pepper.s, Pepper.client_public_key, Pepper.server_private_key) == EXIT_SUCCESS) {
                unsigned char temp_payload[payloadLen + 16];

                memset(temp_payload, 0, 16);
                memcpy(temp_payload + 16, payload, payloadLen);

                unsigned char decrypted[sizeof(temp_payload)];

                if (crypto_secretbox_xsalsa20poly1305_open(decrypted, temp_payload, sizeof(temp_payload), nonce, Pepper.s) == EXIT_SUCCESS) {;
                    unsigned char *decrypted_ptr = decrypted + 32;

                    memcpy(Pepper.decryptNonce, decrypted_ptr + 24, 24);
                    Nonce__init(Pepper.decryptNonce, NULL, NULL);

                    payload = decrypted_ptr + 48;
                }
            }
        };
    }
    else if (Pepper.decryptNonce == NULL)
    {
        payload = payload;
    }
    else
    {
        Nonce__increment(Pepper.decryptNonce);

        unsigned char temp_payload[payloadLen + 16];

        memset(temp_payload, 0, 16);
        memcpy(temp_payload + 16, payload, payloadLen);

        unsigned char decrypted[sizeof(temp_payload)];

        if (crypto_secretbox_xsalsa20poly1305_open(decrypted, temp_payload, sizeof(temp_payload), Pepper.decryptNonce, Pepper.shared_encryption_key) == 0)
            memcpy(payload, decrypted + 32, sizeof(decrypted) - 32);
    }
}

void PepperCrypto__encrypt(const int16_t id, unsigned char *payload, uint32_t payloadLen)
{
    if (id == 20104 && id != 20100 && id != 20103)
    {
        Nonce__init(Pepper.decryptNonce, Pepper.client_public_key, Pepper.server_public_key);

        unsigned char temp_payload[payloadLen + 56];

        memcpy(temp_payload, Pepper.encryptNonce, 24);
        memcpy(temp_payload + 24, Pepper.shared_encryption_key, 32);
        memcpy(temp_payload + 56, payload, payloadLen);

        unsigned char padded_payload[sizeof(temp_payload) + 32];

        memset(padded_payload, 0, 32);
        memcpy(padded_payload + 32, temp_payload, sizeof(temp_payload));

        unsigned char encrypted[sizeof(padded_payload)];

        if (crypto_secretbox_xsalsa20poly1305(encrypted, padded_payload, sizeof(padded_payload), Pepper.decryptNonce, Pepper.s))
            memcpy(payload, encrypted + 16, sizeof(encrypted) - 16);
    }
    else if (id != 20100 && id != 20103)
    {
        Nonce__increment(Pepper.encryptNonce);

        unsigned char padded_payload[payloadLen + 32];
        memset(padded_payload, 0, 32);
        memcpy(padded_payload + 32, payload, payloadLen);

        unsigned char encrypted[sizeof(padded_payload)];

        if (crypto_secretbox_xsalsa20poly1305(encrypted, padded_payload, sizeof(padded_payload), Pepper.nonce, Pepper.shared_encryption_key))
            memcpy(payload, encrypted + 16, sizeof(encrypted) - 16);
    }
}

void PepperCrypto__generate_random()
{
    randombytes(Pepper.shared_encryption_key, 32);
}

void RC4__init() {
    unsigned char RC4__key[38] = "fhsd6f86f67rt8fw78fw789we78r9789wer6re";
    unsigned char RC4__nonce[5] = "nonce";

    memcpy(RC4.key, RC4__key, sizeof(RC4__key));
    memcpy(RC4.nonce, RC4__nonce, sizeof(RC4__nonce));
}

void PepperCrypto__init()
{
    unsigned char PepperCrypto__server_private_key[32] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    memcpy(Pepper.server_private_key, PepperCrypto__server_private_key, 32);

    PepperCrypto__generate_random(); // PepperCrypto__shared_encryption_key

    Nonce__init(Pepper.encryptNonce, NULL, NULL);

    Pepper.decryptNonce = NULL;

    unsigned char PepperCrypto__s[32] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    memcpy(Pepper.s, PepperCrypto__s, 32);
}
