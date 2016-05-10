#include <fstream>
#include "multisearch.h"
#include "searchquery.h"

MultiSearch::MultiSearch(int number, char** queries){
    searches = new SearchQuery*[number];
    for (int i = 0; i < number; i++){
        searches[i] = new SearchQuery(queries[i]);
    }
}

void MultiSearch::performSearch(char* fileName){
    char fileBuffer[BUFFERSIZE];
    std::ifstream in(fileName);

    unsigned int bufferOffset;
    while (!in.eof()){
        in.read(fileBuffer, BUFFERSIZE);
        unsigned int charactersRead = in.gcount();
        executeSearches(fileBuffer, charactersRead);
        bufferOffset = getBufferOffset();
    }
}

void MultiSearch::executeSearches(char *textBuffer, unsigned int characters){
    return;
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
}
