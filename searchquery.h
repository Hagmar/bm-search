#ifndef SEARCHQUERY_H
#define SEARCHQUERY_H

#define ALPHABET_SIZE 256

class SearchQuery {
    private:
        int* bcTable[ALPHABET_SIZE];

        void createBCTable();

    public:
        struct searchStatus {
            unsigned int occurrences;
            int index;
        } status;

        char* pattern;
        unsigned int length;

        void search(unsigned char*, unsigned int, unsigned char[ALPHABET_SIZE]);

        SearchQuery(char*, unsigned char[]);
        ~SearchQuery();
};

#endif
