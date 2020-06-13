CC=gcc
CFLAGS=-I. -std=c99

all : udpserver udpclient tcpserver tcpclient

udp : udpserver udpclient

tcp : tcpserver tcpclient

udpserver : udpserver.c
	$(CC) -o udpserver udpserver.c $(CFLAGS)

udpclient : udpclient.c
	$(CC) -o udpclient udpclient.c $(CFLAGS)

tcpserver : tcpserver.c
	$(CC) -o tcpserver tcpserver.c $(CFLAGS)

tcpclient : tcpclient.c
	$(CC) -o tcpclient tcpclient.c $(CFLAGS)

clean :
	rm -f udpserver udpclient tcpserver tcpclient