/*
 * Project    : ipv6calc
 * File       : ipv6calchelp.c
 * Version    : $Id: ipv6calchelp.c,v 1.2 2002/03/03 11:01:53 peter Exp $
 * Copyright  : 2002 by Peter Bieringer <pb (at) bieringer.de>
 *
 * Information:
 *  Help libary
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ipv6calc.h"
#include "ipv6calctypes.h"
#include "ipv6calchelp.h"

#include "showinfo.h"


/* display info */
void printversion(void) {
	fprintf(stderr, "%s  version: %s\n", PROGRAM_NAME, PROGRAM_VERSION);
};

void printcopyright(void) {
	fprintf(stderr, "%s\n", PROGRAM_COPYRIGHT);
};

void printinfo(void)  {
	printversion();
	printcopyright();
	fprintf(stderr, "This program formats and calculates IPv6 addresses\n");
	fprintf(stderr, "See '%s -?' for more details\n\n", PROGRAM_NAME);
};

/* format option arguments */
void printhelp_print(void) {
	fprintf(stderr, "   --printprefix        : print only prefix of IPv6 address\n");
        fprintf(stderr, "   --printsuffix        : print only suffix of IPv6 address\n");
};

void printhelp_mask(void) {
	fprintf(stderr, "   --maskprefix         : mask IPv6 address with prefix length (clears suffix bits)\n");
        fprintf(stderr, "   --masksuffix         : mask IPv6 address with suffix length (clears prefix bits)\n");
};

void printhelp_case(void) {
	fprintf(stderr, "   --uppercase|-u       : print chars of IPv6 address in upper case\n");
        fprintf(stderr, "   --lowercase|-l       : print chars of IPv6 address in lower case [default]\n");
};

void printhelp_printstartend(void) {
	fprintf(stderr, "   --printstart <1-128> : print part of IPv6 address start from given number\n");
	fprintf(stderr, "   --printend   <1-128> : print part of IPv6 address end at given number\n");
};

void printhelp_doublecommands(void) {
	printversion();
	printcopyright();
	fprintf(stderr, "   Only one command may be specified!\n");
};

void printhelp_missinginputdata(void) {
	printversion();
	printcopyright();
	fprintf(stderr, "   Missing or to few input data given!\n");
};

/* list of input types */
void printhelp_inputtypes(void) {
	int i, j, maxlen = 0;
	char printformatstring[20];
	
	printversion();
	printcopyright();

	/* look for longest type definition */
	for (j = 0; j < sizeof(ipv6calc_formatstrings) / sizeof(ipv6calc_formatstrings[0]); j++) {
		if (strlen(ipv6calc_formatstrings[j].token) > maxlen) {
			maxlen = strlen(ipv6calc_formatstrings[j].token);
		};
	};

	if (maxlen > 999) {
		fprintf(stderr, " Something going wrong with array 'ipv6calc_formatstrings'!\n");
		exit (1);
	};

	sprintf(printformatstring, "  %%-%ds: %%s\n", maxlen);

	if (ipv6calc_debug) {
		fprintf(stderr, "Format string: %s\n", printformatstring);
	};

	fprintf(stderr, "\n Available input types:\n");

	/* run through matrix */
	for (i = 0; i < sizeof(ipv6calc_formatmatrix) / sizeof(ipv6calc_formatmatrix[0]); i++) {
		if (ipv6calc_debug) {
			fprintf(stderr, "Row %d: %04lx - %04lx\n", i, ipv6calc_formatmatrix[i][0], ipv6calc_formatmatrix[i][1]);
		};
		if (ipv6calc_formatmatrix[i][1] != 0) {
			/* available for input, look for name now */
			for (j = 0; j < sizeof(ipv6calc_formatstrings) / sizeof(ipv6calc_formatstrings[0]); j++) {
				if (ipv6calc_debug) {
					fprintf(stderr, "Format-Row %d: %04lx - %s - %s\n", j, ipv6calc_formatstrings[j].number, ipv6calc_formatstrings[j].token, ipv6calc_formatstrings[j].explanation);
				};
				if (ipv6calc_formatstrings[j].number == ipv6calc_formatmatrix[i][0]) {
					fprintf(stderr, printformatstring, ipv6calc_formatstrings[j].token, ipv6calc_formatstrings[j].explanation);
				};
			};
		};
	};
};


