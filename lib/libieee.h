/*
 * Project    : ipv6calc
 * File       : libieee.h
 * Version    : $Id$
 * Copyright  : 2002-2019 by Peter Bieringer <pb (at) bieringer.de>
 *
 * Information:
 *  Header file for libieee.c
 */

#include "ipv6calc_inttypes.h"
#include "libmac.h"
#include "libeui64.h"


#ifndef _libieee_h

#define _libieee_h

/* Structure */
typedef struct {
	const uint32_t id;
	const char *string_owner;
	const char *shortstring_owner;
} s_ieee_oui;

typedef struct {
	const uint32_t id;
	const uint32_t subid_begin;
	const uint32_t subid_end;
	const char *string_owner;
	const char *shortstring_owner;
} s_ieee_oui28;

typedef struct {
	const uint32_t id;
	const uint32_t subid_begin;
	const uint32_t subid_end;
	const char *string_owner;
	const char *shortstring_owner;
} s_ieee_oui36;

typedef struct {
	const uint32_t id;
	const uint32_t subid_begin;
	const uint32_t subid_end;
	const char *string_owner;
	const char *shortstring_owner;
} s_ieee_iab;

typedef struct {
	const uint32_t bits_00_23;
	const uint8_t type;
	const uint32_t mapping;
} s_ieee_mapping;

#define IEEE_IAB	0x1
#define IEEE_OUI36	0x2
#define IEEE_OUI28	0x3

