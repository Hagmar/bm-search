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

void MultiSearch::buildTransTable(){
    for (int i = 0; i < ALPHABET_SIZE; ++i){
        trans[i] = tolower(i);
    }
}

float MultiSearch::performSearch(const char* fileName){
    char fileBuffer[BUFFERSIZE];
    std::ifstream in(fileName);

    unsigned int bufferOffset = 0;
    unsigned int i;
    while (!in.eof()){
        memcpy(fileBuffer, fileBuffer+BUFFERSIZE-bufferOffset, bufferOffset);
        in.read(fileBuffer+bufferOffset, BUFFERSIZE-bufferOffset);
        unsigned int charactersRead = in.gcount();
        for (i = bufferOffset; i < BUFFERSIZE; i++){
            fileBuffer[i] = trans[fileBuffer[i]];
        }
        executeSearches(fileBuffer, charactersRead+bufferOffset);
        bufferOffset = getBufferOffset();
    }
    float occurrences = sumOccurrences();
    resetSearches();
    in.close();
    return occurrences;
}

void MultiSearch::executeSearches(char *textBuffer, unsigned int characters){
    for (unsigned int i = 0; i < number; i++){
        searches[i]->search(textBuffer, characters);
    }
}

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

float MultiSearch::sumOccurrences(){
    float occurrences = 0;
    for (unsigned int i = 0; i < number; i++){
        if (!searches[i]->status.occurrences){
            return 0;
        }
        occurrences += searches[i]->status.occurrences;
    }
    return occurrences/number;
}

void MultiSearch::resetSearches(){
    for (unsigned int i = 0; i < number; i++){
        searches[i]->status.index = 0;
        searches[i]->status.occurrences = 0;
    }
}
