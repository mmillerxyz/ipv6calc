/*
 * Project    : ipv6calc
 * File       : librfc1886.h
 * Version    : $Id: librfc1886.h,v 1.3 2002/03/03 20:14:53 peter Exp $
 * Copyright  : 2001-2002 by Peter Bieringer <pb (at) bieringer.de>
 *
 * Information:
 *  Header file for librfc1886.c
 */ 

#include "libipv6addr.h"

/* prototypes */
extern int librfc1886_addr_to_nibblestring(ipv6calc_ipv6addr *ipv6addrp, char *resultstring, unsigned long int formatoptions, char* domain);
extern int librfc1886_nibblestring_to_ipv6addrstruct(const char *inputstring, ipv6calc_ipv6addr *ipv6addrp, char *resultstring);