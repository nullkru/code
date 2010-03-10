#!/bin/bash

# xextract.sh - multiple format archive extractor
# Licensed under the terms of the GNU GPLv2 or later
# Proprietary Software Must Perish!


# TODO:
# fix bugs, implement planned features ;-)


# KNOWN BUGS:
# there are unresolved problems with "unzip" and "unrar", which due to limitations of the binary itself may not be used to extract archives named in a manner similar to "-*" (with "-" being the first char in the filename) - or at least I did not figure out how to do that, yet. Sucks.


# PLANNED FEATURES:
# specify password for extraction (for formats supporting encryption)
# (optional) recursive extraction
# maybe more?


# AUTHOR: Johannes Truschnigg ( johannes.truschnigg@gmx.at || http://gnulords.org/~colo/ )


# GLOBAL VARIABLES, SETTINGS
VERBOSE=0; # keep quiet
DELETE=0; # do not delete archives after successful processing
FORCE=0; # do not overwrite files without asking
SCRIPTNAME="`basename ${0}`"; # beefing up error-messages
STARTDIR=$PWD; # where the script was invoked from
# ABSOLUTE PATHS TO (UN)ARCHIVERS
BZIP="/bin/bunzip2"
GZIP="/bin/gunzip"
RAR="/usr/bin/unrar"
TAR="/bin/tar"
ZIP="/usr/bin/unzip"


# FUNCTIONS
xex_getfiletype () # determine the type of file we're about to process
{
	if [ ! -e "${1}" ];
	then
		echo -e 1>&2 "${SCRIPTNAME}: \tError: file \"${1}\" does not exist.";
	else
	FILETYPE=`file -b -- "${1}"`;
	case "${FILETYPE}" in
		"`echo ${FILETYPE} | grep -i \"^gzip\"`" ) xex_buildcmdline GZIP "${1}";;
		"`echo ${FILETYPE} | grep -i \"^bzip\"`" ) xex_buildcmdline BZIP "${1}";;
		"`echo ${FILETYPE} | grep -i \"^rar\"`" ) xex_buildcmdline RAR "${1}";;
		"`echo ${FILETYPE} | grep -i \"^POSIX tar\"`" ) xex_buildcmdline TAR "${1}";;
		"`echo ${FILETYPE} | grep -i \"^Zip\"`" ) xex_buildcmdline ZIP "${1}";;
		* ) echo -e 1>&2 "${SCRIPTNAME}: \tError: file \"${1}\" is of an unrecognized format.";
	esac;
	fi;
}

xex_buildcmdline () # building commands to extract recognized archives
{
	let COUNT++;
	EXITBUG=0;
	# code for building archiver-specific commandline follows
	# the script assumes that the archive's filename is passed at the very end of the commandline, please be aware of that when hacking around
	case "${1}" in
		"BZIP" )
			CMDLINE="${BZIP}";
			[ "${FORCE}" = "1" ] && CMDLINE="${CMDLINE} -f";
			[ "${VERBOSE}" = "1" ] && CMDLINE="${CMDLINE} -v";
			CMDLINE="${CMDLINE} -- ";
		;;
		"GZIP" )
			CMDLINE="${GZIP}";
			[ "${FORCE}" = 1 ] && CMDLINE="${CMDLINE} -f";
			[ "${VERBOSE}" = 1 ] && CMDLINE="${CMDLINE} -v";
			CMDLINE="${CMDLINE} -- ";
		;;
		"RAR" )
			# non-GNU option style SUCKS, really.
			EXITBUG=1; # unrar fucks up its exit state when trying to unpack an archive named --foo or -bar or sth. like that - to be sure not to kill off an archive we're unable to extract, this variable has to be introduced to sanitize unrar's moronic behaviour. Non-free software at the suck once more. :\
			CMDLINE="${RAR}";
			[ "${FORCE}" = 1 ] && CMDLINE="${CMDLINE} y";
			[ "${VERBOSE}" = 0 ] && CMDLINE="${CMDLINE} inul";
			CMDLINE="${CMDLINE} x ";
		;;
		"TAR" )
			CMDLINE="${TAR}";
			[ "${FORCE}" = 1 ] && CMDLINE="${CMDLINE} --overwrite";
			[ "${VERBOSE}" = 1 ] && CMDLINE="${CMDLINE} -v";
			CMDLINE="${CMDLINE} -x --file=";
		;;
		"ZIP" )
			# non-GNU option style SUCKS, really.
			EXITBUG=1; # unzip suffers from similar idiocy as unrar does. Please stick to "bzip2" and "gzip" when creating archives. Thanks
			CMDLINE="${ZIP}";
			[ "${FORCE}" = 1 ] && CMDLINE="${CMDLINE} -o";
			[ "${VERBOSE}" = 0 ] && CMDLINE="${CMDLINE} -q";
			CMDLINE="${CMDLINE} -- ";
		;;
	esac;
	CMDLINE="${CMDLINE}`basename "${2}"`";
	[ "${VERBOSE}" = 1 ] && echo -e "Processing file \"${2}\"...\n\t----->";
	[ -d ${2%/*} ] && cd ${2%/*};
	${CMDLINE} && [ "${DELETE}" = 1 ] && [ ${EXITBUG} -ne 1 ] && $rm -f -- "`basename "${2}"`" && EXITBUG=0; # extract; kill off the archive if -d was specified and extraction was successful
	cd ${STARTDIR};
	[ "${VERBOSE}" = 1 ] && echo -e "\t<-----\n...processing of file \"${2}\" finished.\n\n";
}

xex_showusage()
{
	echo -e 1>&2 "${SCRIPTNAME}:\t extracts multiple archive files to your current working directory.\nUsage: ${SCRIPTNAME} [-vdf] [--] file1 [file2] [...] [fileN]";
}


# MAIN
if [ -z "${*}" ];
then
	echo -e 1>&2 "${SCRIPTNAME}: \tError: no input file(s) specified." && xex_showusage;
else
	ERRORS=0; # number of errors occured
	COUNT=0; # attempts to extract
	# CMDLINE EVALUATION
	while getopts hfdv SCRIPTOPT 2>/dev/null;
	do
		case ${SCRIPTOPT} in
			v )
				VERBOSE=1;
			;;
			d )
				DELETE=1;
			;;
			f )
				FORCE=1;
			;;
			h )
				xex_showusage; exit 0;
			;;
			- )
				break
			;;
			* )
				echo -e 1>&2 "${SCRIPTNAME}: \tError: bad command line option." && xex_showusage && exit 1;
		esac;
	done;
	# ARGUMENT PROCESSING LOOP
	while [ -n "${1}" ];
	do
		echo ${1} | egrep "^-[-vfdh]$" &>/dev/null || 
		xex_getfiletype "${1}";
		shift;
	done;
	[ ${VERBOSE} = 1 ] && echo -e "\n${SCRIPTNAME}: \tProcessed ${COUNT} file[s]."
fi
