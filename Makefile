ULFIUS_LOCATION=lib/ulfius
ORCANIA_LOCATION=lib/orcania
CC=gcc
BUILD_DIR=build
CFLAGS+=-c -Wall -D_REENTRANT $(ADDITIONALFLAGS) $(CPPFLAGS)
LIBS=-L$(LIBYDER_LOCATION) -lc -lulfius -ljansson -lorcania -lyder -lmicrohttpd -lpthread -L$(ULFIUS_LOCATION) -L
CFILES=crypto_core_driver.c callbacks.c error_util.c json_response_utils.c uart.c commands/set_flags.c commands/sign_transaction.c commands/do_pow.c commands/generate_address.c commands/generate_random_seed.c commands/attach_to_tangle.c commands/test_hardware_acceleration.c
OFILES=crypto_core_driver.o callbacks.o error_util.o json_response_utils.o uart.o set_flags.o sign_transaction.o do_pow.o generate_address.o generate_random_seed.o attach_to_tangle.o test_hardware_acceleration.o

ifndef YDERFLAG
LIBS+=-lyder
endif

all: crypto_core_driver

clean:
	rm -f *.o crypto_core_driver

debug: ADDITIONALFLAGS=-DDEBUG -g -O0

debug: crypto_core_driver

liborcania.a:
	make static

#Fixme: Pass include directory for liborcania static library and header files
libulfius.so:
	cd $(ULFIUS_LOCATION) && $(MAKE) debug CURLFLAG=1 GNUTLSFLAG=1

#Fixme: Create build system and use /libname/xxx.h name pattern
crypto_core_driver.o: src/crypto_core_driver.c
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && $(CC) -I../include -I../lib -I../lib/ulfius/include $(CFLAGS) $(foreach file,$(CFILES),../src/$(file)) -DDEBUG -g -O0

crypto_core_driver: libulfius.so liborcania.a crypto_core_driver.o
	cd $(BUILD_DIR) && $(CC) -o crypto_core_driver $(OFILES) $(LIBS)

test: crypto_core_driver
	LD_LIBRARY_PATH=$(ULFIUS_LOCATION):${LD_LIBRARY_PATH} ./$(BUILD_DIR)/crypto_core_driver

#Fixme: Add static librarys. Copy them into build and link them. Basiclly: simple build system
#Fixme: Fix -lgnutls
static: crypto_core_driver.o
	cd $(BUILD_DIR) && $(CC) -o crypto_core_driver $(OFILES) $(LIBS)
