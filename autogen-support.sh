#!/bin/bash
#
# Project    : ipv6calc
# File       : autogen-support.sh
# Version    : $Id$
# Copyright  : 2014-2019 by Peter Bieringer <pb (at) bieringer.de>
#
# Information: provide support functions to autogen.sh/autogen-all-variants.sh
#
# $BASE_DEVEL_GEOIP/  (default if unset: "..")
#          GeoIP-1.4.4
#          GeoIP-1.4.5
#          GeoIP-1.4.6
#          GeoIP-1.4.7
#          GeoIP-1.4.8
#          GeoIP-1.5.0  # 20190202 (EL7 via base as of 20190202)
#          GeoIP-1.5.1
#          GeoIP-1.5.2
#          GeoIP-1.6.0
#          GeoIP-1.6.1
#          GeoIP-1.6.2
#          GeoIP-1.6.3
#          GeoIP-1.6.4
#          GeoIP-1.6.5  # (EL6 via EPEL as of 20190202)
#          GeoIP-1.6.6	# 20161218
#          GeoIP-1.6.7	# 20161218
#          GeoIP-1.6.8	# 20161218
#          GeoIP-1.6.9	# 20161218
#          GeoIP-1.6.10	# 20170617
#          GeoIP-1.6.11	# 20170617
#          GeoIP-1.6.12	# 20190202
#
# $BASE_DEVEL_IP2LCATION/   (default if unset: "..")
#          C-IP2Location-4.0.2  # dropped with version 0.99
#          ip2location-c-6.0.1  # dropped with version 2.0
#          IP2Location-c-6.0.2  # dropped with version 2.0
#          ip2location-c-6.0.3	# 20141003 # dropped with version 2.0
#          ip2location-c-7.0.0	# 20141003 DOWNLOAD BROKEN
#          ip2location-c-7.0.1	# 20150416
#          ip2location-c-8.0.1	# 20161218
#          ip2location-c-8.0.2	# 20161218
#          ip2location-c-8.0.3	# 20161218
#          ip2location-c-8.0.4	# 20170617
#          ip2location-c-8.0.5	# 20190202
#          ip2location-c-8.0.6	# 20190202
#          ip2location-c-8.0.7	# 20190202 BROKEN
#          ip2location-c-8.0.8	# 20190204

#### Definitions

## List of GeoIP versions (append newest one rightmost!)
geoip_versions="1.4.4 1.4.5 1.4.6 1.4.7 1.4.8 1.5.0 1.5.1 1.5.2 1.6.0 1.6.1 1.6.2 1.6.3 1.6.4 1.6.5 1.6.6 1.6.7 1.6.8 1.6.9 1.6.10 1.6.11"
geoip_url_maxmind="http://geolite.maxmind.com/download/geoip/api/c/"
geoip_url_github="https://codeload.github.com/maxmind/geoip-api-c/tar.gz/"

# reduce version on known issues
if which autoconf >/dev/null 2>&1; then
	autoconf_version=$(autoconf -V |grep autoconf | awk '{ print $NF }' | awk -F. '{ print $1 * 1000 + $2 }')
	if [ -n "$autoconf_version" -a $autoconf_version -lt 2065 ]; then
		# autoconf >= 2.65 is required for GeoIP >= 1.5.2
		geoip_versions_orig="$geoip_versions"
		geoip_versions=""
		for version in $geoip_versions_orig; do
			[ -n "$geoip_versions" ] && geoip_versions="$geoip_versions "
			prefix=""
			version_num=$(echo $version | awk -F. '{ print $3 + $2 * 100 + $1 * 10000}')
			if [ $version_num -ge 10502 ]; then
				prefix="!"
			fi
			geoip_versions="$geoip_versions$prefix$version"
		done	
	fi
else
	echo "ERROR : missing executable in path: : autoconf" >&2
	exit 1
fi

geoip_versions_download="$geoip_versions"

geoip_cross_version_test_blacklist() {
	local version_have=$(echo $1 | awk -F. '{ print $3 + $2 * 100 + $1 * 10000}')
	local version_test=$(echo $2 | awk -F. '{ print $3 + $2 * 100 + $1 * 10000}')

	if [ $version_have -ge 10407 -a $version_test -lt 10407 ]; then
		# missing GeoIP_cleanup
		return 1
	fi

	return 0
}


