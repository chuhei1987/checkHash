/*
* Project: checkHash
* Version: 1.0
* Project author: https://github.com/mt1006
* File: errors.c
*/

#include "checkHash.h"

void syntaxError(void)
{
	if (*_simpleOutput)
	{
		puts("-1");
	}
	else
	{
		puts("#Invalid syntax!");
		puts("#Usage: ch [options] [filename] [hash / filename / filenames...]");
		puts("#See \"ch -h\"");
	}
	exit(1);
}

void fileError(unichar* fileName, int errorCode)
{
	if (*_simpleOutput)
	{
		puts("-2");
	}
	else
	{
		puts("#Failed to open the file!");
		fputs("#Filename: ", stdout);
		uc_puts(fileName);
		printf("#Error code: %d [%s]\n", errorCode, strerror(errorCode));
	}
	exit(2);
}

void unknownHashFunction(void)
{
	if (*_simpleOutput)
	{
		puts("-3");
	}
	else
	{
		puts("#Unknown hash function!");
		puts("#Use \"ch -f\" to get list of all available hash functions.");
	}
	exit(3);
}

void invalidHash(void)
{
	if (*_simpleOutput)
	{
		puts("-4");
	}
	else
	{
		puts("#Invalid hash!");
	}
	exit(4);
}

void programError(char* file, int line)
{
	if (*_simpleOutput)
	{
		puts("-5");
	}
	else
	{
		puts("#Something went wrong...");
		puts("#This is program error\n");
		puts("#Error details:");
		printf("#checkHash version: %s\n", CH_VERSION);
		printf("#file: %s\n", file);
		printf("#line: %d\n", line);
		fputs("#arguments: ", stdout);
		for (int i = 1; i < g_argc; i++)
		{
			uc_fputs(g_argv[i], stdout);
		}
		puts("");
	}
	exit(5);
}