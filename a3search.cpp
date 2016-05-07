#include <iostream>
#include "a3search.h"

int main(int argc, char** argv){
    const char* folder = argv[1];
    const char* indexFile = argv[2];
    unsigned int queries = argc-3;
    if (std::string(argv[3]) == "-s"){
        argv += 2;
        queries -= 2;
    }
    char** searchQueries = argv+3;
    return 0;
}
