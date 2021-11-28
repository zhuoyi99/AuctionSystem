CC=gcc
CFLAGS=-Iinclude -Wall -Werror -ggdb -Wno-unused 

SSRC=$(shell find src -name '*.c')
DEPS=$(shell find include -name '*.h')

LIBS=-lpthread

all: server

setup:
	mkdir -p bin

server: setup $(DEPS) 
	$(CC) $(CFLAGS)  $(SSRC) lib/protocol.o -o bin/zbid_server $(LIBS) 
	cp lib/zbid_client bin 
	cp lib/auctionroom bin

run_server:
	./bin/zbid_server 3200 rsrc/auction1.txt

run_client1:
	./bin/zbid_client "peter" zotzot 127.0.0.1 3200

.PHONY: clean

clean:
	rm -rf bin 
