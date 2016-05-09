#include <iostream>
#include <sstream>
#include "a3search.h"
#include "multisearch.h"

int main(int argc, char** argv){
    const char* folder = argv[1];
    const char* indexFile = argv[2];
    unsigned int queries = argc-3;
    int sSize = 20;
    if (std::string(argv[3]) == "-s"){
        std::stringstream(argv[4]) >> sSize;
        argv += 2;
        queries -= 2;
    }
    MultiSearch* searchQueries = new MultiSearch(argc-3, argv+3);
    return 0;
}