## List of IP2Location versions (append newest one rightmost!)
ip2location_versions="7.0.1 8.0.1 8.0.2 8.0.3 8.0.4 8.0.5 8.0.6 8.0.8"
ip2location_versions_download="7.0.1 8.0.1 8.0.2 8.0.3 8.0.4 8.0.5 8.0.6 8.0.8"
ip2location_url_base="https://www.ip2location.com/downloads/"
ip2location_url_github="https://codeload.github.com/chrislim2888/IP2Location-C-Library/tar.gz/"

ip2location_cross_version_test_blacklist() {
	local version_have=$(echo $1 | awk -F. '{ print $3 + $2 * 100 + $1 * 10000}')
	local version_test=$(echo $2 | awk -F. '{ print $3 + $2 * 100 + $1 * 10000}')

	if [ $version_have -ge 60000 -a $version_test -lt 60000 ]; then
		# incompatible API
		return 1
	fi

	if [ $version_have -ge 60003 -a $version_test -lt 60003 ]; then
		# incompatible (library name got suffix .1)
		return 1
	fi

	if [ $version_have -ge 70000 -a $version_test -lt 70000 ]; then
		# incompatible
		return 1
	fi

	if [ $version_have -lt 70000 -a $version_test -ge 70000 ]; then
		# incompatible
		return 1
	fi

	return 0
}

#### NO CHANGES BELOW

### Automatic Definitions

### base directory for GeoIP/IP2Location
BASE_SOURCES=${BASE_SOURCES:-~/Downloads}

BASE_DEVEL_GEOIP=${BASE_DEVEL_GEOIP:-~/tmp}
BASE_DEVEL_IP2LOCATION=${BASE_DEVEL_IP2LOCATION:-~/tmp}


### Functions Definitions

## generate GeoIP/IP2Location source package name from version
# in download mode provide full URL
nameversion_from_name_version() {
	local name="$1"
	local version="$2"
	local mode="$3" # optional (download|extract|outfile)

	local nameversion=""

	local version_numeric=$(echo "$version" | awk -F. '{ print $3 + $2 * 100 + $1 * 10000}')

	case $name in
	    GeoIP|G)
		if [ "$mode" = "download" ]; then
			if [ $version_numeric -ge 10502 ]; then
				# since 1.5.2 on github
				nameversion="${geoip_url_github}v$version"
			else
				nameversion="${geoip_url_maxmind}GeoIP-$version.tar.gz"
			fi
		elif [ "$mode" = "outfile" ]; then
			if [ $version_numeric -ge 10502 ]; then
				# since 1.5.2 on github
				nameversion="geoip-api-c-$version.tar.gz"
			else
				nameversion="GeoIP-$version.tar.gz"
			fi
		else
			if [ $version_numeric -ge 10502 ]; then
				nameversion="geoip-api-c-$version"
			else
				nameversion="GeoIP-$version"
			fi
		fi
		;;
	    IP2Location|I)
		case $version in
		    4.*)
			nameversion="C-IP2Location-$version"
			;;
		    *)
			# default
			if [ "$mode" = "download" ]; then
				if [ $version_numeric -ge 80000 ]; then
					# since 8.0.0 on github
					nameversion="${ip2location_url_github}$version"
				else
					nameversion="${ip2location_url_base}ip2location-c-$version.tar.gz"
				fi
			elif [ "$mode" = "outfile" ]; then
				nameversion="ip2location-c-$version.tar.gz"
			elif [ "$mode" = "extract" ]; then
				case $version in
				    6.0.1|6.0.2|6.0.3|7.*|8.*)
					nameversion="ip2location-c-$version"
					;;
				    *)
					# default
					nameversion="IP2Location-c-$version"
					;;
				esac
			else
				case $version in
				    8.*)
					nameversion="IP2Location-C-Library-$version"
					;;
				    6.0.1|6.0.3|7.*)
					nameversion="ip2location-c-$version"
					;;
				    *)
					# default
					nameversion="IP2Location-c-$version"
					;;
				esac
			fi
		esac
		;;
	    *)
		echo "ERROR : unsupported: $name" >&2
		return 1
		;;
	esac

	echo "$nameversion"
}

