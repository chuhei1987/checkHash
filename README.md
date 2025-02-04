# About

checkHash is a simple command line tool that allows you to easily get file checksum, compare multiple files or compare file checksum to checksum on input.

[Download Version 1.0](https://github.com/chuhei1987/checkHash/releases/tag/checkHash-1.0.1)


For trying your self, may need using something like cl /EHsc /std:c++17 /I "C:\Program Files\OpenSSl\include" main.cpp libssl.lib libcrypto.lib /link /LIBPATH:"C:\Program Files\OpenSSl\lib" 
For linux, you may try such as "gcc -I /usr/local/ssl *.c -Wl,-L,/usr/local/lib -lssl -lcrypto", "gcc *.c -L, -lssl -lcrypto -o HASHCHK.exe" and so on after openssl installed, That author doesn't leave hints, I got that by trial and errors, now I have try cross-compiling for the damn.

It is said, the latest option , "gcc *.c -L, -lssl -lcrypto -o HASHCHK.exe" is tested with MSYS2 UCRT64, which requires openssl dll to get that work so I do like what certutil does, by providing new industrial standards. 

# Example

```
HASHCHK file1.txt
file_sha256("file1.txt") = ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad

HASHCHK file1.txt file2.txt
file_sha256("file1.txt") = ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad
file_sha256("file2.txt") = 9834876dcfb05cb167a5c24953eba58c4ac89b1adf57f28f2f9d09af107ee8f0
[NOT EQUAL]

HASHCHK file1.txt ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad
file_sha256("file1.txt") = ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad
[EQUAL]


```


# List of Options
```
 [none] / -c         Get file hash and compare it to hash or hash of other file
  (--compare)        Comparing is optional. If you don't want to compare, enter only the one filename.
                     If you want to compare, enter a filename or hash.
                     Based on the used characters and the length of the second input,
                     it automatically determines whether it is a file or a hash and what type of hash.
                     If you want to be sure about the interpretation of the input, use -cf or -ch.
                     You can also use -f to select the hash function.
                     Examples:
                      HASHCHK file1.txt
                      HASHCHK file1.txt file2.txt
                      HASHCHK file1.txt ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad
 -g                  Get the hash for each file from input.
  (--get-hash)       Calculates a hash for each input file.
                     Examples:
                      HASHCHK -g file1.txt file2.txt file3.txt
 -s [strings]        Hash of string.
  (--string-hash)    Calculates the hash for string or strings.
                     Examples:
                      HASHCHK -s "Example string"
                      HASHCHK -s "First string" "Second string"
 -cf                 Get file hash and compare it to hash of other file
  (--compare-files)  Similar to -c, but takes the second argument always as a filename.
                     Examples:
                      ch -cf file1.txt file2.txt
 -ch                 Get file hash and compare it to hash on input
  (--compare-hashes) Similar to -c, but takes the second argument always as a hash.
                     Unlike -c it does not automatically detect the type of hash function when neither is set.
                     It uses SHA-256 by default.
                     Examples:
                      HASHCHK -ch file1.txt ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad
 -f [function]       Sets the selected hash function.
  (--hash-function)  Default hash function is SHA-256.
                     To get list of all available hash functions,
                     use the -f option without any additional arguments.
                     Examples:
                      HASHCHK -f
                      HASHCHK -f sha3512 file1.txt
                      HASHCHK -f sha512 -g file1.txt file2.txt
 -so                 Simple output.
  (--simple-output)  Simplifies the output.
                     When comparing, it gives 1 at the end when equal or 0 when different.
                     Examples:
                      HASHCHK -so file1.txt file2.txt
                      HASHCHK -h -so file1.txt file2.txt file3.txt
 -i (--information)  Information about checkHash.
 -fi(--full-info)    Full info about checkHash.
 -v (--version)      Information about checkHash version.
 -h / -? (--help)    Display this help message.
```

# Available Hash Functions


- SHA2: **SHA-256, SHA-384, SHA-512, SHA-512/256**
- SHA3: **SHA3-256, SHA3-384, SHA3-512**
- **SM3**
