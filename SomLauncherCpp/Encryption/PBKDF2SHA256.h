#ifndef PBKDF2SHA256_H_
#define PBKDF2SHA256_H_

#include <string>
#include <stdio.h>
#include <stdint.h>

#include <openssl/sha.h>
#include <openssl/evp.h>
#include <openssl/crypto.h>
#include <openssl/bio.h>
#include <openssl/buffer.h>

void PBKDF2_HMAC_SHA_256(const char* pass, const unsigned char* salt, int32_t iterations, uint32_t outputBytes, char* hexResult, uint8_t* binResult)
{
	unsigned int i;
	unsigned char* digest = new unsigned char[outputBytes];
	PKCS5_PBKDF2_HMAC(pass, strlen(pass), salt, strlen((const char*)salt), iterations, EVP_sha256(), outputBytes, digest);

	for (i = 0; i < sizeof(digest); ++i)
	{
		//sprintf(hexResult + (i * 2), "%02x", 255 & digest[i]);
		binResult[i] = digest[i];
	};
}

QByteArray PBKDF2_SHA256_DJANGO(const std::string& password, const std::string& input_salt, int iterations = 390000, size_t count_symbols = 32)
{
	// catch success == 0
	//std::unique_ptr<unsigned char[]> result = std::make_unique<unsigned char[]>(count_symbols);
	unsigned char* result = new unsigned char[count_symbols];
	int success = PKCS5_PBKDF2_HMAC(password.c_str(), password.size(), (unsigned char*)input_salt.c_str(), input_salt.size(), iterations, EVP_sha256(), count_symbols, result);

	QByteArray resultBytes((char*)result, count_symbols);

	delete[] result;
	return resultBytes;
}

#endif // !PBKDF2SHA256_H_