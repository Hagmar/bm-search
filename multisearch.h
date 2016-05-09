#ifndef MULTISEARCH_H
#define MULTISEARCH_H

#include "searchquery.h"

class MultiSearch {
    public:
        SearchQuery** searches;

        MultiSearch(int, char**);
        ~MultiSearch();
};

#endif