## retrieve GeoIP/IP2Location options from version
options_from_name_version() {
	local name="$1"
	local version="$2"
	local output="$3"

	local nameversion=$(nameversion_from_name_version $name $version)

	case $name in
	    GeoIP|G)
		local dir="$BASE_DEVEL_GEOIP/$nameversion"
		libdir="$dir/libGeoIP/.libs"
		lib="$libdir/libGeoIP.so"
		result="--with-geoip-headers=$dir/libGeoIP --with-geoip-lib=$libdir"
		;;
	    IP2Location|I)
		local dir="$BASE_DEVEL_IP2LOCATION/$nameversion"
		libdir="$dir/libIP2Location/.libs"
		lib="$libdir/libIP2Location.so"
		result="--with-ip2location-headers=$dir/libIP2Location --with-ip2location-lib=$libdir"
		;;
	    *)
		echo "ERROR : unsupported: $name" >&2
		return 1
		;;
	esac

	case $output in
	    'only-lib')
		echo "$lib"
		;;
	    'only-libdir')
		echo "$libdir"
		;;
	    *)
		echo "$result"
		;;
	esac
}

## fallback for GeoIP/IP2Location
fallback_options_from_name() {
	local name="$1"

	local file_header=""
	local versions=""

	case $name in
	    GeoIP|G)
		file_header="/usr/include/GeoIP.h"
		versions="$geoip_versions"
		dir_base="$BASE_DEVEL_GEOIP"
		;;
	    IP2Location|I)
		file_header="/usr/include/IP2Location.h"
		versions="$ip2location_versions"
		dir_base="$BASE_DEVEL_IP2LOCATION"
		;;
	    *)
		echo "ERROR : unsupported: $name" >&2
		return 1
		;;
	esac

	if [ -e "$file_header" ]; then
		echo "NOTICE: file is existing, no fallback required for $name: $file_header" >&2
		return 0
	fi

	echo "NOTICE: file is missing $file_header, check for local availability for $name: $file_header" >&2

	for version in $(echo "$versions" | awk '{ for (i=NF;i>0;i--) print $i }'); do
		if [ ${version:0:1} = "!" ]; then
			echo "NOTICE: skip blacklisted version: $version" >&2
			continue
		fi

		echo "DEBUG : check for version for $name: $version" >&2

		dir="$dir_base/$(nameversion_from_name_version $name $version)"

		if [ -d "$dir" ]; then
			echo "INFO  : found at least directory for name $name: $dir" >&2
			result="$(options_from_name_version $name $version)"
			break
		else
			echo "NOTICE: did not find directory for name $name: $dir (try next)" >&2
		fi
	done

	if [ -z "$result" ]; then
		echo "ERROR : can't find any local source for $name in: $dir_base" >&2
		return 1
	fi

	echo "$result"
}