// internal map for IAB / OUI-28 / OUI-36 lists
// mapping value used for pack/unpack - do not change per entry, max 0xfff
/*@unused@*/ static const s_ieee_mapping ieee_mapping[] = {
	// IAB
	{ 0x0050C2,	IEEE_IAB, 0x1 },
	{ 0x40D855,	IEEE_IAB, 0x2 },
	// OUI36
	{ 0x001BC5,	IEEE_OUI36, 0x9 },
	{ 0x70B3D5,	IEEE_OUI36, 0xa },
	// OUI28 (2019-10-08)
	{ 0x0055DA,	IEEE_OUI28, 0x0010 },
	{ 0x006967,	IEEE_OUI28, 0x0011 },
	{ 0x04714B,	IEEE_OUI28, 0x0012 },
	{ 0x04C3E6,	IEEE_OUI28, 0x0013 },
	{ 0x04D16E,	IEEE_OUI28, 0x0014 },
	{ 0x08ED02,	IEEE_OUI28, 0x0015 },
	{ 0x0C73EB,	IEEE_OUI28, 0x0016 },
	{ 0x0CEFAF,	IEEE_OUI28, 0x0017 },
	{ 0x0CFE5D,	IEEE_OUI28, 0x0018 },
	{ 0x100723,	IEEE_OUI28, 0x0019 },
	{ 0x10DCB6,	IEEE_OUI28, 0x001a },
	{ 0x141FBA,	IEEE_OUI28, 0x001b },
	{ 0x144FD7,	IEEE_OUI28, 0x001c },
	{ 0x189BA5,	IEEE_OUI28, 0x001d },
	{ 0x1C21D1,	IEEE_OUI28, 0x001e },
	{ 0x1C8259,	IEEE_OUI28, 0x001f },
	{ 0x1C8774,	IEEE_OUI28, 0x0020 },
	{ 0x1C8776,	IEEE_OUI28, 0x0021 },
	{ 0x1C8779,	IEEE_OUI28, 0x0022 },
	{ 0x1C8879,	IEEE_OUI28, 0x0023 },
	{ 0x1CA0D3,	IEEE_OUI28, 0x0024 },
	{ 0x1CC0E1,	IEEE_OUI28, 0x0025 },
	{ 0x1CCAE3,	IEEE_OUI28, 0x0026 },
	{ 0x1CFD08,	IEEE_OUI28, 0x0027 },
	{ 0x208593,	IEEE_OUI28, 0x0028 },
	{ 0x241510,	IEEE_OUI28, 0x0029 },
	{ 0x244E7B,	IEEE_OUI28, 0x002a },
	{ 0x282C02,	IEEE_OUI28, 0x002b },
	{ 0x283638,	IEEE_OUI28, 0x002c },
	{ 0x28F537,	IEEE_OUI28, 0x002d },
	{ 0x28FD80,	IEEE_OUI28, 0x002e },
	{ 0x2C16BD,	IEEE_OUI28, 0x002f },
	{ 0x2C265F,	IEEE_OUI28, 0x0030 },
	{ 0x2C279E,	IEEE_OUI28, 0x0031 },
	{ 0x2C4835,	IEEE_OUI28, 0x0032 },
	{ 0x2C6A6F,	IEEE_OUI28, 0x0033 },
	{ 0x2CD141,	IEEE_OUI28, 0x0034 },
	{ 0x3009F9,	IEEE_OUI28, 0x0035 },
	{ 0x300A60,	IEEE_OUI28, 0x0036 },
	{ 0x301F9A,	IEEE_OUI28, 0x0037 },
	{ 0x34008A,	IEEE_OUI28, 0x0038 },
	{ 0x34049E,	IEEE_OUI28, 0x0039 },
	{ 0x34298F,	IEEE_OUI28, 0x003a },
	{ 0x34D0B8,	IEEE_OUI28, 0x003b },
	{ 0x34E1D1,	IEEE_OUI28, 0x003c },
	{ 0x383A21,	IEEE_OUI28, 0x003d },
	{ 0x3873EA,	IEEE_OUI28, 0x003e },
	{ 0x38B19E,	IEEE_OUI28, 0x003f },
	{ 0x38B8EB,	IEEE_OUI28, 0x0040 },
	{ 0x38FDFE,	IEEE_OUI28, 0x0041 },
	{ 0x3C24F0,	IEEE_OUI28, 0x0042 },
	{ 0x3C39E7,	IEEE_OUI28, 0x0043 },
	{ 0x3C427E,	IEEE_OUI28, 0x0044 },
	{ 0x3C6A2C,	IEEE_OUI28, 0x0045 },
	{ 0x401175,	IEEE_OUI28, 0x0046 },
	{ 0x4048FD,	IEEE_OUI28, 0x0047 },
	{ 0x40A36B,	IEEE_OUI28, 0x0048 },
	{ 0x40ED98,	IEEE_OUI28, 0x0049 },
	{ 0x40F385,	IEEE_OUI28, 0x004a },
	{ 0x440377,	IEEE_OUI28, 0x004b },
	{ 0x44D5F2,	IEEE_OUI28, 0x004c },
	{ 0x480BB2,	IEEE_OUI28, 0x004d },
	{ 0x4865EE,	IEEE_OUI28, 0x004e },
	{ 0x4C4BF9,	IEEE_OUI28, 0x004f },
	{ 0x4C65A8,	IEEE_OUI28, 0x0050 },
	{ 0x4C917A,	IEEE_OUI28, 0x0051 },
	{ 0x4CBC98,	IEEE_OUI28, 0x0052 },
	{ 0x4CE173,	IEEE_OUI28, 0x0053 },
	{ 0x500B91,	IEEE_OUI28, 0x0054 },
	{ 0x506255,	IEEE_OUI28, 0x0055 },
	{ 0x50A4D0,	IEEE_OUI28, 0x0056 },
	{ 0x50FF99,	IEEE_OUI28, 0x0057 },
	{ 0x549A11,	IEEE_OUI28, 0x0058 },
	{ 0x54A493,	IEEE_OUI28, 0x0059 },
	{ 0x58E876,	IEEE_OUI28, 0x005a },
	{ 0x58FCDB,	IEEE_OUI28, 0x005b },
	{ 0x5CF286,	IEEE_OUI28, 0x005c },
	{ 0x6095CE,	IEEE_OUI28, 0x005d },
	{ 0x60D7E3,	IEEE_OUI28, 0x005e },
	{ 0x643139,	IEEE_OUI28, 0x005f },
	{ 0x64FB81,	IEEE_OUI28, 0x0060 },
	{ 0x6891D0,	IEEE_OUI28, 0x0061 },
	{ 0x6C5C3D,	IEEE_OUI28, 0x0062 },
	{ 0x6CDFFB,	IEEE_OUI28, 0x0063 },
	{ 0x70886B,	IEEE_OUI28, 0x0064 },
	{ 0x70F8E7,	IEEE_OUI28, 0x0065 },
	{ 0x7419F8,	IEEE_OUI28, 0x0066 },
	{ 0x741AE0,	IEEE_OUI28, 0x0067 },
	{ 0x745BC5,	IEEE_OUI28, 0x0068 },
	{ 0x74E14A,	IEEE_OUI28, 0x0069 },
	{ 0x74F8DB,	IEEE_OUI28, 0x006a },
	{ 0x78C2C0,	IEEE_OUI28, 0x006b },
	{ 0x78CA83,	IEEE_OUI28, 0x006c },
	{ 0x78D800,	IEEE_OUI28, 0x006d },
	{ 0x7C477C,	IEEE_OUI28, 0x006e },
	{ 0x7C70BC,	IEEE_OUI28, 0x006f },
	{ 0x7CBACC,	IEEE_OUI28, 0x0070 },
	{ 0x7CBC84,	IEEE_OUI28, 0x0071 },
	{ 0x7CCBE2,	IEEE_OUI28, 0x0072 },
	{ 0x800A80,	IEEE_OUI28, 0x0073 },
	{ 0x807B85,	IEEE_OUI28, 0x0074 },
	{ 0x80E4DA,	IEEE_OUI28, 0x0075 },
	{ 0x8439BE,	IEEE_OUI28, 0x0076 },
	{ 0x8489EC,	IEEE_OUI28, 0x0077 },
	{ 0x848BCD,	IEEE_OUI28, 0x0078 },
	{ 0x84E0F4,	IEEE_OUI28, 0x0079 },
	{ 0x885D90,	IEEE_OUI28, 0x007a },
	{ 0x885FE8,	IEEE_OUI28, 0x007b },
	{ 0x88A9A7,	IEEE_OUI28, 0x007c },
	{ 0x8C147D,	IEEE_OUI28, 0x007d },
	{ 0x8C192D,	IEEE_OUI28, 0x007e },
	{ 0x8C1CDA,	IEEE_OUI28, 0x007f },
	{ 0x8C593C,	IEEE_OUI28, 0x0080 },
	{ 0x8CC8F4,	IEEE_OUI28, 0x0081 },
	{ 0x904E91,	IEEE_OUI28, 0x0082 },
	{ 0x90C682,	IEEE_OUI28, 0x0083 },
	{ 0x9802D8,	IEEE_OUI28, 0x0084 },
	{ 0x980637,	IEEE_OUI28, 0x0085 },
	{ 0x986D35,	IEEE_OUI28, 0x0086 },
	{ 0x98AAFC,	IEEE_OUI28, 0x0087 },
	{ 0x98F9C7,	IEEE_OUI28, 0x0088 },
	{ 0x9C431E,	IEEE_OUI28, 0x0089 },
	{ 0x9C69B4,	IEEE_OUI28, 0x008a },
	{ 0x9CF6DD,	IEEE_OUI28, 0x008b },
	{ 0xA019B2,	IEEE_OUI28, 0x008c },
	{ 0xA0224E,	IEEE_OUI28, 0x008d },
	{ 0xA02833,	IEEE_OUI28, 0x008e },
	{ 0xA03E6B,	IEEE_OUI28, 0x008f },
	{ 0xA0BB3E,	IEEE_OUI28, 0x0090 },
	{ 0xA0C5F2,	IEEE_OUI28, 0x0091 },
	{ 0xA41163,	IEEE_OUI28, 0x0092 },
	{ 0xA43BFA,	IEEE_OUI28, 0x0093 },
	{ 0xA44F29,	IEEE_OUI28, 0x0094 },
	{ 0xA4580F,	IEEE_OUI28, 0x0095 },
	{ 0xA4DA22,	IEEE_OUI28, 0x0096 },
	{ 0xA4ED43,	IEEE_OUI28, 0x0097 },
	{ 0xA83FA1,	IEEE_OUI28, 0x0098 },
	{ 0xAC1DDF,	IEEE_OUI28, 0x0099 },
	{ 0xAC64DD,	IEEE_OUI28, 0x009a },
	{ 0xB01F81,	IEEE_OUI28, 0x009b },
	{ 0xB0C5CA,	IEEE_OUI28, 0x009c },
	{ 0xB0FD0B,	IEEE_OUI28, 0x009d },
	{ 0xB437D1,	IEEE_OUI28, 0x009e },
	{ 0xB44BD6,	IEEE_OUI28, 0x009f },
	{ 0xB4A2EB,	IEEE_OUI28, 0x00a0 },
	{ 0xB8D812,	IEEE_OUI28, 0x00a1 },
	{ 0xBC3400,	IEEE_OUI28, 0x00a2 },
	{ 0xBC6641,	IEEE_OUI28, 0x00a3 },
	{ 0xBC9740,	IEEE_OUI28, 0x00a4 },
	{ 0xC08359,	IEEE_OUI28, 0x00a5 },
	{ 0xC0D391,	IEEE_OUI28, 0x00a6 },
	{ 0xC47C8D,	IEEE_OUI28, 0x00a7 },
	{ 0xC4954D,	IEEE_OUI28, 0x00a8 },
	{ 0xC4FFBC,	IEEE_OUI28, 0x00a9 },
	{ 0xC82C2B,	IEEE_OUI28, 0x00aa },
	{ 0xC86314,	IEEE_OUI28, 0x00ab },
	{ 0xC88ED1,	IEEE_OUI28, 0x00ac },
	{ 0xCC1BE0,	IEEE_OUI28, 0x00ad },
	{ 0xCC2237,	IEEE_OUI28, 0x00ae },
	{ 0xCCD31E,	IEEE_OUI28, 0x00af },
	{ 0xCCD39D,	IEEE_OUI28, 0x00b0 },
	{ 0xD02212,	IEEE_OUI28, 0x00b1 },
	{ 0xD05F64,	IEEE_OUI28, 0x00b2 },
	{ 0xD07650,	IEEE_OUI28, 0x00b3 },
	{ 0xD0C857,	IEEE_OUI28, 0x00b4 },
	{ 0xD0D94F,	IEEE_OUI28, 0x00b5 },
	{ 0xD425CC,	IEEE_OUI28, 0x00b6 },
	{ 0xD47C44,	IEEE_OUI28, 0x00b7 },
	{ 0xD8860B,	IEEE_OUI28, 0x00b8 },
	{ 0xDC4427,	IEEE_OUI28, 0x00b9 },
	{ 0xDCE533,	IEEE_OUI28, 0x00ba },
	{ 0xE05A9F,	IEEE_OUI28, 0x00bb },
	{ 0xE0B6F5,	IEEE_OUI28, 0x00bc },
	{ 0xE41E0A,	IEEE_OUI28, 0x00bd },
	{ 0xE44CC7,	IEEE_OUI28, 0x00be },
	{ 0xE4956E,	IEEE_OUI28, 0x00bf },
	{ 0xE81863,	IEEE_OUI28, 0x00c0 },
	{ 0xEC9F0D,	IEEE_OUI28, 0x00c1 },
	{ 0xF023B9,	IEEE_OUI28, 0x00c2 },
	{ 0xF041C8,	IEEE_OUI28, 0x00c3 },
	{ 0xF0ACD7,	IEEE_OUI28, 0x00c4 },
	{ 0xF40E11,	IEEE_OUI28, 0x00c5 },
	{ 0xF80278,	IEEE_OUI28, 0x00c6 },
	{ 0xF81D78,	IEEE_OUI28, 0x00c7 },
	{ 0xF88A3C,	IEEE_OUI28, 0x00c8 },
	{ 0xF8B568,	IEEE_OUI28, 0x00c9 },
	{ 0xFCA47A,	IEEE_OUI28, 0x00ca },
	{ 0xFCD2B6,	IEEE_OUI28, 0x00cb },
};

#endif

extern uint32_t libieee_map_oui_macaddr(const ipv6calc_macaddr *macaddrp);
extern uint32_t libieee_map_oui_eui64addr(const ipv6calc_eui64addr *eui64addrp);
extern int libieee_unmap_oui_macaddr(ipv6calc_macaddr *macaddrp, uint32_t map_value);
extern int libieee_unmap_oui_eui64addr(ipv6calc_eui64addr *eui64addrp, uint32_t map_value);

extern int libieee_check_oui36_iab(const uint32_t bits_00_23);
extern int libieee_check_oui28(const uint32_t bits_00_23);
