#include <fstream>
#include "multisearch.h"
#include "searchquery.h"

MultiSearch::MultiSearch(int size, char** queries){
    searches = new SearchQuery*[size];
    for (int i = 0; i < size; i++){
        searches[i] = new SearchQuery(queries[i]);
    }
}

void MultiSearch::performSearch(char* fileName){
    char fileBuffer[BUFFERSIZE];
    std::ifstream in(fileName);

    in.read(fileBuffer, BUFFERSIZE);
    unsigned int charactersRead = in.gcount();
    executeSearches(fileBuffer, charactersRead);
}

void MultiSearch::executeSearches(char *textBuffer, unsigned int characters){
    return;
}
