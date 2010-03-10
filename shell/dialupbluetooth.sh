#!/bin/bash
modprobe -v -o bluetooth l2cap sco rfcomm bnep hidp hci_usb hci_uart bcm203x hci_vhci

rfcom connect 0 00:1F:3A:DE:4A:42 1

