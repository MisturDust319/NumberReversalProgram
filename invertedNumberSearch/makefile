#default compiler:
CC=g++
#Compiler flags
CFLAGS=-c -Wall

all: invertedNumberSearch
	@echo 'Running makefile for invertedNumberSearch'

invertedNumberSearch: invertedNumberSearch.o outputHandler.o
	@echo 'Linking files'
	$(CC) invertedNumberSearch.o outputHandler.o -o invertedNumberSearch

invertedNumberSearch.o: invertedNumberSearch.cpp
	@echo 'Compiling invertedNumberSearch.cpp'
	$(CC) $(CFLAGS) invertedNumberSearch.cpp

outputHandler.o: outputHandler.cpp
	@echo 'Compiling outputHandler.cpp'
	$(CC) $(CFLAGS) outputHandler.cpp

clean:
	@echo 'Cleaning solution'
	remove *.o invertedNumberSearch 
