# the compiler and linker are specified below

CC = g++ -std=c++11
CF = -c
OF = -o

all: test_rbtree test_firewall

test_firewall: test_firewall.o firewall.o
	$(CC) $(OF) test_firewall test_firewall.o firewall.o

test_rbtree: test_rbtree.o
	$(CC) $(OF) test_rbtree test_rbtree.o

test_rbtree.o: ./rbtree/test_rbtree.cc ./rbtree/rbtree.h ./rbtree/rbtree.cc
	$(CC) $(CF) ./rbtree/test_rbtree.cc

test_firewall.o: ./firewall/test_firewall.cc ./firewall/firewall.cc ./firewall/firewall.h
	$(CC) $(CF) ./firewall/test_firewall.cc

firewall.o: ./firewall/firewall.cc ./firewall/firewall.h
	$(CC) $(CF) ./firewall/firewall.cc


clean:
	rm *.o
