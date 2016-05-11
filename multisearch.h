#ifndef MULTISEARCH_H
#define MULTISEARCH_H

#include "searchquery.h"

#define BUFFERSIZE 4096

class MultiSearch {
    public:
        unsigned int number;
        SearchQuery** searches;

        void performSearch(const char*);
        void executeSearches(char*, unsigned int);
        unsigned int getBufferOffset();

        MultiSearch(int, char**);
        ~MultiSearch();
};

#endif
