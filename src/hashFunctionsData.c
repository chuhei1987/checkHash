/*
* Project: checkHash
* Version: 1.0
* Project author: https://github.com/mt1006
* File: hashFunctionsData.c
*/

#include "checkHash.h"

int lenForHF(HashFunction hashFunction)
{
	if (hashFunction == HF_SHA1) { return 160 / 8; }
	else if (hashFunction == HF_SHA224) { return 224 / 8; }
	else if (hashFunction == HF_SHA256) { return 256 / 8; }
	else if (hashFunction == HF_SHA384) { return 384 / 8; }
	else if (hashFunction == HF_SHA512) { return 512 / 8; }
	else if (hashFunction == HF_SHA512_224) { return 224 / 8; }
	else if (hashFunction == HF_SHA512_256) { return 256 / 8; }
	else if (hashFunction == HF_SHA3_224) { return 224 / 8; }
	else if (hashFunction == HF_SHA3_256) { return 256 / 8; }
	else if (hashFunction == HF_SHA3_384) { return 384 / 8; }
	else if (hashFunction == HF_SHA3_512) { return 512 / 8; }
	else if (hashFunction == HF_MD4) { return 128 / 8; }
	else if (hashFunction == HF_MD5) { return 128 / 8; }
	else if (hashFunction == HF_BLAKE2b512) { return 512 / 8; }
	else if (hashFunction == HF_BLAKE2s256) { return 256 / 8; }
	else if (hashFunction == HF_RIPEMD160) { return 160 / 8; }
	else if (hashFunction == HF_WHIRLPOOL) { return 512 / 8; }
	else if (hashFunction == HF_SM3) { return 256 / 8; }
	else { programError("hashFunctionsData.c", __LINE__); }
}

char* strForHF(HashFunction hashFunction)
{
	if (hashFunction == HF_SHA1) { return "sha1"; }
	else if (hashFunction == HF_SHA224) { return "sha224"; }
	else if (hashFunction == HF_SHA256) { return "sha256"; }
	else if (hashFunction == HF_SHA384) { return "sha384"; }
	else if (hashFunction == HF_SHA512) { return "sha512"; }
	else if (hashFunction == HF_SHA512_224) { return "sha512/224"; }
	else if (hashFunction == HF_SHA512_256) { return "sha512/256"; }
	else if (hashFunction == HF_SHA3_224) { return "sha3-224"; }
	else if (hashFunction == HF_SHA3_256) { return "sha3-256"; }
	else if (hashFunction == HF_SHA3_384) { return "sha3-384"; }
	else if (hashFunction == HF_SHA3_512) { return "sha3-512"; }
	else if (hashFunction == HF_MD4) { return "md4"; }
	else if (hashFunction == HF_MD5) { return "md5"; }
	else if (hashFunction == HF_BLAKE2b512) { return "BLAKE2b-512"; }
	else if (hashFunction == HF_BLAKE2s256) { return "BLAKE2s-256"; }
	else if (hashFunction == HF_RIPEMD160) { return "ripemd160"; }
	else if (hashFunction == HF_WHIRLPOOL) { return "whirlpool"; }
	else if (hashFunction == HF_SM3) { return "sm3"; }
	else { programError("hashFunctionsData.c", __LINE__); }
}

PointerToHF pointerToHF(HashFunction hashFunction)
{
	programError("hashFunctionsData.c", __LINE__);
	return NULL;
}

const EVP_MD* pointerToOpenSSLhf(HashFunction hashFunction)
{
	if (hashFunction == HF_SHA1) { return EVP_sha1(); }
	else if (hashFunction == HF_SHA224) { return EVP_sha224(); }
	else if (hashFunction == HF_SHA256) { return EVP_sha256(); }
	else if (hashFunction == HF_SHA384) { return EVP_sha384(); }
	else if (hashFunction == HF_SHA512) { return EVP_sha512(); }
	else if (hashFunction == HF_SHA512_224) { return EVP_sha512_224(); }
	else if (hashFunction == HF_SHA512_256) { return EVP_sha512_256(); }
	else if (hashFunction == HF_SHA3_224) { return EVP_sha3_224(); }
	else if (hashFunction == HF_SHA3_256) { return EVP_sha3_256();; }
	else if (hashFunction == HF_SHA3_384) { return EVP_sha3_384(); }
	else if (hashFunction == HF_SHA3_512) { return EVP_sha3_512(); }
	else if (hashFunction == HF_MD4) { return EVP_md4(); }
	else if (hashFunction == HF_MD5) { return EVP_md5(); }
	else if (hashFunction == HF_BLAKE2b512) { return EVP_blake2b512(); }
	else if (hashFunction == HF_BLAKE2s256) { return EVP_blake2s256(); }
	else if (hashFunction == HF_RIPEMD160) { return EVP_ripemd160(); }
	else if (hashFunction == HF_WHIRLPOOL) { return EVP_whirlpool(); }
	else if (hashFunction == HF_SM3) { return EVP_sm3(); }
	else { programError("hashFunctionsData.c", __LINE__); }
}

int isOpenSSLhf(HashFunction hashFunction)
{
	return 1;
}

HashFunction hfFromStr(char* input, int inputLen)
{
	char str[32];
	toLowercase(input, str, 32);
	if (!strcmp(str, "sha1")) { return HF_SHA1; }
	else if (!strcmp(str, "sha-224") || !strcmp(str, "sha224")) { return HF_SHA224; }
	else if (!strcmp(str, "sha-256") || !strcmp(str, "sha256")) { return HF_SHA256; }
	else if (!strcmp(str, "sha-384") || !strcmp(str, "sha384")) { return HF_SHA384; }
	else if (!strcmp(str, "sha-512") || !strcmp(str, "sha512")) { return HF_SHA512; }
	else if (!strcmp(str, "sha-512/224") || !strcmp(str, "sha512/224")) { return HF_SHA512_224; }
	else if (!strcmp(str, "sha-512/256") || !strcmp(str, "sha512/256")) { return HF_SHA512_256; }
	else if (!strcmp(str, "sha3-224")) { return HF_SHA3_224; }
	else if (!strcmp(str, "sha3-256")) { return HF_SHA3_256; }
	else if (!strcmp(str, "sha3-384")) { return HF_SHA3_384; }
	else if (!strcmp(str, "sha3-512")) { return HF_SHA3_512; }
	else if (!strcmp(str, "md4")) { return HF_MD4; }
	else if (!strcmp(str, "md5")) { return HF_MD5; }
	else if (!strcmp(str, "blake2b-512") || !strcmp(str, "blake2b512")) { return HF_BLAKE2b512; }
	else if (!strcmp(str, "blake2s-256") || !strcmp(str, "blake2s256")) { return HF_BLAKE2s256; }
	else if (!strcmp(str, "ripemd-160") || !strcmp(str, "ripemd160")) { return HF_RIPEMD160; }
	else if (!strcmp(str, "whirlpool") || !strcmp(str, "whpl")) { return HF_WHIRLPOOL; }
	else if (!strcmp(str, "sm3")) { return HF_SM3; }
	else { unknownHashFunction(); }
}