#ifndef MULTISEARCH_H
#define MULTISEARCH_H

#include "searchquery.h"

#define BUFFERSIZE 4096

class MultiSearch {
    private:
        unsigned int number;
        SearchQuery** searches;
        char trans[ALPHABET_SIZE];

        void buildTransTable();
        void executeSearches(char*, unsigned int);
        unsigned int getBufferOffset();
        float sumOccurrences();
        void resetSearches();

    public:
        float performSearch(const char*);

        MultiSearch(int, char**);
        ~MultiSearch();
};

#endif
