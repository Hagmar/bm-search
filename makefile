CC=g++

all: a3search

a3search: a3search.cpp a3search.h
	$(CC) -o a3search a3search.cpp
