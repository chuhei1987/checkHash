/*
* Project: checkHash
* Version: 1.0
* Project author: https://github.com/mt1006
* File: utilities.c
*/

#include "checkHash.h"

int64 getFileSize(FILE* file)
{
	fseek(file, 0, SEEK_END);
	#if defined(_WIN32)
	int64 size = _ftelli64(file);
	#elif defined(__linux__)
	int64 size = ftello(file);
	#else
	#error "_ftelli64" or "ftello" not supported
	int64 size = ftell(file);
	#endif
	fseek(file, 0, SEEK_SET);
	return size;
}

void toLowercase(char* input, char* output, int outputSize)
{
	memcpy(output, input, (outputSize - 1) * sizeof(char));
	output[outputSize - 1] = '\0';
	int inputLen = strlen(input);
	int len = inputLen > (outputSize - 1) ? (outputSize - 1) : inputLen;
	for (int i = 0; i < len; i++)
	{
		if (output[i] >= 'A' && output[i] <= 'Z')
		{
			output[i] += ('a' - 'A');
		}
	}
}

void bytesToHex(byte* input, char* output, int inputSize)
{
	static const char numToHex[17] = "0123456789abcdef";
	for (int i = 0; i < inputSize; i++)
	{
		output[i * 2] = numToHex[input[i] >> 4];
		output[i * 2 + 1] = numToHex[input[i] & 0xF];
	}
	output[inputSize * 2] = '\0';
}

int utf8ArraySize(unichar* input, int inputSize)
{
	if (USE_WCHAR)
	{
		int output = 1;
		for (int i = 0; i < inputSize; i++)
		{
			unsigned short ch = (unsigned short)input[i];
			if (ch < 0x80) { output++; }
			else if (ch < 0x800) { output += 2; }
			else { output += 3; }
		}
		return output;
	}
	else
	{
		return inputSize + 1;
	}
}

void unicharArrayToUTF8(unichar* input, char* output, int inputSize)
{
	if (USE_WCHAR)
	{
		int p = 0;
		for (int i = 0; i < inputSize; i++)
		{
			unsigned short ch = (unsigned short)input[i];
			if (ch < 0x80)
			{
				output[p] = (char)ch;
				p++;
			}
			else if (ch < 0x800)
			{
				output[p] = (ch >> 6) | 0xC0;
				output[p + 1] = (ch & 0x3F) | 0x80;
				p += 2;
			}
			else
			{
				output[p] = (ch >> 12) | 0xE0;
				output[p + 1] = ((ch >> 6) & 0x3F) | 0x80;
				output[p + 2] = (ch & 0x3F) | 0x80;
				p += 3;
			}
		}
		output[p] = '\0';
	}
	else
	{
		memcpy(output, input, inputSize + 1);
	}
}

char* toUTF8(unichar* input, int inputLen)
{
	if (USE_WCHAR)
	{
		int outputStrSize = utf8ArraySize(input, inputLen);
		char* output = (char*)malloc(outputStrSize * sizeof(char));
		unicharArrayToUTF8(input, output, inputLen);
		return output;
	}
	else
	{
		return input;
	}
}

int isHex(unichar* input, int inputLen)
{
	int len = uc_strlen(input);
	for (int i = 0; i < len; i++)
	{
		if ((input[i] < uc('0') || input[i] > uc('9')) &&
			(input[i] < uc('A') || input[i] > uc('F')) &&
			(input[i] < uc('a') || input[i] > uc('f')))
		{
			return 0;
		}
	}
	return 1;
}

HashFunction detectHashFunction(unichar* input)
{
	int len = uc_strlen(input);
	if (isHex(input, len))
	{
		if (len == lenForHF(HF_SHA256) * 2) { return HF_SHA256; }
		else if (len == lenForHF(HF_SHA224) * 2) { return HF_SHA224; }
		else if (len == lenForHF(HF_SHA384) * 2) { return HF_SHA384; }
		else if (len == lenForHF(HF_SHA512) * 2) { return HF_SHA512; }
		else if (len == lenForHF(HF_SHA1) * 2) { return HF_SHA1; }
		else if (len == lenForHF(HF_MD5) * 2) { return HF_MD5; }
	}
	return HF_DEFAULT;
}