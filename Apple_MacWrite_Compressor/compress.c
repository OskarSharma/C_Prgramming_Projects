/*
* Program:      compress
*
* Purpose:      Compress a file.
*
* Usage:        compress INFILE -o OUTFILE
*/

#include "nibbler.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_usage(void) {
    printf("Usage:  compress INFILE -o OUTFILE\n");
    exit(0);
}

/*
* Purpose: 	Compress a textfile by converting each byte or character into one or
* 			more nibbles according to the table from Figure 2 of asgn5. 
*
* Parameters: 	FILE *fin - opened input file that is to be compressed
* 		NIB *nib - nibble-based output stream created with nib_open(), 
* 			where compressed nibs are written. 
*
* Returns: 	N/A
*/
void compress(FILE *fin, NIB *nib) {
    int ch;
    while ((ch = fgetc(fin)) != EOF) {
	int nibble = 0;
	switch (ch) {
	    case ' ': nibble = 0x01; break;
	    case 'e': nibble = 0x02; break;
	    case 't': nibble = 0x03; break;
	    case 'n': nibble = 0x04; break;
	    case 'r': nibble = 0x05; break;
	    case 'o': nibble = 0x06; break;
	    case 'a': nibble = 0x07; break;
	    case 'i': nibble = 0x08; break;
	    case 's': nibble = 0x09; break;
	    case 'd': nibble = 0x0A; break;
	    case 'l': nibble = 0x0B; break;
	    case 'h': nibble = 0x0C; break;
	    case 'c': nibble = 0x0D; break;
	    case 'f': nibble = 0x0E; break;
	    case 'p': nibble = 0x0F; break;
	    default: nibble = 0;
	}

	if (nibble != 0)
	    nib_put_nibble(nibble, nib);
	else {
	    nib_put_nibble(0x0, nib);
	    nib_put_nibble((ch >> 4) & 0x0F, nib);
	    nib_put_nibble(ch & 0x0F, nib);
	}
    }
}

/* 
* Purpose: 	drive the compressor per "infile -o outfile"
*
* Parameters: 	argc, argv
*
* Returns: 	0 in success, nonzero on error
*/
int main(int argc, char **argv) {
    if (argc != 4 || strcmp(argv[2], "-o") != 0) {
	fprintf(stderr, "usage: %s infile -o outfile\n", argv[0]);
	return 1;
    }

    FILE *fin = fopen(argv[1], "r");
    if (!fin) {
	fprintf(stderr, "error: cannot open input: %s\n", argv[1]);
	return 1;
    }

    NIB *nib = nib_open(argv[3], "w");
    if (!nib) {
	fprintf(stderr, "error: cannot open output: %s\n", argv[3]);
	fclose(fin);
	return 1;
    }

    compress(fin, nib);

    fclose(fin);
    nib_close(nib);
    return 0;
}
