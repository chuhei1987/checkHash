/*
* Project: checkHash
* Version: 1.0.1
* Project author: https://github.com/chuhei1987/checkHash
* File: help.c
*/

#include "checkHash.h"

void showHelp(void)
{
	puts(
		"checkHash - Help\n"
		"Usage: HASHCHK [options] [filename] [hash / filename / filenames...]\n\n"
		"List of options:\n"
		" [none] / -c         Get file hash and compare it to hash or hash of other file\n"
		"  (--compare)        Comparing is optional. If you don't want to compare, enter only the one filename.\n"
		"                     If you want to compare, enter a filename or hash.\n"
		"                     Based on the used characters and the length of the second input,\n"
		"                     it automatically determines whether it is a file or a hash and what type of hash.\n"
		"                     If you want to be sure about the interpretation of the input, use -cf or -ch.\n"
		"                     You can also use -f to select the hash function.\n"
		"                     Examples:\n"
		"                      HASHCHK file1.txt\n"
		"                      HASHCHK file1.txt file2.txt\n"
		"                      HASHCHK file1.txt ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad\n"
		" -g                  Get the hash for each file from input.\n"
		"  (--get-hash)       Calculates a hash for each input file.\n"
		"                     Examples:\n"
		"                      HASHCHK -g file1.txt file2.txt file3.txt\n"
		" -s [strings]        Hash of string.\n"
		"  (--string-hash)    Calculates the hash for string or strings.\n"
		"                     Examples:\n"
		"                      HASHCHK -s \"Example string\"\n"
		"                      HASHCHK -s \"First string\" \"Second string\"\n"
		" -cf                 Get file hash and compare it to hash of other file\n"
		"  (--compare-files)  Similar to -c, but takes the second argument always as a filename.\n"
		"                     Examples:\n"
		"                      HASHCHK -cf file1.txt file2.txt\n"
		" -ch                 Get file hash and compare it to hash on input\n"
		"  (--compare-hashes) Similar to -c, but takes the second argument always as a hash.\n"
		"                     Unlike -c it does not automatically detect the type of hash function when neither is set.\n"
		"                     It uses SHA3-256 by default.\n"
		"                     Examples:\n"
		"                      HASHCHK -ch file1.txt ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad\n"
		" -f [function]       Sets the selected hash function.\n"
		"  (--hash-function)  Default hash function is SHA3-256.\n"
		"                     To get list of all available hash functions,\n"
		"                     use the -f option without any additional arguments.\n"
		"                     Examples:\n"
		"                      HASHCHK -f\n"
		"                      HASHCHK -f sha3-256 file1.txt\n"
		"                      HASHCHK -f sha3-512 -g file1.txt file2.txt\n"
		" -so                 Simple output.\n"
		"  (--simple-output)  Simplifies the output.\n"
		"                     When comparing, it gives 1 at the end when equal or 0 when different.\n"
		"                     Examples:\n"
		"                      HASHCHK -so file1.txt file2.txt\n"
		"                      HASHCHK -h -so file1.txt file2.txt file3.txt\n"
		" -i (--information)  Information about checkHash.\n"
		" -fi(--full-info)    Full info about checkHash.\n"
		" -v (--version)      Information about checkHash version.\n"
		" -h / -? (--help)    Display this help message.");
}

void showInformations(void)
{
	puts(
		"checkHash - Information\n"
		"checkHash " CH_VERSION " [" CH_CPU "/" CH_OS "]\n"
		"Author: https://github.com/chuhei1987/checkHash\n"
		"Version: " CH_VERSION "\n"
		"Architecture: " CH_CPU "\n"
		"Platform: " CH_OS);
}

void showFullInfo(void)
{
	puts(
		"checkHash - Full info\n"
		"checkHash " CH_VERSION " [" CH_CPU "/" CH_OS "]\n"
		"Author: https://github.com/chuhei1987/checkHash\n"
		"Version: " CH_VERSION "\n"
		"Architecture: " CH_CPU "\n"
		"Platform: " CH_OS);
	#if defined(_MSC_VER)
	puts("Compiler: MSC\n"
		"Compiler version: " DEF_TO_STR(_MSC_VER) " [" DEF_TO_STR(_MSC_FULL_VER) "]");
	#elif defined(__GNUC__)
	puts("Compiler: GCC\n"
		"Compiler version: " __VERSION__);
	#else
	puts("Compiler: [unknown]");
	#endif
}

void showVersion(void)
{
	puts("checkHash " CH_VERSION " [" CH_CPU "/" CH_OS "]");
}

void hashFunctionsList(void)
{
	puts(
		"checkHash - Hash functions list (ch -f)\n"
		//">SHA1\n"
		//">SHA2: SHA-224, SHA-256, SHA-384, SHA-512, SHA-512/224, SHA-512/256\n"
		">SHA2: SHA-256, SHA-384, SHA-512, SHA-512/256\n"
		//">SHA3: SHA3-224, SHA3-256, SHA3-384, SHA3-512\n"
		">SHA3: SHA3-256, SHA3-384, SHA3-512\n"
		//">MD: MD4, MD5\n"
		//">BLAKE: BLAKE2b-512, BLAKE2s-256\n"
		//">RIPEMD: RIPEMD-160\n"
		//">WHIRLPOOL\n"
		">SM3"
		);
}