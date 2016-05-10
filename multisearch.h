#ifndef MULTISEARCH_H
#define MULTISEARCH_H

#include "searchquery.h"

class MultiSearch {
    public:
        SearchQuery** searches;

        void performSearch(char*);

        MultiSearch(int, char**);
        ~MultiSearch();
};

#endif
