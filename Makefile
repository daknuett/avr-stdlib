CC=avr-gcc
INCDIR=`pwd`/include
std_LIBDIR = ./lib

include config/Makefile.inc

%.elf: %.c libs
	$(CC) $(CFLAG) $@ $(LIBS) $<
i%.elf: %.elf
	avrdude -p '$(DEVICE)' -c avrispmkii  -U flash:w:$<:a

clean:
	cd lib/ && make clean && cd ..

libs:
	cd lib && make -s || make


CONFIGDIR = `pwd`/config
SUBCONFIGDIRS = lib/m168/config lib/m8/config lib/config lib/extra/config
SUBCONFIG_LINKS = $(addsuffix /project_config,$(SUBCONFIGDIRS)) 

init_mkdirs: $(SUBCONFIGDIRS)

$(SUBCONFIGDIRS):
	mkdir -p $@

init: $(SUBCONFIG_LINKS)

$(SUBCONFIG_LINKS):
	echo "GLOBAL_CONFIG = $(CONFIGDIR)" >  $@

uninit: 
	find . -name project_config -exec rm -f {} \;
