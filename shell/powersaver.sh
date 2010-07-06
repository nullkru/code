#!/bin/bash

powersavemodules=(uhci_hcd ehci_hcd e1000e)

wlanpower='/sys/bus/pci/drivers/iwlagn/0000:03:00.0/tx_power'

ahcilinkpower=("/sys/class/scsi_host/host0/link_power_management_policy" "/sys/class/scsi_host/host1/link_power_management_policy")

dirtywriteback='/proc/sys/vm/dirty_writeback_centisecs'

function powersave()
{
	
	#usb power management
	for i in /sys/bus/usb/devices/*/power/autosuspend; do echo 1 > $i; done
	
	#unloading modules in powersavemodules array
	for i in ${powersavemodules[@]}; do rmmod $i ; echo unloaded $i ; done

	#drop AHCI link power level
	for ctl in ${ahcilinkpower[@]} ; do echo "min_power" > $ctl ; done
	#enable laptop mode
	echo 5 > /proc/sys/vm/laptop_mode
	#Increase writeback timeout to 15 seconds
	echo 1500 > $dirtywriteback
	#Drop wireless power level (at the cost of latency)
	echo 5 > $wlanpower
	#disable wake on lan
	
	echo disable > /proc/acpi/ibm/bluetooth
	/etc/rc.d/bluetooth stop
	#disabled in the bios ethtool -s eth0 wol d
	echo "PowerSave ON!"
}

function poweron()
{
	for i in /sys/bus/usb/devices/*/power/autosuspend; do echo 2 > $i; done
	
	#loading modules in powersavemodules array
	for i in ${powersavemodules[@]}; do modprobe $i ; echo loading $i ; done

	#wireless power
	echo 15 > $wlanpower

	#ahci max performance
	for ctl in ${ahcilinkpower[@]} ; do echo "max_performance" > $ctl ; done

	echo 499 > $dirtywriteback

}

if [[ ! $1 ]]; then 
	powersave
else
	poweron
fi	
