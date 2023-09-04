/*
* Project: checkHash
* Version: 1.0.1
* Project author: https://github.com/chuhei1987/checkHash
* File: operations.c
*/

#include "checkHash.h"

const int maxHashLen = 2049;

void arrayHash(byte* input, char* output, int64 inputSize, HashFunction hashFunction)
{
	if (isOpenSSLhf(hashFunction))
	{
		int outputLen;
		int hashLen = lenForHF(hashFunction);
		const EVP_MD* function = pointerToOpenSSLhf(hashFunction);
		byte* hashArray = (byte*)malloc(hashLen * sizeof(byte));
		EVP_MD_CTX* context = EVP_MD_CTX_new();
		EVP_DigestInit_ex(context, function, NULL);
		EVP_DigestUpdate(context, input, inputSize);
		EVP_DigestFinal_ex(context, hashArray, &outputLen);
		if (hashLen != outputLen) { programError("operations.c", __LINE__); }
		EVP_MD_CTX_destroy(context);
		bytesToHex(hashArray, output, hashLen);
	}
	else
	{
		pointerToHF(hashFunction)(input, output, inputSize);
	}
}

void fileHash(unichar* fileName, char* output, HashFunction hashFunction)
{
	FILE* file = uc_fopen(fileName, uc("rb"));
	if (!file) { fileError(fileName, errno); }
	int64 fileSize = getFileSize(file);
	byte* buffer = (byte*)malloc(fileSize * sizeof(byte));
	int64 read = fread(buffer, sizeof(byte), fileSize, file);
	if (read != fileSize * sizeof(byte)) { fileError(fileName, errno); }
	arrayHash(buffer, output, fileSize, hashFunction);
	free(buffer);
}

void compare(OperationInput operationInput)
{
	if (operationInput.argumentsCount == 1)
	{
		getHash(operationInput);
	}
	else if (operationInput.argumentsCount == 2)
	{
		HashFunction detectedHF = detectHashFunction(operationInput.argv[operationInput.inputFirst + 1]);
		if (detectedHF == HF_DEFAULT)
		{
			compareFiles(operationInput);
		}
		else
		{
			if (operationInput.hashFunction == HF_DEFAULT)
			{
				operationInput.hashFunction = detectedHF;
			}
			compareToHash(operationInput);
		}
	}
	else
	{
		syntaxError();
	}
}

void getHash(OperationInput operationInput)
{
	if (!operationInput.inputFirst) { syntaxError(); }
	if (operationInput.hashFunction == HF_DEFAULT) { operationInput.hashFunction = CH_DEFAULT_HASH_FUNCTION; }
	int hashStrLen = lenForHF(operationInput.hashFunction) * 2 + 1;
	char* hash = (char*)malloc(hashStrLen * sizeof(char));
	for (int i = operationInput.inputFirst; i <= operationInput.inputLast; i++)
	{
		fileHash(operationInput.argv[i], hash, operationInput.hashFunction);
		if (operationInput.simpleOutput)
		{
			puts(hash);
		}
		else
		{
			printf("file_%s(\"", strForHF(operationInput.hashFunction));
			uc_fputs(operationInput.argv[i], stdout);
			printf("\") = %s\n", hash);
		}
	}
	free(hash);
}

void stringHash(OperationInput operationInput)
{
	if (!operationInput.inputFirst) { syntaxError(); }
	if (operationInput.hashFunction == HF_DEFAULT) { operationInput.hashFunction = CH_DEFAULT_HASH_FUNCTION; }
	int hashStrLen = lenForHF(operationInput.hashFunction) * 2 + 1;
	char* hash = (char*)malloc(hashStrLen * sizeof(char));
	for (int i = operationInput.inputFirst; i <= operationInput.inputLast; i++)
	{
		int strLen = uc_strlen(operationInput.argv[i]);
		char* str = toUTF8(operationInput.argv[i], strLen);
		if (USE_WCHAR) { strLen = strlen(str); }
		arrayHash((byte*)str, hash, strLen, operationInput.hashFunction);
		if (operationInput.simpleOutput)
		{
			puts(hash);
		}
		else
		{
			printf("%s(\"", strForHF(operationInput.hashFunction));
			uc_fputs(operationInput.argv[i], stdout);
			printf("\") = %s\n", hash);
		}
		if (USE_WCHAR) { free(str); }
	}
	free(hash);
}

void compareFiles(OperationInput operationInput)
{
	if (!operationInput.inputFirst) { syntaxError(); }
	if (operationInput.hashFunction == HF_DEFAULT) { operationInput.hashFunction = CH_DEFAULT_HASH_FUNCTION; }
	int hashStrLen = lenForHF(operationInput.hashFunction) * 2 + 1;
	int equal = 1;
	char* firstHash = (char*)malloc(hashStrLen * sizeof(char));
	char* hash = (char*)malloc(hashStrLen * sizeof(char));
	for (int i = operationInput.inputFirst; i <= operationInput.inputLast; i++)
	{
		fileHash(operationInput.argv[i], hash, operationInput.hashFunction);
		if (!operationInput.simpleOutput)
		{
			printf("file_%s(\"", strForHF(operationInput.hashFunction));
			uc_fputs(operationInput.argv[i], stdout);
			printf("\") = %s\n", hash);
		}
		if (i == operationInput.inputFirst) { memcpy(firstHash, hash, hashStrLen * sizeof(char)); }
		else { equal &= !strcmp(hash, firstHash); }
	}
	if (operationInput.simpleOutput) { printf("%d\n", equal); }
	else if (equal) { puts("[EQUAL]"); }
	else { puts("[NOT EQUAL]"); }
	free(firstHash);
	free(hash);
}


void compareToHash(OperationInput operationInput)
{
	if (operationInput.inputLast - operationInput.inputFirst != 1) { syntaxError(); }
	if (operationInput.hashFunction == HF_DEFAULT) { operationInput.hashFunction = CH_DEFAULT_HASH_FUNCTION; }
	unichar* inputFile = operationInput.argv[operationInput.inputFirst];
	unichar* inputHash = operationInput.argv[operationInput.inputLast];
	int hashLen = lenForHF(operationInput.hashFunction) * 2 + 1;
	int inputHashLen = uc_strlen(inputHash) + 1;
	if (!isHex(inputHash, inputHashLen - 1) || hashLen != inputHashLen) { invalidHash(); }
	char* hash = (char*)malloc(hashLen * sizeof(char));
	char* charInputHash = toUTF8(inputHash, inputHashLen - 1);
	char* lowercaseInputHash = (char*)malloc(inputHashLen * sizeof(char));
	toLowercase(charInputHash, lowercaseInputHash, strlen(charInputHash) + 1);
	fileHash(inputFile, hash, operationInput.hashFunction);
	if (!operationInput.simpleOutput)
	{
		printf("file_%s(\"", strForHF(operationInput.hashFunction));
		uc_fputs(inputFile, stdout);
		printf("\") = %s\n", hash);
	}
	int equal = !strcmp(hash, lowercaseInputHash);
	if (operationInput.simpleOutput) { printf("%d\n", equal); }
	else if (equal) { puts("[EQUAL]"); }
	else { puts("[NOT EQUAL]"); }
	if (USE_WCHAR) { free(charInputHash); }
	free(hash);
	free(lowercaseInputHash);
}