## build GeoIP/IP2Location libraries
build_library() {
	local name="$1"
	local version_selected="$2"

	echo "INFO  : build: name=$name version=$version_selected" >&2

	local versions=""
	local base_devel=""

	case $name in
	    GeoIP|G)
		versions="$geoip_versions"
		base_devel="$BASE_DEVEL_GEOIP"
		;;
	    IP2Location|I)
		versions="$ip2location_versions"
		base_devel="$BASE_DEVEL_IP2LOCATION"
		;;
	    *)
		echo "ERROR : unsupported: $name" >&2
		return 1
		;;
	esac

	result_all=0

	autoreconf_version=$(autoreconf -V |grep autoreconf | awk '{ print $NF }' | awk -F. '{ print $1 * 1000 + $2 }')

	for version in $versions; do
		if [ ${version:0:1} = "!" ]; then
			echo "NOTICE: skip blacklisted version: $version" >&2
			continue
		fi

		if [ -n "$version_selected" -a "$version" != "$version_selected" ]; then
			echo "NOTICE: skip not selected version: $version" >&2
			continue
		fi

		local version_numeric=$(echo "$version" | awk -F. '{ print $3 + $2 * 100 + $1 * 10000}')
		local nameversion=$(nameversion_from_name_version $name $version)

		if [ ! -d "$base_devel/$nameversion" ]; then
			echo "ERROR : devel directory missing: $base_devel/$nameversion (forgot to extract?)" >&2
			return 1
		fi

		pushd $base_devel/$nameversion >/dev/null
		if [ $? -ne 0 ]; then
			echo "ERROR : can't change to directory: $base_devel/$nameversion (skip)" >&2
			continue
		else
			echo "INFO  : changed to directory: $base_devel/$nameversion"
		fi

		if [ "$dry_run" = "1" ]; then
			echo "INFO  : would build library (dry-run): $name-$version ($nameversion)"
			continue
		else
			echo "INFO  : build library: $name-$version ($nameversion)"
		fi

		case $name in
		    GeoIP)
			skip_autoreconf=0
			if [ -n "$autoconf_version" -a $autoconf_version -eq 2059 ]; then
				if [ $version_numeric -eq 10407 -o $version_numeric -eq 10501 ]; then
					# on CentOS 5 with autoreconf 2.59 somehow broken for 1.4.7 and 1.5.1
					skip_autoreconf=1
				fi
			fi

			if [ $skip_autoreconf -eq 1 ]; then
				./configure && make clean && make
				result=$?
			else
				autoreconf -fi && ./configure && make clean && make
				result=$?
			fi
			;;
		    IP2Location)
			case $version in
			    6.0.3)
				echo "NOTICE: $name-$version requires patching of Makefile.am"
				perl -pi -e 's/data/ /g' Makefile.am
				;;
			esac
			autoreconf -fi && ./configure && make clean && make
			result=$?
			;;
		esac

		popd >/dev/null

		if [ $result -ne 0 ]; then
			echo "ERROR : trouble during build of $name-$version ($nameversion)" >&2
			result_all=1
			break
		else
			echo "INFO  : successful build of $name-$version ($nameversion)" >&2
			build_library_status="$build_library_status $nameversion"
		fi
	done

	return $result_all
}


