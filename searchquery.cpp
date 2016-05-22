#include <iostream>
#include <cstring>
#include "searchquery.h"

SearchQuery::SearchQuery(char* p, unsigned char trans[ALPHABET_SIZE]){
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

// Generate the bad-character table for the search pattern
// Uses the full, two-dimensional table of the Boyer-Moore algorithm, not the
// one-dimensional one of the simplified Boyer-Moore-Horspool algorithm
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

// Perform Boyer-Moore search on the file contents
void SearchQuery::search(unsigned char* text, unsigned int textLength, unsigned char trans[ALPHABET_SIZE]){
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
        while ((i += j-bcTable[trans[text[i+j]]][j]) < textLength-length);

        // Restore BC-table
        bcTable[pattern[j]][j] = tempBCEntry;

        // Check if end of text has been reached
        if (i < textLength+1){
            break;
        }

        // Restore i
        i -= j + textLength + 1;

        // Check for match at position i
        while (j != -1 && pattern[j] == trans[text[i+j]]){
            j--;
        }
        if (j == -1){
            status.occurrences++;
            i++;
        } else {
            i += j-bcTable[trans[text[i+j]]][j];
        }
    }
    // Maintain next matching position
    status.index = textLength-i;
}
