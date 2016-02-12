# My AVR extra library

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
