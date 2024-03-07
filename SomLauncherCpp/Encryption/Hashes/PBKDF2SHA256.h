#ifndef PBKDF2SHA256_H_
#define PBKDF2SHA256_H_

#include <qbytearray.h>

#include <string>
#include <stdio.h>
#include <stdint.h>

#include <openssl/sha.h>
#include <openssl/evp.h>
#include <openssl/crypto.h>
#include <openssl/bio.h>
#include <openssl/buffer.h>

void PBKDF2_HMAC_SHA_256(const char* pass, const unsigned char* salt, int32_t iterations, uint32_t outputBytes, char* hexResult, uint8_t* binResult);

QByteArray PBKDF2_SHA256_DJANGO(const std::string& password,
	const std::string& input_salt, int iterations = 390000, size_t count_symbols = 32);

#endif // !PBKDF2SHA256_H_