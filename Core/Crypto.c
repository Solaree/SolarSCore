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
PepperKey Pepper;

size_t ustrlen(
    const unsigned char *data
)
{
    size_t length = 0;
    while (data[length] != '\0')
    {
        ++length;
    }
    return length;
}

void urandom(
    unsigned char *buf,
    size_t size
)
{
#ifdef __linux__    /* We dont use '__unix__',
                        because function uses only Linux kerenel device system */
    int32_t randomData = open("/dev/urandom", O_RDONLY);

    if (randomData < 0)
    {
        perror("[!] Failed to open /dev/urandom");
        exit(EXIT_FAILURE);
    }

    ssize_t result = read(randomData, buf, size);

    if (result < 0)
    {
        perror("[!] Failed to read from /dev/urandom");
        close(randomData);
        exit(EXIT_FAILURE);
    }
    close(randomData);
#elif defined(_WIN32)
    HCRYPTPROV hCryptProv;
    if (!CryptAcquireContext(&hCryptProv, NULL, NULL, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT))
    {
        fprintf(stderr, "[!] Failed to acquire cryptograhic context\n");
        exit(EXIT_FAILURE);
    }

    if (!CryptGenRandom(hCryptProv, (DWORD)size, buf))
    {
        fprintf(stderr, "[!] Failed to generate random data\n");
        CryptReleaseContext(hCryptProv, 0);
        exit(EXIT_FAILURE);
    }

    CryptReleaseContext(hCryptProv, 0);
#endif
}

void RC4__swap(
    unsigned char *a,
    unsigned char *b
)
{
    int32_t tmp = *a;
    *a = *b;
    *b = tmp;
}

int32_t RC4__KSA(
    unsigned char *S
) 
{
    int32_t len = ustrlen(RC4.key);
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

int32_t RC4__PRGA(
    unsigned char *S,
    unsigned char *plaintext,
    unsigned char *ciphertext
)
{
    int32_t i = 0;
    int32_t j = 0;

    for (size_t n = 0, len = ustrlen(plaintext); n < len; n++)
    {
        i = (i + 1) % N;
        j = (j + S[i]) % N;

        RC4__swap(&S[i], &S[j]);
        int32_t rnd = S[(S[i] + S[j]) % N];

        ciphertext[n] = rnd ^ plaintext[n];
    }
    return EXIT_SUCCESS;
}

int32_t RC4__encrypt(
    unsigned char *plaintext,
    unsigned char *ciphertext
)
{
    unsigned char S[N];

    RC4__KSA(S);
    RC4__PRGA(S, plaintext, ciphertext);
    return EXIT_SUCCESS;
}

void Nonce__init(
    unsigned char *clientKey,
    unsigned char *serverKey
)
{
    if (!clientKey)
    {
        if (!&Pepper.nonce )
            urandom(Pepper.nonce.nonce, 24);
    }
    else
    {
        blake2b_state hash;

        blake2b_Init(&hash, 24);

        if (&Pepper.nonce)
            blake2b_Update(&hash, Pepper.nonce.nonce, 24);
        blake2b_Update(&hash, clientKey, ustrlen(clientKey));
        blake2b_Update(&hash, serverKey, ustrlen(serverKey));

        blake2b_Final(&hash, Pepper.nonce.nonce, 24);
    }
}

void Nonce__increment(

) 
{
    uint64_t *value = (uint64_t*)Pepper.nonce.nonce;
    *value += 2;
}

void PepperCrypto__decrypt(
    const int16_t id,
    unsigned char *payload
)
{
    size_t payloadlen = ustrlen(payload);

    if (id == 10101 && id != 10100)
    {
        memcpy(Pepper.client_public_key, payload, 32);
        payload += 32;
        payloadlen -= 32;

        crypto_scalarmult_curve25519_tweet_base(Pepper.server_public_key, Pepper.server_private_key);

        Nonce__init(Pepper.client_public_key, Pepper.server_public_key);

        crypto_box_curve25519xsalsa20poly1305_tweet_beforenm(Pepper.s, Pepper.client_public_key, Pepper.server_private_key);

        uint8_t temp[56];
        memcpy(temp, Pepper.encryptNonce.nonce, 24);
        memcpy(temp + 24, payload, payloadlen);
        
        uint8_t decrypted[56];
        crypto_secretbox_xsalsa20poly1305_tweet_open(decrypted, temp, 56, Pepper.encryptNonce.nonce, Pepper.s);
        
        memcpy(Pepper.decryptNonce.nonce, decrypted + 24, 24);
    }
    else if (&Pepper.decryptNonce)
    {
        Nonce__increment();

        uint8_t temp[56];
        memcpy(temp, Pepper.decryptNonce.nonce, 24);
        memcpy(temp + 24, payload, payloadlen);
        
        uint8_t decrypted[56];
        crypto_secretbox_xsalsa20poly1305_tweet_open(decrypted, temp, 56, Pepper.decryptNonce.nonce, Pepper.shared_encryption_key);

        memcpy(payload, decrypted, payloadlen);
    }
}

void PepperCrypto__encrypt(
    const int16_t id,
    unsigned char *payload
)
{
    if (id == 20104 && id != 20100 && id != 20103)
    {
        Nonce__init(0, 0);
        Nonce__increment();

        unsigned char temp[64];
        memcpy(temp, Pepper.nonce.nonce, 24);
        memcpy(temp + 24, Pepper.shared_encryption_key, 32);
        memcpy(temp + 56, payload, ustrlen(payload));

        unsigned char encrypted[16];
        crypto_secretbox_xsalsa20poly1305(encrypted, temp, 64, Pepper.nonce.nonce, Pepper.s);

        memcpy(payload, encrypted, 16);
    }
    else if (id != 20100 && id != 20103)
    {
        Nonce__increment();

        unsigned char temp[56];
        memcpy(temp, Pepper.nonce.nonce, 24);
        memcpy(temp + 24, payload, ustrlen(payload));

        unsigned char encrypted[16];
        crypto_secretbox_xsalsa20poly1305(encrypted, temp, 56, Pepper.nonce.nonce, Pepper.shared_encryption_key);

        memcpy(payload, encrypted, 16);
    }
}

void PepperCrypto__generate_random(

)
{
    urandom(Pepper.shared_encryption_key, 32);
}

void Crypto__init(

)
{
    unsigned char RC4__key[] = "fhsd6f86f67rt8fw78fw789we78r9789wer6re";
    unsigned char RC4__nonce[] = "nonce";

    memcpy(RC4.key, RC4__key, ustrlen(RC4__key));
    memcpy(RC4.nonce, RC4__nonce, ustrlen(RC4__nonce));

    unsigned char PepperCrypto__server_private_key[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    memcpy(Pepper.server_private_key, PepperCrypto__server_private_key, ustrlen(PepperCrypto__server_private_key));

    PepperCrypto__generate_random(); // PepperCrypto__shared_encryption_key

    unsigned char PepperCrypto__s[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    memcpy(Pepper.s, PepperCrypto__s, ustrlen(PepperCrypto__s));
}
