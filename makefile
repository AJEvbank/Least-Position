all:
	mpicc -Wall main.c main.h functions.c -o main -lm