## clean GeoIP/IP2Location libraries
clean_versions() {
	local name="$1"
	local version_selected="$2"

	echo "INFO  : clean: name=$name version=$version_selected" >&2

	local versions=""
	local base_devel=""

	case $name in
	    GeoIP|G)
		versions="$geoip_versions"
		base_devel="$BASE_DEVEL_GEOIP"
		;;
	    IP2Location|I)
		versions="$ip2location_versions"
		base_devel="$BASE_DEVEL_IP2LOCATION"
		;;
	    *)
		echo "ERROR : unsupported: $name" >&2
		return 1
		;;
	esac

	result_all=0

	for version in $versions; do
		if [ ${version:0:1} = "!" ]; then
			echo "NOTICE: skip blacklisted version: $version" >&2
			continue
		fi

		if [ -n "$version_selected" -a "$version" != "$version_selected" ]; then
			echo "NOTICE: skip not selected version: $version" >&2
			continue
		fi

		local nameversion=$(nameversion_from_name_version $name $version)

		if [ ! -d "$base_devel/$nameversion" ]; then
			echo "NOTICE: devel directory missing: $base_devel/$nameversion (nothing to clean)" >&2
			continue
		fi

		if [ "$dry_run" = "1" ]; then
			echo "INFO  : would remove: $base_devel/$nameversion" >&2
			continue
		else
			echo "INFO  : remove: $base_devel/$nameversion" >&2
		fi

		rm -rf $base_devel/$nameversion
		result=$?

		if [ $result -ne 0 ]; then
			echo "ERROR : trouble during remove of of $name-$version ($nameversion)" >&2
			result_all=1
			break
		else
			echo "INFO  : successful remove of $name-$version ($nameversion)" >&2
			clean_library_status="$clean_library_status $nameversion"
		fi
	done

	return $result_all
}
## extract GeoIP/IP2Location source packages
extract_versions() {
	local name="$1"
	local version_selected="$2"

	echo "INFO  : extract: name=$name version=$version_selected" >&2

	case $name in
	    GeoIP|G)
		versions="$geoip_versions"
		base_devel="$BASE_DEVEL_GEOIP"
		;;
	    IP2Location|I)
		versions="$ip2location_versions"
		base_devel="$BASE_DEVEL_IP2LOCATION"
		;;
	    *)
		echo "ERROR : unsupported: $name" >&2
		return 1
		;;
	esac

	result_all=0

	for version in $versions; do
		if [ ${version:0:1} = "!" ]; then
			echo "NOTICE: skip blacklisted version: $version" >&2
			continue
		fi

		if [ -n "$version_selected" -a "$version" != "$version_selected" ]; then
			echo "NOTICE: skip not selected version: $version" >&2
			continue
		fi

		local nameversion=$(nameversion_from_name_version $name $version extract)

		local nameversion_internal=$(nameversion_from_name_version $name $version)
		local file="$BASE_SOURCES/$nameversion.tar.gz"

		if [ ! -f "$file" ]; then
			echo "NOTICE: file not existing, can't extract: $file" >&2
			continue
		fi

		if [ "$dry_run" = "1" ]; then
			echo "INFO  : would extract source package (dry-run): $name-$version ($nameversion) from $file" >&2
			continue
		else
			echo "INFO  : extract source package: $name-$version ($nameversion): $file" >&2
		fi

		if [ ! -d "$base_devel" ]; then
			echo "ERROR : base devel directory missing: $base_devel" >&2
			return 1
		fi

		# check contents of tgz
		base_dir=$(tar tzf "$file" | head -1 | sed 's/^\.\///g' | awk -F /  '{ print $1 }')
		if [ -z "$base_dir" ]; then
			echo "ERROR : can't extract base_dir from: $file" >&2
			return 1
		fi

		echo "INFO  : file contains base_dir: $base_dir" >&2

		if [ "$nameversion_internal" != "$base_dir" ]; then
			echo "ERROR : nameversion is not matching base_dir: $nameversion_internal <=> $base_dir (download broken or workaround required)"
			return 1
		fi

		tar xzf "$file" -C $base_devel
		result=$?

		if [ $result -ne 0 ]; then
			echo "ERROR : trouble during extract of $name-$version ($nameversion) from $file" >&2
			result_all=1
			break
		else
			echo "INFO  : successful extract of $name-$version ($nameversion) from $file to $base_devel" >&2
			extract_library_status="$extract_library_status $nameversion"
		fi
	done

	return $result_all
}
## retrieve GeoIP/IP2Location source packages
download_versions() {
	local name="$1"
	local version_selected="$2"

	echo "INFO  : download: name=$name version=$version_selected" >&2

	case $name in
	    GeoIP|G)
		versions="$geoip_versions_download"
		base_devel="$BASE_DEVEL_GEOIP"
		;;
	    IP2Location|I)
		versions="$ip2location_versions_download"
		base_devel="$BASE_DEVEL_IP2LOCATION"
		;;
	    *)
		echo "ERROR : unsupported: $name" >&2
		return 1
		;;
	esac

	result_all=0

	for version in $versions; do
		if [ ${version:0:1} = "!" ]; then
			echo "NOTICE: skip blacklisted version: $version" >&2
			continue
		fi

		if [ -n "$version_selected" -a "$version" != "$version_selected" ]; then
			echo "NOTICE: skip not selected version: $version" >&2
			continue
		fi

		local url=$(nameversion_from_name_version $name $version download)
		local outfile="$(nameversion_from_name_version $name $version outfile)"

		local outfile_option=""
		local outfile_option_info=""
		if ! echo "$url" | grep -q "$outfile"; then
			# URL does not contains outfile
			outfile_option="-O $outfile"
			outfile_option_info="($outfile_option)"
		fi

		if [ ! -d "$BASE_SOURCES" ]; then
			echo "ERROR : base source directory missing: $BASE_SOURCES (BASE_SOURCES)" >&2
			return 1
		fi

		pushd $BASE_SOURCES >/dev/null
		if [ $? -ne 0 ]; then
			echo "ERROR : can't change to directory: $BASE_SOURCES (BASE_SOURCES)" >&2
			return 1
		fi

		if [ "$dry_run" = "1" ]; then
			echo "INFO  : would download source package (dry-run): $name-$version from $url $outfile_option_info" >&2
			continue
		else
			echo "INFO  : download source package: $name-$version from $url $outfile_option_info" >&2
		fi

		wget -c -q "$url" $outfile_option
		result=$?

		popd >/dev/null

		if [ $result -ne 0 ]; then
			echo "ERROR : trouble during downloading of $name-$version from $url" >&2
			result_all=1
			break
		else
			echo "INFO  : successful downloaded of $name-$version from $url to $BASE_SOURCES" >&2
			download_library_status="$download_library_status $name:$version"
		fi
	done

	return $result_all
}

