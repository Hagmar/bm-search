#ifndef SEARCHQUERY_H
#define SEARCHQUERY_H

#define ALPHABET_SIZE 256

class SearchQuery {
    private:
        short* bcTable[ALPHABET_SIZE];

        void createBCTable();

    public:
        char* pattern;

        SearchQuery(char*);
        ~SearchQuery();
};

#endif
