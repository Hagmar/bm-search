#ifndef MULTISEARCH_H
#define MULTISEARCH_H

#include "searchquery.h"

#define BUFFERSIZE 4096

class MultiSearch {
    public:
        unsigned int number;
        SearchQuery** searches;

        unsigned int performSearch(const char*);
        void executeSearches(char*, unsigned int);
        unsigned int getBufferOffset();
        unsigned int sumOccurrences();
        void resetSearches();

        MultiSearch(int, char**);
        ~MultiSearch();
};

#endif
