ULFIUS_LOCATION=lib/ulfius
CC=gcc
BUILD_DIR=build
CFLAGS+=-c -Wall -D_REENTRANT $(ADDITIONALFLAGS) $(CPPFLAGS)
LIBS=-L$(LIBYDER_LOCATION) -lc -ljansson -lulfius -lorcania -L$(ULFIUS_LOCATION)
CFILES=crypto_core_driver.c callbacks.c error_util.c json_response_utils.c commands/set_flags.c commands/sign_transaction.c commands/do_pow.c commands/generate_address.c commands/generate_random_seed.c commands/attach_to_tangle.c commands/test_hardware_acceleration.c
OFILES=crypto_core_driver.o callbacks.o error_util.o json_response_utils.o set_flags.o sign_transaction.o do_pow.o generate_address.o generate_random_seed.o attach_to_tangle.o test_hardware_acceleration.o

ifndef YDERFLAG
LIBS+=-lyder
endif

all: crypto_core_driver

clean:
	rm -f *.o crypto_core_driver

debug: ADDITIONALFLAGS=-DDEBUG -g -O0

debug: crypto_core_driver

libulfius.so:
	cd $(ULFIUS_LOCATION) && $(MAKE) debug CURLFLAG=1 GNUTLSFLAG=1

crypto_core_driver.o: src/crypto_core_driver.c
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && $(CC) -I../include -I../lib $(CFLAGS) $(foreach file,$(CFILES),../src/$(file)) -DDEBUG -g -O0

crypto_core_driver: libulfius.so crypto_core_driver.o
	cd $(BUILD_DIR) && $(CC) -o crypto_core_driver $(OFILES) $(LIBS)

test: crypto_core_driver
	LD_LIBRARY_PATH=$(ULFIUS_LOCATION):${LD_LIBRARY_PATH} ./$(BUILD_DIR)/crypto_core_driver

static: crypto_core_driver.o
	$(CC) -o crypto_core_driver $(OFILES) $(PREFIX)/lib/liborcania.a $(PREFIX)/lib/libyder.a $(PREFIX)/lib/libulfius.a -ljansson -lmicrohttpd -lpthread -lgnutls
