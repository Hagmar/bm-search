CC=g++

all: a3search

debug: CCFLAGS=-g3
debug: clean all

a3search: a3search.cpp a3search.h multisearch.o
	$(CC) $(CCFLAGS) -o a3search a3search.cpp multisearch.o searchquery.o

multisearch.o: multisearch.cpp multisearch.h searchquery.o
	$(CC) $(CCFLAGS) -c multisearch.cpp

searchquery.o: searchquery.cpp searchquery.h
	$(CC) $(CCFLAGS) -c searchquery.cpp

clean:
	rm *.o
