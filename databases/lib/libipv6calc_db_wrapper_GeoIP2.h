/*
 * Project    : ipv6calc
 * File       : databases/lib/libipv6calc_db_wrapper_GeoIP2.h
 * Version    : $Id$
 * Copyright  : 2019-2019 by Peter Bieringer <pb (at) bieringer.de>
 *
 * Information:
 *  Header file for libipv6calc_db_wrapper_GeoIP2.c
 */

#include "ipv6calctypes.h"

#ifndef _libipv6calc_db_wrapper_GeoIP2_h

#define _libipv6calc_db_wrapper_GeoIP2_h 1

// database types
#define GeoIP2_DB_COUNTRY_LITE				1
#define GeoIP2_DB_CITY_LITE				2
#define GeoIP2_DB_ASN					3
#define GeoIP2_DB_COUNTRY				4	// commercial
#define GeoIP2_DB_CITY					5	// commercial
#define GeoIP2_DB_ISP					6	// commercial
#define GeoIP2_DB_MAX					GeoIP2_DB_ISP

#define IPV6CALC_DB_GEOIP2_INTERNAL_FREE		0x00000001
#define IPV6CALC_DB_GEOIP2_INTERNAL_COMM		0x00000002

/*@unused@*/ static const db_file_desc2 libipv6calc_db_wrapper_GeoIP2_db_file_desc[] = {
	// country (lite)
	{ GeoIP2_DB_COUNTRY_LITE
		, "GeoLite2-Country.mmdb"
		, "IPv4/v6 CountryCode (FREE)"
		, IPV6CALC_DB_IPV4_TO_CC | IPV6CALC_DB_GEOIP_IPV4 | IPV6CALC_DB_IPV6_TO_CC | IPV6CALC_DB_GEOIP_IPV6
		, IPV6CALC_DB_GEOIP2_INTERNAL_FREE
	},

	// city (lite)
	{ GeoIP2_DB_CITY_LITE
		, "GeoLite2-City.mmdb"
		, "IPv4/v6 City (FREE)"
		, IPV6CALC_DB_IPV4_TO_CITY | IPV6CALC_DB_IPV4_TO_REGION | IPV6CALC_DB_IPV4_TO_CC | IPV6CALC_DB_GEOIP_IPV4 | IPV6CALC_DB_IPV6_TO_CITY | IPV6CALC_DB_IPV6_TO_REGION | IPV6CALC_DB_IPV6_TO_CC | IPV6CALC_DB_GEOIP_IPV6
		, IPV6CALC_DB_GEOIP2_INTERNAL_FREE
	},

	// ASN (lite)
	{ GeoIP2_DB_ASN
		, "GeoLite2-ASN.mmdb"
		, "IPv4/v6 ASN (FREE)"
		, IPV6CALC_DB_IPV4_TO_AS | IPV6CALC_DB_IPV6_TO_AS
		, IPV6CALC_DB_GEOIP2_INTERNAL_FREE
	},

	// country
	{ GeoIP2_DB_COUNTRY
		, "Geo2-Country.mmdb"
		, "IPv4/v6 CountryCode (COMM)"
		, IPV6CALC_DB_IPV4_TO_CC | IPV6CALC_DB_GEOIP_IPV4 | IPV6CALC_DB_IPV6_TO_CC | IPV6CALC_DB_GEOIP_IPV6
		, IPV6CALC_DB_GEOIP2_INTERNAL_COMM
	},

	// city
	{ GeoIP2_DB_CITY
		, "Geo2-City.mmdb"
		, "IPv4/v6 City (COMM)"
		, IPV6CALC_DB_IPV4_TO_CITY | IPV6CALC_DB_IPV4_TO_REGION | IPV6CALC_DB_IPV4_TO_CC | IPV6CALC_DB_GEOIP_IPV4 | IPV6CALC_DB_IPV6_TO_CITY | IPV6CALC_DB_IPV6_TO_REGION | IPV6CALC_DB_IPV6_TO_CC | IPV6CALC_DB_GEOIP_IPV6
		, IPV6CALC_DB_GEOIP2_INTERNAL_COMM
	},

	// ISP
	{ GeoIP2_DB_ISP
		, "Geo2-ISP.mmdb"
		, "IPv4/v6 ISP (COMM)", IPV6CALC_DB_IPV4_TO_AS | IPV6CALC_DB_GEOIP_IPV4 | IPV6CALC_DB_IPV6_TO_AS | IPV6CALC_DB_GEOIP_IPV6
		, IPV6CALC_DB_GEOIP2_INTERNAL_COMM
	},
};


// features
extern uint32_t wrapper_features_GeoIP2;

#endif

extern int         libipv6calc_db_wrapper_GeoIP2_wrapper_init(void);
extern int         libipv6calc_db_wrapper_GeoIP2_wrapper_cleanup(void);
extern void        libipv6calc_db_wrapper_GeoIP2_wrapper_info(char* string, const size_t size);
extern void        libipv6calc_db_wrapper_GeoIP2_wrapper_print_db_info(const int level_verbose, const char *prefix_string);
extern char       *libipv6calc_db_wrapper_GeoIP2_wrapper_db_info_used(void);

extern int         libipv6calc_db_wrapper_GeoIP2_wrapper_country_code_by_addr(const ipv6calc_ipaddr *ipaddrp, char *country, const size_t country_len);
extern uint32_t    libipv6calc_db_wrapper_GeoIP2_wrapper_asn_by_addr(const ipv6calc_ipaddr *ipaddrp);

extern int         libipv6calc_db_wrapper_GeoIP2_has_features(const uint32_t features);


#ifdef SUPPORT_GEOIP2

#include "libipv6calc_db_wrapper_MMDB.h"

extern char geoip2_db_dir[NI_MAXHOST];

extern int          libipv6calc_db_wrapper_GeoIP2_db_avail(const unsigned int type);
extern int          libipv6calc_db_wrapper_GeoIP2_open_type(const unsigned int type_flag);

extern const char  *libipv6calc_db_wrapper_GeoIP2_dbdescription(const unsigned int type);
extern char        *libipv6calc_db_wrapper_GeoIP2_database_info(const unsigned int type);

extern int geoip2_db_comm_to_free_switch_min_delta_months;
extern int geoip2_db_only_type;

extern int          libipv6calc_db_wrapper_GeoIP2_all_by_addr(const ipv6calc_ipaddr *ipaddrp, libipv6calc_db_wrapper_geolocation_record *recordp);

#endif