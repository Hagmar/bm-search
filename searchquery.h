#ifndef SEARCHQUERY_H
#define SEARCHQUERY_H

#define ALPHABET_SIZE 256

class SearchQuery {
    private:
        short* bcTable[ALPHABET_SIZE];

        void createBCTable();

    public:
        struct searchStatus {
            unsigned int occurrences;
            int index;
        } status;

        char* pattern;
        unsigned int length;

        void search(char*, unsigned int, char[ALPHABET_SIZE]);

        SearchQuery(char*, char[]);
        ~SearchQuery();
};

#endif
