/*
* Program:      decompress
*
* Purpose:      Decompress a file that was compressed with "compress".
*
* Usage:        decompress INFILE -o OUTFILE
*/

#include "nibbler.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_usage(void) {
    printf("Usage:  decompress INFILE -o OUTFILE\n");
    exit(0);
}

/* 
* Purpose: 	To reverse the compressing process and decompress. The function reads
* 			nibbles from a compressed file and reconstructs the origincal bytes,
* 			writing them to a normal text file. If a nibble is non-zero, its 
* 			a common character. If it is zero, that'a a market saying that the 
* 			next two nibbles form an uncommon character. 
*
* Parameters: 	NIB *nib - input stream opened with nib_open(); provides compressed nibbles
* 		FILE *fout - output file opened with fopen(); receives decompressed text 
*
* Returns: 	N/A
*/
void decompress(NIB *nib, FILE *fout) {
    while (1) {
	int n = nib_get_nibble(nib);
	if (n == EOF) 
	    break;

	if (n > 0) {
	    int ch = 0; 
	    switch (n) {
		case 0x01: ch = ' '; break;	
		case 0x02: ch = 'e'; break;
		case 0x03: ch = 't'; break;
		case 0x04: ch = 'n'; break;
		case 0x05: ch = 'r'; break;
		case 0x06: ch = 'o'; break;
		case 0x07: ch = 'a'; break;
		case 0x08: ch = 'i'; break;
		case 0x09: ch = 's'; break;
		case 0x0A: ch = 'd'; break;
		case 0x0B: ch = 'l'; break;
		case 0x0C: ch = 'h'; break;
		case 0x0D: ch = 'c'; break;
		case 0x0E: ch = 'f'; break;
		case 0x0F: ch = 'p'; break;
		default: continue;
	    }
	    fputc(ch, fout);
	} else {
	    int n1 = nib_get_nibble(nib);
	    if (n1 == EOF) break;
	    int n2 = nib_get_nibble(nib);
	    if (n2 == EOF) break;

	    int byte = ((n1 & 0x0F) << 4) | (n2 & 0x0F);
	    fputc(byte, fout);
	}
    }
}

/*
* Purpose: 	drive the decompressor per "infile -o outfile". Simply, this function
* 			is for decompressing. 
*
* Parameters: 	argc, argv
*
* Returns: 	0 on success; nonzero on error.
*/
int main(int argc, char **argv) {
    if (argc != 4 || strcmp(argv[2], "-o") != 0) {
	fprintf(stderr, "usage: %s infile -o outfile\n", argv[0]);
	return 1;
    }

    NIB *nin = nib_open(argv[1], "r");
    if (!nin) {
	fprintf(stderr, "error: cannot open input: %s\n", argv[1]);
	return 1;
    }

    FILE *fout = fopen(argv[3], "w");
    if (!fout) {
	fprintf(stderr, "error: cannot open output: %s\n", argv[3]);
	nib_close(nin);
	return 1;
    }

    decompress(nin, fout);

    nib_close(nin);
    fclose(fout);
    return 0;
}
