#include <fstream>
#include <cstring>
#include "multisearch.h"
#include "searchquery.h"

MultiSearch::MultiSearch(int n, char** queries){
    number = n;
    searches = new SearchQuery*[number];
    for (int i = 0; i < number; i++){
        searches[i] = new SearchQuery(queries[i]);
    }
}

void MultiSearch::performSearch(const char* fileName){
    char fileBuffer[BUFFERSIZE];
    std::ifstream in(fileName);

    unsigned int bufferOffset = 0;
    while (!in.eof()){
        in.read(fileBuffer+bufferOffset, BUFFERSIZE-bufferOffset);
        unsigned int charactersRead = in.gcount();
        executeSearches(fileBuffer, charactersRead);
        bufferOffset = getBufferOffset();
        memcpy(fileBuffer, fileBuffer-bufferOffset, bufferOffset);
    }
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