## help
help() {
	cat <<END
$0 [-h|-?]
$0 source
$0 [-D] [-X] [-B] [-n] [GeoIP|IP2Location [<version>]]
$0 [-A] [-n] [GeoIP|IP2Location [<version>]]

	source: source mode (using functions only in main script)

	-D  : download GeoIP/IP2Location source packages
	-C  : clean GeoIP/IP2Location source packages
	-X  : extract GeoIP/IP2Location source packages
	-B  : build GeoIP/IP2Location libraries
	-A  : whole chain: download/extract/build
	-n  : dry-run
	(optionally, type and version can be specified)

	GeoIP: $geoip_versions
	IP2Location: $ip2location_versions
	Prefix '!' means not supported on this platform

	-h|?: this online help

	used values from environment (or defaults):
	  BASE_SOURCES=$BASE_SOURCES
	  BASE_DEVEL_GEOIP=$BASE_DEVEL_GEOIP
	  BASE_DEVEL_IP2LOCATION=$BASE_DEVEL_IP2LOCATION
END
}

if [ "$1" != "source" ]; then
	# use script not only as source (function-mode)

	#### Main
	while getopts ":ADCXnB?h" opt; do
		case $opt in
		    'n')
			dry_run=1
			echo "NOTICE: dry-run selected" >&2
			;;
		    'A')
			action="prepare"
			do_download="1"
			do_clean="1"
			do_extract="1"
			do_build="1"
			;;
		    'C')
			action="prepare"
			do_clean="1"
			;;
		    'D')
			action="prepare"
			do_download="1"
			;;
		    'X')
			action="prepare"
			do_extract="1"
			;;
		    'B')
			action="prepare"
			do_build="1"
			;;
		    \?|h)
			help
			exit 1
			;;
		    *)
			echo "Invalid option: -$OPTARG" >&2
			exit 1
			;;
		esac
	done

	shift $[ $OPTIND - 1 ]

	case $action in
	    'prepare')
		if [ "$do_download" = "1" ]; then
			if [ -z "$*" ]; then
				download_versions GeoIP || exit 1
				download_versions IP2Location || exit 1
			else
				download_versions $* || exit 1
			fi
			echo "INFO  : following libaries were successfully downloaded: $download_library_status" >&2
		fi
		if [ "$do_clean" = "1" ]; then
			if [ -z "$*" ]; then
				clean_versions GeoIP || exit 1
				clean_versions IP2Location || exit 1
			else
				clean_versions $* || exit 1
			fi
			echo "INFO  : following libaries were successfully cleaned: $clean_library_status" >&2
		fi
		if [ "$do_extract" = "1" ]; then
			if [ -z "$*" ]; then
				extract_versions GeoIP || exit 1
				extract_versions IP2Location || exit 1
			else
				extract_versions $* || exit 1
			fi
			echo "INFO  : following libaries were successfully extracted: $extract_library_status" >&2
		fi
		if [ "$do_build" = "1" ]; then
			if [ -z "$*" ]; then
				build_library GeoIP || exit 1
				build_library IP2Location || exit 1
			else
				build_library $* || exit 1
			fi
			echo "INFO  : following libaries were successfully built: $build_library_status" >&2
		fi
		;;
	    *)
		help
		;;
	esac
fi
