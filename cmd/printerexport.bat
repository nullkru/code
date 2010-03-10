REM by kru<@chao.ch> [http://chao.ch]
REM date 21.06.2006
REM um die drucker wieder hinzu zu fügen einfach alle exportierten registry einträge
REM wieder hinzufügen und computer neu starten. (achtung treiber müssen ev nachinstalliert werden
REM einfach mal einen drucker anklicken und man wird gefragt ob der treiber installiert werden soll)

@title kru's - printer exporter

@set DIR=C:\printers

@echo Script um Drucker mit einstellungen zu exportieren
@echo Dateien werden im Verzeichniss %DIR% gespeichert
@pause
@echo Start ........
@mkdir %DIR%
@echo off
reg export "HKCU\Printers" "%DIR%\1printer.reg"
reg export "HKEY_USERS\S-1-5-18\SOFTWARE\Microsoft\Windows NT\CurrentVersion\Devices" "%DIR%\2printer.reg"
reg export "HKEY_USERS\S-1-5-18\SOFTWARE\Microsoft\Windows NT\CurrentVersion\PrinterPorts" "%DIR%\3printer.reg"
reg export "HKCU\SOFTWARE\Microsoft\Windows NT\CurrentVersion\Devices" "%DIR%\4printer.reg"
reg export "HKLM\SOFTWARE\Microsoft\Windows NT\CurrentVersion\Print" "%DIR%\5printer.reg"
reg export "HKEY_USERS\.DEFAULT\SOFTWARE\Microsoft\Windows NT\CurrentVersion\PrinterPorts" "%DIR%\6printer.reg"
reg export "HKEY_USERS\.DEFAULT\SOFTWARE\Microsoft\Windows NT\CurrentVersion\Devices" "%DIR%\7printer.reg"
reg export "HKLM\SYSTEM\CurrentControlSet\Control\Print" "%DIR%\8printer.reg"
reg export "HKLM\SYSTEM\ControlSet001\Control\Print" "%DIR%\9printer.reg"
@echo on
@echo Jetzt zu deinem ziel Computer wechseln und dort alle exportierten .reg in die registry importieren
@echo Fertig... Vielen Dank
@pause
