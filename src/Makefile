CC = g++
OPT = -g -Wall -O3 -Wno-unused-function -Wno-unused-variable -std=c++11

all: othello

othello: main.o
	$(CC) -o $@ $^

othello.o: main.cc othello_cut.h negamax.h scout.h
	$(CC) $(OPT) $<

.PHONY: clean

clean:
	rm -f othello *.o *.txt