/*
 * Project    : ipv6calc
 * File       : libipv6calc.h
 * Version    : $Id: libipv6calc.h,v 1.5 2002/03/03 20:14:53 peter Exp $
 * Copyright  : 2001-2002 by Peter Bieringer <pb (at) bieringer.de>
 *
 * Information:
 *  Header file for libipv6calc.c
 */ 

/* prototypes */
extern void string_to_upcase(char *string);
extern void string_to_lowcase(char *string);
extern void string_to_reverse(char *string);
extern long libipv6calc_autodetectinput(char *string);