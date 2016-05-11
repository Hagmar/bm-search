#include <iostream>
#include <cstring>
#include "searchquery.h"

SearchQuery::SearchQuery(char* p){
    pattern = p;
    length = strlen(pattern);
    createBCTable();
    status.occurrences = 0;
    status.index = 0;
}

void SearchQuery::createBCTable(){
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

void SearchQuery::search(char* text, unsigned int textLength){
    unsigned int i = status.index;
    unsigned int j;
    while (i <= textLength-length){
        j = length-1;
        while (j != -1 && pattern[j] == text[i+j]){
            j--;
        }
        if (j == -1){
            status.occurrences++;
            i++;
        } else {
            i += j-bcTable[text[i+j]][j];
        }
    }
    status.index = textLength-i;
}
