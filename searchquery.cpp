#include <cstring>
#include "searchquery.h"

SearchQuery::SearchQuery(char* p){
    pattern = p;
    createBCTable();
}

void SearchQuery::createBCTable(){
    unsigned int length = strlen(pattern);
    for (int i = 0; i < ALPHABET_SIZE; i++){
        bcTable[i] = new short[length];
        memset(bcTable[i], -1, length*sizeof(unsigned short));
    }

    char c;
    for (int i = 0; i < length-1; i++){
        c = pattern[i];
        for (int j = 0; j < ALPHABET_SIZE; j++){
            bcTable[j][i+1] = bcTable[j][i];
        }
        bcTable[c][i+1] = i;
    }
}
