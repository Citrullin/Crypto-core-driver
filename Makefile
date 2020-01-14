LIB_DIR=lib
ULFIUS_DIR=$(LIB_DIR)/ulfius
ORCANIA_DIR=$(LIB_DIR)/orcania
MICROHTTPD_DIR=$(LIB_DIR)/microhttpd
YDER_DIR=$(LIB_DIR)/yder
JANSSON_DIR=$(LIB_DIR)/jansson
GNUTLS_DIR=$(LIB_DIR)/gnutls
NETTLE_DIR=$(LIB_DIR)/nettle
LIBTASN_DIR=$(LIB_DIR)/libtasn1
CC=gcc
BUILD_DIR=build
CFLAGS+=-c -Wall -D_REENTRANT $(ADDITIONALFLAGS) $(CPPFLAGS)
LIBS=-L$(BUILD_DIR) -lc -lulfius -ljansson -lorcania -lyder -lmicrohttpd -lpthread
CFILES=crypto_core_driver.c callbacks.c error_util.c json_response_utils.c uart.c commands/set_flags.c commands/sign_transaction.c commands/do_pow.c commands/generate_address.c commands/generate_random_seed.c commands/attach_to_tangle.c commands/test_hardware_acceleration.c commands/json_data_tx.c
OFILES=crypto_core_driver.o callbacks.o error_util.o json_response_utils.o uart.o set_flags.o sign_transaction.o do_pow.o generate_address.o generate_random_seed.o attach_to_tangle.o test_hardware_acceleration.o json_data_tx.o


all: crypto_core_driver

clean:
	rm -f *.o crypto_core_driver

debug: ADDITIONALFLAGS=-DDEBUG -g -O0

debug: crypto_core_driver

jansson.a:
	cd $(JANSSON_DIR) && autoreconf -i && ./configure && $(MAKE)

liborcania.a:
	cd $(ORCANIA_DIR)/src && make static

yder.a:
	cd $(YDER_DIR)/src && $(MAKE) static

bison:
	cd $(BUILD_DIR) && wget https://ftp.gnu.org/gnu/bison/bison-3.5.tar.xz && tar -xvf bison-3.5.tar.xz && cd bison-3.5
	./configure && make && make install

libtasn1.a:
	cd $(LIBTASN_DIR) && ./bootstrap && ./configure --disable-doc && $(MAKE) && $(MAKE) install

#Fixme: Pass include directory for liborcania static library and header files
libulfius.a:
	cd $(ULFIUS_DIR) && $(MAKE) CFLAGS='-I ../../gnutls/lib/includes -lcurl -c -pedantic -std=gnu99 -fPIC -Wall -Werror -Wextra -D_REENTRANT -I../include -O3'

libmicrohttpd.a:
	cd $(MICROHTTPD_DIR) && ./bootstrap && ./configure && $(MAKE)

#Fixme: fix static library for nettle
libgnutls.a:
	cd $(GNUTLS_DIR) && ./bootstrap && ./configure --disable-doc --enable-static --with-included-unistring && $(MAKE)

libnettle.a:
	cd $(NETTLE_DIR) && ./.bootstrap && ./configure --disable-documentation && $(MAKE) libnettle.a

#Fixme: Create build system and use /libname/xxx.h name pattern
crypto_core_driver.o: src/crypto_core_driver.c
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && $(CC) -I../include -I../lib -I../lib/ulfius/include $(CFLAGS) $(foreach file,$(CFILES),../src/$(file)) -DDEBUG -g -O0

crypto_core_driver: libtasn1.a jansson.a libmicrohttpd.a libulfius.a liborcania.a yder.a crypto_core_driver.o
	cp $(MICROHTTPD_DIR)/src/microhttpd/.libs/libmicrohttpd.a $(BUILD_DIR)/
	cp $(JANSSON_DIR)/src/libjansson.a $(BUILD_DIR)/
	cp $(YDER_DIR)/src/libyder.a $(BUILD_DIR)/
	cp $(ORCANIA_DIR)/src/liborcania.a $(BUILD_DIR)/
	cp $(ULFIUS_DIR)/src/libulfius.a $(BUILD_DIR)/
	cp $(NETTLE_DIR)/src/libnettle.a $(BUILD_DIR)/
	cd $(BUILD_DIR) && $(CC) -o crypto_core_driver $(OFILES) $(LIBS)

test: crypto_core_driver
	LD_LIBRARY_PATH=$(ULFIUS_LOCATION):${LD_LIBRARY_PATH} ./$(BUILD_DIR)/crypto_core_driver

#Fixme: Add static librarys. Copy them into build and link them. Basiclly: simple build system
#Fixme: Fix -lgnutls
static: crypto_core_driver.o
	cd $(BUILD_DIR) && $(CC) -o crypto_core_driver $(OFILES) $(LIBS)
