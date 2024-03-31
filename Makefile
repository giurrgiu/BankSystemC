# -*- Makefile -*-
CC=gcc

main: main.o clients.o commands.o files.o utilities.o
	gcc -g main.o clients.o commands.o files.o utilities.o -o BankSystem
	make clean
	
main.o: main.c
	gcc -c main.c

clients.o: clients.c
	gcc -c clients.c

commands.o: commands.c
	gcc -c commands.c

files.o: files.c
	gcc -c files.c

utilities.o: utilities.c 
	gcc -c utilities.c

clean:
	del main.o clients.o commands.o files.o utilities.o