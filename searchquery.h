#ifndef SEARCHQUERY_H
#define SEARCHQUERY_H

class SearchQuery {
    public:
        char* pattern;

        SearchQuery(char*);
        ~SearchQuery();
};

#endif
