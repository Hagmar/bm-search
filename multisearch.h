#ifndef MULTISEARCH_H
#define MULTISEARCH_H

#include "searchquery.h"

#define BUFFERSIZE 4096

class MultiSearch {
    private:
        void executeSearches(char*, unsigned int);
        unsigned int getBufferOffset();
        float sumOccurrences();
        void resetSearches();

    public:
        unsigned int number;
        SearchQuery** searches;

        float performSearch(const char*);

        MultiSearch(int, char**);
        ~MultiSearch();
};

#endif
