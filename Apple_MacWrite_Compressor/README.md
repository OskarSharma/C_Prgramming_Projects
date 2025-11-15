This project implements a text-compression utility based on the original encoding strategy used in Apple’s early MacWrite word-processing system. 
The program reduces file size by converting characters into 4-bit nibbles using a frequency-based lookup table. Common characters (such as spaces,
vowels, and high-frequency letters) are mapped to single-nibble codes, while uncommon characters are encoded using a three-nibble fallback scheme. 
The companion decompressor reverses the process and reconstructs the exact original text.

Features include:
Nibble-level I/O subsystem implementing custom read/write operations (nibbler.c, nibbler.h)

Compression utility that encodes text using a compact, MacWrite-style variable-length scheme
  
Decompression utility that restores files back to their original byte stream

Error-handled CLI tools for compress infile -o outfile and decompress infile -o outfile

Comprehensive unit tests verifying nibble operations and end-to-end correctness

This project demonstrates low-level data representation, bitwise manipulation, file-I/O abstraction, and the design of a lightweight compression format.