/* list of output types */
void printhelp_outputtypes(long int inputtype) {
	int i, j, maxlen = 0;
	char printformatstring[20];
	
	printversion();
	printcopyright();

	/* look for longest type definition */
	for (j = 0; j < sizeof(ipv6calc_formatstrings) / sizeof(ipv6calc_formatstrings[0]); j++) {
		if (strlen(ipv6calc_formatstrings[j].token) > maxlen) {
			maxlen = strlen(ipv6calc_formatstrings[j].token);
		};
	};

	if (maxlen > 999) {
		fprintf(stderr, " Something going wrong with array 'ipv6calc_formatstrings'!\n");
		exit (1);
	};

	sprintf(printformatstring, "  %%-%ds: %%s\n", maxlen);

	if (ipv6calc_debug) {
		fprintf(stderr, "Format string: %s\n", printformatstring);
	};

	if (inputtype > 0) {
		fprintf(stderr, "\n Available output types filtered by input type:\n");
	} else {
		fprintf(stderr, "\n Available output types:\n");
	};

	/* run through matrix */
	for (j = 0; j < sizeof(ipv6calc_formatstrings) / sizeof(ipv6calc_formatstrings[0]); j++) {
		if (ipv6calc_debug) {
			fprintf(stderr, "Format-Row %d: %04lx - %s - %s\n", j, ipv6calc_formatstrings[j].number, ipv6calc_formatstrings[j].token, ipv6calc_formatstrings[j].explanation);
		};

		for (i = 0; i < sizeof(ipv6calc_formatmatrix) / sizeof(ipv6calc_formatmatrix[0]); i++) {
			if (inputtype > 0) {
				if (ipv6calc_formatmatrix[i][0] != inputtype) {
					/* skip */
					continue;
				};
			};
		
			if (ipv6calc_debug) {
				fprintf(stderr, "Row %d: %04lx - %04lx\n", i, ipv6calc_formatmatrix[i][0], ipv6calc_formatmatrix[i][1]);
			};
			if (ipv6calc_formatmatrix[i][1] & ipv6calc_formatstrings[j].number) {
				/* available for input, look for name now */
				fprintf(stderr, printformatstring, ipv6calc_formatstrings[j].token, ipv6calc_formatstrings[j].explanation);
				break;
			};
		};
	};
	fprintf(stderr, "\n For examples and available format options use:\n");
	fprintf(stderr, "   %s --outputtype <type> --examples\n", PROGRAM_NAME);
};


/* list of action types */
void printhelp_actiontypes(void) {
	int i, j, maxlen = 0;
	char printformatstring[20];
	
	printversion();
	printcopyright();

	/* look for longest type definition */
	for (j = 0; j < sizeof(ipv6calc_actionstrings) / sizeof(ipv6calc_actionstrings[0]); j++) {
		if (strlen(ipv6calc_actionstrings[j].token) > maxlen) {
			maxlen = strlen(ipv6calc_actionstrings[j].token);
		};
	};

	if (maxlen > 999) {
		fprintf(stderr, " Something going wrong with array 'ipv6calc_actionstrings'!\n");
		exit (1);
	};

	sprintf(printformatstring, "  %%-%ds: %%s\n", maxlen);

	if (ipv6calc_debug) {
		fprintf(stderr, "Format string: %s\n", printformatstring);
	};

	fprintf(stderr, "\n Available action types:\n");

	for (j = 0; j < sizeof(ipv6calc_actionstrings) / sizeof(ipv6calc_actionstrings[0]); j++) {
		if (ipv6calc_debug) {
			fprintf(stderr, "Format-Row %d: %04lx - %s - %s\n", j, ipv6calc_actionstrings[j].number, ipv6calc_actionstrings[j].token, ipv6calc_actionstrings[j].explanation);
		};
		fprintf(stderr, printformatstring, ipv6calc_actionstrings[j].token, ipv6calc_actionstrings[j].explanation);
	};
};


/* print global help */
void printhelp(void) {
	printversion();
	printcopyright();
	fprintf(stderr, "\nGeneral:\n");
	fprintf(stderr, " [-d|--debug <debug value>] ...\n");
	
	fprintf(stderr, "Usage with new style options:\n");
	fprintf(stderr, " %s --inputtype|--intype <input type> --outputtype|--outtype <output type> [--actiontype|--action <action>] [<format option> ...] <input data>\n", PROGRAM_NAME);
	fprintf(stderr, "  For more help about input types see:\n");
	fprintf(stderr, "   %s --inputtype|--intype -?\n", PROGRAM_NAME);
	fprintf(stderr, "  For more help about output types see:\n");
	fprintf(stderr, "   %s --outputtype|--outtype -?\n", PROGRAM_NAME);
	fprintf(stderr, "  For more help about action types see:\n");
	fprintf(stderr, "   %s --actiontype|--action -?\n", PROGRAM_NAME);

	fprintf(stderr, "\nOld style options:\n");
	fprintf(stderr, "Usage: (see '%s <command> -?' for more help)\n", PROGRAM_NAME);
	
	showinfo_printhelp();

	return;
};


/* print help for output type examples */


static void printhelp_output_base85(void) {
	fprintf(stderr, " Print a given IPv6 address in base85 format (RFC 1924), e.g.\n");
	fprintf(stderr, "  1080:0:0:0:8:800:200c:417a -> 4)+k&C#VzJ4br>0wv%%Yp\n");
};

static void printhelp_output_bitstring(void) {
	fprintf(stderr, " Print a given IPv6 address as a bitstring label for use with DNS, e.g.\n");
	fprintf(stderr, "  3ffe:ffff::1    -> \\[x3ffeffff000000000000000000000001/128].ip6.arpa.\n");
	fprintf(stderr, "  3ffe:ffff::1/64 -> \\[x3ffeffff000000000000000000000001/64].ip6.arpa.\n");
	fprintf(stderr, "  --printsuffix 3ffe:ffff::1/64 -> \\[x0000000000000001/64]\n");
	fprintf(stderr, "  --printprefix 3ffe:ffff::1/64 -> \\[x3ffeffff00000000/64]\n");
};

