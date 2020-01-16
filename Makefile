LIB_DIR=lib
ULFIUS_DIR=$(LIB_DIR)/ulfius
ORCANIA_DIR=$(LIB_DIR)/orcania
JANSSON_DIR=$(LIB_DIR)/jansson
YDER_DIR=$(LIB_DIR)/yder
CC=gcc
BUILD_DIR=build
CFLAGS+=-c -Wall -D_REENTRANT $(ADDITIONALFLAGS) $(CPPFLAGS)
LIBS=-L$(LIBYDER_LOCATION) -lc -lulfius -ljansson -lorcania -lyder -lmicrohttpd -lpthread -L$(ULFIUS_LOCATION) -L
CFILES=crypto_core_driver.c callbacks.c error_util.c json_response_utils.c uart.c commands/set_flags.c commands/sign_transaction.c commands/do_pow.c commands/generate_address.c commands/generate_random_seed.c commands/attach_to_tangle.c commands/test_hardware_acceleration.c commands/json_data_tx.c
OFILES=crypto_core_driver.o callbacks.o error_util.o json_response_utils.o uart.o set_flags.o sign_transaction.o do_pow.o generate_address.o generate_random_seed.o attach_to_tangle.o test_hardware_acceleration.o json_data_tx.o
INCLUDE=-I../lib/jansson/src -I../lib/orcania/include -I../lib/ulfius/include -I../lib/yder/include

ifndef YDERFLAG
LIBS+=-lyder
endif

all: crypto_core_driver

clean:
	rm -f *.o crypto_core_driver

debug: ADDITIONALFLAGS=-DDEBUG -g -O0

debug: crypto_core_driver

jansson.a:
	cd $(JANSSON_DIR) && autoreconf -i && ./configure && $(MAKE)

liborcania.a:
	cd $(ORCANIA_DIR) && $(MAKE) install

yder.a:
	cd $(YDER_DIR)/src && $(MAKE) install

#Fixme: Pass include directory for liborcania static library and header files
libulfius.so:
	cd $(ULFIUS_DIR) && $(MAKE) debug CURLFLAG=1 GNUTLSFLAG=1 && make install

#Fixme: Create build system and use /libname/xxx.h name pattern
crypto_core_driver.o: src/crypto_core_driver.c
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && $(CC) -Iinclude $(INCLUDE) $(CFLAGS) $(foreach file,$(CFILES),../src/$(file)) -DDEBUG -g -O0

crypto_core_driver: yder.a jansson.a liborcania.a libulfius.so crypto_core_driver.o
	cd $(BUILD_DIR) && $(CC) -o crypto_core_driver $(OFILES) $(LIBS) -I libs

test: crypto_core_driver
	LD_LIBRARY_PATH=$(ULFIUS_DIR):${LD_LIBRARY_PATH} ./$(BUILD_DIR)/crypto_core_driver

#Fixme: Add static librarys. Copy them into build and link them. Basiclly: simple build system
#Fixme: Fix -lgnutls
static: crypto_core_driver.o
	cd $(BUILD_DIR) && $(CC) -o crypto_core_driver $(OFILES) $(LIBS)
