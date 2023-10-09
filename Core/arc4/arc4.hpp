/*
* arc4.hpp - The SolarSCore
* Copyright (C) 2016 drFabio
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

#include <cstdint>

#ifndef ARC4_HPP
#define ARC4_HPP
 /**
 * RC4 Encryptor utility for decrypting Strings
 * @brief Utility to RC4 encrypt bytes
 */
class ARC4 {
public:
    /**
    * Set/Reset the key use this method if you want to reuse the same ARC4 structure again
    * @param k the key
    * @param size the size of the key
    */
    void setKey(unsigned char *k, int32_t size);
    /**
    * Encrypts a string
    * @param in String to encrypt
    * @param out String to decrypt
    * @param size size of the key to encrypt
    */
    void encrypt(unsigned char *in, unsigned char *out, int32_t size);
    /**
    * Encrypts a string
    * @param in String to encrypt
    * @param out String to decrypt
    * @param size size of the key to encrypt
    */
    void encrypt(char *in, char *out, int32_t size);
protected:
    void ksa(unsigned char *key);
    void swap(unsigned char data[], int32_t i, int32_t j);
    void prga(unsigned char *plaintext, unsigned char *cipher, int32_t size);
    void prga(char *plaintext, char *cipher, int32_t size);

    unsigned char sbox[256];
    int32_t sizeKey, prgaIndexA, prgaIndexB;
};
#endif // !ARC4_HPP