static void printhelp_output_ipv6addr(void) {
	fprintf(stderr, " Print a given IPv6 address depending on format options:\n");
	fprintf(stderr, "  Uncompressed, e.g.\n");
	fprintf(stderr, "   3ffe:ffff:100:f101::1 -> 3ffe:ffff:100:f101:0:0:0:1\n");
	fprintf(stderr, "   3ffe:ffff:100:f101::1/64 -> 3ffe:ffff:100:f101:0:0:0:1/64\n");
	fprintf(stderr, "  Full uncompressed, e.g.\n");
	fprintf(stderr, "   3ffe:ffff:100:f101::1 -> 3ffe:ffff:0100:f101:0000:0000:0000:0001\n");
	fprintf(stderr, "  Compressed, e.g.\n");
	fprintf(stderr, "   3ffe:ffff:0100:f101:0000:0000:0000:0001 -> 3ffe:ffff:100:f101::1\n");
};

static void printhelp_output_eui64(void) {
	fprintf(stderr, " Print a generated EUI-64 identifier, e.g.:\n");
	fprintf(stderr, "  00:50:BF:06:B4:F5 -> 0250:bfff:fe06:b4f5\n");
};

static void printhelp_output_iid_token(void) {
	fprintf(stderr, " Print generated interface identifier and token, e.g.:\n");
	fprintf(stderr, "  -> 4462:bdea:8654:776d 486072ff7074945e\n");
};

static void printhelp_output_revnibble_int(void) {
	fprintf(stderr, " Print a given IPv6 address in dot separated reverse nibble format for use with DNS, e.g.\n");
	fprintf(stderr, "  3ffe:ffff:100:f101::1\n    -> 1.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.1.0.1.f.0.0.1.0.0.0.4.0.e.f.f.3.ip6.int.\n");
	fprintf(stderr, "  3ffe:ffff:100:f101::1/64\n    -> 1.0.1.f.0.0.1.0.0.0.4.0.e.f.f.3.ip6.int.\n");
};

static void printhelp_output_revnibble_arpa(void) {
	fprintf(stderr, " Print a given IPv6 address in dot separated reverse nibble format for use with DNS, e.g.\n");
	fprintf(stderr, "  3ffe:ffff:100:f101::1\n    -> 1.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.1.0.1.f.0.0.1.0.0.0.4.0.e.f.f.3.ip6.arpa.\n");
	fprintf(stderr, "  3ffe:ffff:100:f101::1/64\n    -> 1.0.1.f.0.0.1.0.0.0.4.0.e.f.f.3.ip6.arpa.\n");
};

static void printhelp_output_ifinet6void(void) {
	fprintf(stderr, " Print a given IPv6 address to same format shown in Linux /proc/net/if_inet6:\n");
	fprintf(stderr, "  3ffe:ffff:100:f101::1    -> 3ffeffff0100f1010000000000000001 00\n");
	fprintf(stderr, "  3ffe:ffff:100:f101::1/64 -> 3ffeffff0100f1010000000000000001 00 40\n");
};


void printhelp_output_dispatcher(long int outputtype) {
	int i, j;

	printversion();
	
	fprintf(stderr, "\n");

	switch (outputtype) {
		case FORMAT_base85:
			printhelp_output_base85();
			break;

		case FORMAT_bitstring:
			printhelp_output_bitstring();
			break;
			
		case FORMAT_ipv6addr:
			printhelp_output_ipv6addr();
			break;
			
		case FORMAT_eui64:
			printhelp_output_eui64();
			break;

		case FORMAT_revnibbles_int:
			printhelp_output_revnibble_int();
			break;

		case FORMAT_revnibbles_arpa:
			printhelp_output_revnibble_arpa();
			break;

		case FORMAT_ifinet6:
			printhelp_output_ifinet6void();
			break;
			
		case FORMAT_iid_token:
			printhelp_output_iid_token();
			break;

		default:
			fprintf(stderr, " Help currently missing...!\n");
			break;
	};
	
	/* looking for outtype */
	for (i = 0; i < sizeof(ipv6calc_outputformatoptionmap) / sizeof(ipv6calc_outputformatoptionmap[0]); i++) {
		if (outputtype == ipv6calc_outputformatoptionmap[i][0]) {
			if (ipv6calc_outputformatoptionmap[i][1] == 0) {
				break;
			};
			
			fprintf(stderr, " Available format options:\n");

			/* run through format options */
			for (j = 0; j < sizeof(ipv6calc_formatoptionstrings) / sizeof (ipv6calc_formatoptionstrings[0]); j++) {
				if (ipv6calc_outputformatoptionmap[i][1] & ipv6calc_formatoptionstrings[j].number) {
					fprintf(stderr, "  %s: %s\n", ipv6calc_formatoptionstrings[j].token, ipv6calc_formatoptionstrings[j].explanation);
				};
			};
			break;
		};
	};
};



