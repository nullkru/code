#!/bin/bash
_unloadd='launchctl unload -w '
_loadd='launchctl load -w'
_path='/System/Library/LaunchDaemons/'
daemons="com.apple.syslogd.plist \
	com.apple.wifiFirmwareLoader.plist \
	com.apple.ReportCrash.DirectoryService.plist \
	com.apple.ReportCrash.Jetsam.plist \
   	com.apple.ReportCrash.SafetyNet.plist \
	com.apple.ReportCrash.SimulateCrash.plist \
   	com.apple.ReportCrash.plist \
   	com.apple.CrashHousekeeping.plist \
   	com.apple.DumpBasebandCrash.plist \
   	com.apple.DumpPanic.plist \
	com.apple.aslmanager.plist \
	com.apple.powerlog.plist \
	com.apple.tcpdump.server.plist \
	com.apple.mobile.profile_janitor.plist \
	com.apple.chud.chum.plist \
	com.apple.chud.pilotfish.plist \
	com.apple.psctl.plist \
	com.apple.apsd.tcpdump.pdp_ip0.plist \
	com.apple.apsd.tcpdump.en0.plist \
	com.apple.AOSNotification.plist \
	com.apple.racoon.plist"

function unload() {
	for i in $daemons
	do
		$_unloadd ${_path}${i}
	done
}

unload
