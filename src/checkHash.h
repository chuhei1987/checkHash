/*
* Project: checkHash
* Version: 1.0.a
* Project author: https://github.com/chuhei1987/checkHash
* File: checkHash.h
*/
#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define _FILE_OFFSET_BITS 64

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <errno.h>
#include <openssl/evp.h>

#if defined(_WIN32)
#include <Windows.h>
#define CH_OS "Windows"
#elif defined(__linux__)
#define CH_OS "Linux"
#else
#define CH_OS "[unknown]"
#endif

#if defined(__x86_64__) || defined(_M_AMD64)
#define CH_CPU "AMD64"
#elif defined(__i386__) || defined(_M_IX86)
#define CH_CPU "IA-32"
#else
#define CH_CPU "[unknown]"
#endif

#define CH_VERSION "1.0.A"
#define CH_DEFAULT_OPERATION COMPARE
#define CH_DEFAULT_HASH_FUNCTION HF_SHA3_256 //Based on principle of non repeatable rule. 
#define TO_STR(x) #x
#define DEF_TO_STR(x) TO_STR(x)

typedef unsigned char byte;
typedef long long int64;
typedef void(*PointerToHF)(byte* input, char* output, int64 inputSize);

#ifdef _WIN32

#define USE_WCHAR 1
typedef wchar_t unichar;
#define uc(str) L##str
#define uc_strlen wcslen
#define uc_fopen _wfopen
#define uc_puts _putws
#define uc_fputs fputws

#else

#define USE_WCHAR 0
typedef char unichar;
#define uc(str) str
#define uc_strlen strlen
#define uc_fopen fopen
#define uc_puts puts
#define uc_fputs fputs

#endif

typedef enum
{
	NONE,
	COMPARE,
	GET_HASH,
	STRING_HASH,
	COMPARE_FILES,
	COMPARE_TO_HASH,
	SET_FUNCTION,
	SIMPLE_OUTPUT,
	INFORMATION,
	FULL_INFO,
	VERSION,
	HELP
} Option;

typedef enum
{
	NO_INPUT,
	OPERATION_INPUT,
	SF_INPUT
} ExpectedInput;

typedef enum
{
	HF_DEFAULT,
	//HF_SHA1,
	//HF_SHA224,
	//HF_SHA256,
	//HF_SHA384,
	//HF_SHA512,
	//HF_SHA512_224,
	//HF_SHA512_256,
	//HF_SHA3_224,
	HF_SHA3_256,
	HF_SHA3_384,
	HF_SHA3_512,
	//HF_MD4,
	//HF_MD5,
	//HF_BLAKE2b512,
	//HF_BLAKE2s256,
	//HF_RIPEMD160,
	//HF_WHIRLPOOL,
	//HF_SM3
} HashFunction;

typedef struct
{
	unichar** argv;
	int inputFirst;
	int inputLast;
	int argumentsCount;
	int simpleOutput;
	HashFunction hashFunction;
} OperationInput;

extern int g_argc;
extern unichar** g_argv;
extern int* _simpleOutput;

void syntaxError(void);
void fileError(unichar* fileName, int errorCode);
void unknownHashFunction(void);
void invalidHash(void);
void programError(char* file, int line);

int64 getFileSize(FILE* file);
void toLowercase(char* input, char* output, int outputSize);
void bytesToHex(byte* input, char* output, int inputSize);
int utf8ArraySize(unichar* input, int inputSize);
void unicharArrayToUTF8(unichar* input, char* output, int inputSize);
char* toUTF8(unichar* input, int inputLen);
int isHex(unichar* input, int inputLen);
HashFunction detectHashFunction(unichar* input);

int lenForHF(HashFunction hashFunction);
char* strForHF(HashFunction hashFunction);
PointerToHF pointerToHF(HashFunction hashFunction);
const EVP_MD* pointerToOpenSSLhf(HashFunction hashFunction);
int isOpenSSLhf(HashFunction hashFunction);
HashFunction hfFromStr(char* input, int inputLen);

void showHelp(void);
void showInformations(void);
void showFullInfo(void);
void showVersion(void);
void hashFunctionsList(void);

void arrayHash(byte* input, char* output, int64 inputSize, HashFunction hashFunction);
void fileHash(unichar* fileName, char* output, HashFunction hashFunction);
void compare(OperationInput operationInput);
void getHash(OperationInput operationInput);
void stringHash(OperationInput operationInput);
void compareFiles(OperationInput operationInput);
void compareToHash(OperationInput operationInput);