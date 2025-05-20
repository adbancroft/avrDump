### A sketch that dumps the contents of the EEPROM to the UART in Intel HEX format

`avrdude` produces incorrect output:

`avrdude.exe -v -p atmega2560 -c wiring -P COM8 -U eeprom:r:scheduler_test_3.hex:i`