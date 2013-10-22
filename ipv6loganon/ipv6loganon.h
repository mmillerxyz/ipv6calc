/*
 * Project    : ipv6calc
 * File       : ipv6loganon.h
 * Version    : $Id: ipv6loganon.h,v 1.4 2013/10/22 18:59:55 ds6peter Exp $
 * Copyright  : 2007 by Peter Bieringer <pb (at) bieringer.de>
 * License    : GNU GPL v2
 *
 * Information:
 *  Main header file
 */ 

/* global program related definitions */
#define PROGRAM_NAME "ipv6loganon"
#define PROGRAM_COPYRIGHT "(P) & (C) 2007-" COPYRIGHT_YEAR " by Peter Bieringer <pb (at) bieringer.de>"

/* LRU cache maximum size */
#define CACHE_LRU_SIZE 200

#define DEBUG_ipv6loganon_general      0x00000001l

/* prototyping */
extern int cache_lru_limit;

extern int mask_ipv4;
extern int mask_iid;

extern int feature_zeroize;
extern int feature_anon;
extern int feature_kp;
