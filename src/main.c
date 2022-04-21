/*
* Project: checkHash
* Version: 1.0
* Project author: https://github.com/mt1006
* File: main.c
*/

#include "checkHash.h"

int g_argc;
unichar** g_argv;
int* _simpleOutput;
Option operation = NONE;
ExpectedInput expectedInput = OPERATION_INPUT;
HashFunction hashFunction = HF_DEFAULT;
int operationInputFirst = 0;
int operationInputLast = 0;
int useSimpleOutput = 0;

Option getOption(char* str, int strLen)
{
	if (strLen > 1 && str[0] == '-')
	{
		if (!strcmp(str, "-c") || !strcmp(str, "--compare")) { return COMPARE; }
		else if (!strcmp(str, "-g") || !strcmp(str, "--get-hash")) { return GET_HASH; }
		else if (!strcmp(str, "-s") || !strcmp(str, "--string-hash")) { return STRING_HASH; }
		else if (!strcmp(str, "-cf") || !strcmp(str, "--compare-files")) { return COMPARE_FILES; }
		else if (!strcmp(str, "-ch") || !strcmp(str, "--compare-hashes")) { return COMPARE_TO_HASH; }
		else if (!strcmp(str, "-f") || !strcmp(str, "--hash-function")) { return SET_FUNCTION; }
		else if (!strcmp(str, "-so") || !strcmp(str, "--simple-output")) { return SIMPLE_OUTPUT; }
		else if (!strcmp(str, "-i") || !strcmp(str, "--information")) { return INFORMATION; }
		else if (!strcmp(str, "-fi") || !strcmp(str, "--full-info")) { return FULL_INFO; }
		else if (!strcmp(str, "-v") || !strcmp(str, "--version")) { return VERSION; }
		else if (!strcmp(str, "-h") || !strcmp(str, "-?") || !strcmp(str, "--help")) { return HELP; }
		else { syntaxError(); }
	}
	else if (!strLen) { syntaxError(); }
	else { return NONE; }
}

void argumentParser(int argc, unichar** argv)
{
	for (int i = 1; i < argc; i++)
	{
		int argLen = uc_strlen(argv[i]);
		char* arg = toUTF8(argv[i], argLen);
		Option option = getOption(arg, argLen);
		if (option == NONE)
		{
			if (expectedInput == SF_INPUT)
			{
				if (hashFunction != HF_DEFAULT) { syntaxError(); }
				hashFunction = hfFromStr(arg, argLen);
				expectedInput = OPERATION_INPUT;
			}
			else if (expectedInput == OPERATION_INPUT && !operationInputLast)
			{
				if (!operationInputFirst) { operationInputFirst = i; }
			}
			else
			{
				syntaxError();
			}
		}
		else
		{
			if (expectedInput != NO_INPUT && expectedInput != OPERATION_INPUT) { syntaxError(); }
			if (operationInputFirst && !operationInputLast) { operationInputLast = i - 1; }
			if (option == HELP || option == INFORMATION || option == FULL_INFO || option == VERSION)
			{
				if (argc != 2) { syntaxError(); }
				operation = option;
			}
			else if (option == SET_FUNCTION)
			{
				if (argc == 2) { operation = SET_FUNCTION; }
				else { expectedInput = SF_INPUT; }
			}
			else if (option == SIMPLE_OUTPUT)
			{
				if (useSimpleOutput) { syntaxError(); }
				useSimpleOutput = 1;
			}
			else
			{
				if (operation != NONE || operationInputFirst) { syntaxError(); }
				operation = option;
			}
		}
		if (USE_WCHAR) { free(arg); }
	}
	if (expectedInput != NO_INPUT && expectedInput != OPERATION_INPUT) { syntaxError(); }
	if (operationInputFirst && !operationInputLast) { operationInputLast = argc - 1; }
	if (operation == NONE) { operation = CH_DEFAULT_OPERATION; }
}

void executeOperation(unichar** argv)
{
	OperationInput operationInput;
	operationInput.argv = argv;
	operationInput.inputFirst = operationInputFirst;
	operationInput.inputLast = operationInputLast;
	operationInput.argumentsCount = operationInputLast - operationInputFirst + 1;
	operationInput.simpleOutput = useSimpleOutput;
	operationInput.hashFunction = hashFunction;
	if (operationInput.argumentsCount < 1) { programError("main.c", __LINE__); }
	if (operation == COMPARE) { compare(operationInput); }
	else if (operation == GET_HASH) { getHash(operationInput); }
	else if (operation == STRING_HASH) { stringHash(operationInput); }
	else if (operation == COMPARE_FILES) { compareFiles(operationInput); }
	else if (operation == COMPARE_TO_HASH) { compareToHash(operationInput); }
	else if (operation == SET_FUNCTION) { hashFunctionsList(); }
	else if (operation == INFORMATION) { showInformations(); }
	else if (operation == FULL_INFO) { showFullInfo(); }
	else if (operation == VERSION) { showVersion(); }
	else if (operation == HELP) { showHelp(); }
	else { programError("main.c", __LINE__); }
}

int main(int argc, char** argv)
{
	int uc_argc;
	unichar** uc_argv;
	if (USE_WCHAR)
	{
		#ifdef _WIN32
		uc_argv = CommandLineToArgvW(GetCommandLineW(), &uc_argc);
		#else
		programError("main.c", __LINE__);
		#endif
	}
	else
	{
		uc_argc = argc;
		uc_argv = argv;
	}
	g_argc = uc_argc;
	g_argv = uc_argv;
	_simpleOutput = &useSimpleOutput;
	argumentParser(uc_argc, uc_argv);
	executeOperation(uc_argv);
	return 0;
}
