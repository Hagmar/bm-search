#include <iostream>
#include <cstring>
#include "searchquery.h"

SearchQuery::SearchQuery(char* p, char trans[ALPHABET_SIZE]){
    pattern = p;
    unsigned int i;
    for (i = 0; pattern[i]; i++){
        pattern[i] = trans[pattern[i]];
    }
    length = i;
    createBCTable();
    status.occurrences = 0;
    status.index = 0;
}

void SearchQuery::createBCTable(){
    for (int i = 0; i < ALPHABET_SIZE; i++){
        bcTable[i] = new int[length];
        memset(bcTable[i], -1, length*sizeof(unsigned int));
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
    if (textLength < length){
        return;
    }
    unsigned int i = status.index;
    unsigned int j;
    unsigned int tempBCEntry = bcTable[pattern[length-1]][length-1];
    while (i <= textLength-length){
        j = length-1;
        // Skip-loop to skip to skip unnecessary comparisons
        bcTable[pattern[j]][j] = -textLength-1;
        while ((i += j-bcTable[text[i+j]][j]) < textLength-length);

        // Check if end of text has been reached
        if (i < textLength+1){
            break;
        }

        // Restore BC-table and i
        bcTable[pattern[length-1]][j] = tempBCEntry;
        i -= j + textLength + 1;

        // Check for match at position i
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
