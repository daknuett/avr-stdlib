# AVR extra library

Yet Another AVR library

## Configuration

* Generate needed files using `make init`
* run `./configure.sh`

## Usage

* It uses Auto-make-rules => use
 * `make file.elf` to compile and link the c-file
 * `make ifile.elf` to flash your program on the avr
* use the includes `<pins.h>` & co

## Devices supported

* atmega168: fully supported
* atmega8: partially supported ( many librarys should be compatible)

## Linking

* as auto-rules are used, you will have to reconfigure the project using `./configure.sh` to change the linked libs
* to save flash space unused libarys shouldn't be linked
* to save ram you can use usart in no interrupt mode and do not link some librarys

## Device handling

* You will have to define device specific preprocessor macros for `<pins.h>`:
 * on m8: `__DEV_M8_`
 * on m168: `__DEV_M168_`
* The most part is configured by `configure.sh`


## Functions

| File | Function | Usage |
|------|----------|-------|
| `lib/<device>/digital.c` | `write_pin(char pin)` | write _pin_ digital, _pin_ is the  PDIP pinnumber|
| `lib/<device>/digital.c` | `read_pin(char pin)` | read _pin_ digital, _pin_ is the  PDIP pinnumber|
| `lib/<device>/analog.c` | `analog_write(char pin)` | write _pin_ analog (PWM)(if supported), _pin_ is the  PDIP pinnumber|
| `lib/<device>/analog.c` | `analog_read(char pin)` | read _pin_ analog (if supported), _pin_ is the  PDIP pinnumber|
| `lib/pins.c` | `analog_get(char pin)` |read _pin_ analog with average (if supported), _pin_ is the  PDIP pinnumber|
| `lib/pins.c` | `get_pin(char pin)` |read _pin_ digital with polling, _pin_ is the  PDIP pinnumber|
|...|...|...|
__To be finished__: read the files `include/*.h`.

