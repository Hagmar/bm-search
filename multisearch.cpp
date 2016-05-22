#include <fstream>
#include <cstring>
#include <cctype>
#include "multisearch.h"
#include "searchquery.h"

MultiSearch::MultiSearch(int n, char** queries){
    number = n;
    buildTransTable();
    searches = new SearchQuery*[number];
    for (int i = 0; i < number; i++){
        searches[i] = new SearchQuery(queries[i], trans);
    }
}

// Build a translation table to make all characters lower case
void MultiSearch::buildTransTable(){
    for (int i = 0; i < ALPHABET_SIZE; ++i){
        trans[i] = tolower(i);
    }
}

// Search through a file and calculate the average number of occurrences of
// the search terms
float MultiSearch::performSearch(const char* fileName){
    std::ifstream in(fileName);

    unsigned int bufferOffset = 0;
    unsigned int i;
    while (!in.eof()){
        // Retain as much of the last buffer as is required by any search
        // queries currently attempting to match over the end of the buffer
        memcpy(fileBuffer, fileBuffer+BUFFERSIZE-bufferOffset, bufferOffset);
        in.read(fileBuffer+bufferOffset, BUFFERSIZE-bufferOffset);
        unsigned int charactersRead = in.gcount();
        // Make the file contents lower case
        for (i = bufferOffset; i < charactersRead+bufferOffset; i++){
            fileBuffer[i] = trans[fileBuffer[i]];
        }
        // Execute all the searches on the current buffer
        executeSearches(fileBuffer, charactersRead+bufferOffset);
        bufferOffset = getBufferOffset();
    }
    float occurrences = avgOccurrences();
    resetSearches();
    in.close();
    return occurrences;
}

// Run all searches
void MultiSearch::executeSearches(char *textBuffer, unsigned int characters){
    for (unsigned int i = 0; i < number; i++){
        searches[i]->search(textBuffer, characters);
    }
}

// Check which search requires the most of the buffer to be retained
// Update the searches' index with the correct offset for continuing searching
// in the new buffer contents
unsigned int MultiSearch::getBufferOffset(){
    unsigned int maxIndex = 0;
    unsigned int tempIndex;
    unsigned int i;

    for (i = 0; i < number; i++){
        tempIndex = searches[i]->status.index;
        if (tempIndex > maxIndex){
            maxIndex = tempIndex;
        }
    }
    for (i = 0; i < number; i++){
        searches[i]->status.index = maxIndex-searches[i]->status.index;
    }
    return maxIndex;
}

// Calculate the average number of occurrences of the search terms
float MultiSearch::avgOccurrences(){
    float occurrences = 0;
    for (unsigned int i = 0; i < number; i++){
        if (!searches[i]->status.occurrences){
            return 0;
        }
        occurrences += searches[i]->status.occurrences;
    }
    return occurrences/number;
}

// Clear all the searches
void MultiSearch::resetSearches(){
    for (unsigned int i = 0; i < number; i++){
        searches[i]->status.index = 0;
        searches[i]->status.occurrences = 0;
    }
}
