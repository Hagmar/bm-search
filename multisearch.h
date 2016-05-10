#ifndef MULTISEARCH_H
#define MULTISEARCH_H

#include "searchquery.h"

#define BUFFERSIZE 4096

class MultiSearch {
    public:
        SearchQuery** searches;

        void performSearch(char*);
        void executeSearches(char*, unsigned int);

        MultiSearch(int, char**);
        ~MultiSearch();
};

#endif
