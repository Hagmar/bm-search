#include <iostream>
#include <sstream>
#include <dirent.h>
#include "a3search.h"
#include "multisearch.h"

void performSearch(MultiSearch* ms, char* folder, char* indexFile){
    DIR *dir;
    dirent *ent;
    std::string folderString(folder);
    folderString += "/";
    if ((dir = opendir(folder)) != NULL){
        std::string fileNameString;
        char* fileName;
        float occurrences;
        while ((ent = readdir(dir)) != NULL){
            fileName = ent->d_name;
            fileNameString = std::string(fileName);
            if (fileNameString != "." && fileNameString != ".."){
                fileNameString = folderString + fileNameString;
                occurrences = ms->performSearch(fileNameString.c_str());
            }
        }
        closedir(dir);
    }
}

int main(int argc, char** argv){
    if (argc < 4){
        std::cerr << "Error, wrong numer of arguments" << std::endl;
        return -1;
    } else {
        char* folder = argv[1];
        char* indexFile = argv[2];
        int sSize = 20;
        if (std::string(argv[3]) == "-s"){
            std::stringstream(argv[4]) >> sSize;
            argv += 2;
            argc -= 2;
        }
        MultiSearch* searchQueries = new MultiSearch(argc-3, argv+3);

        performSearch(searchQueries, folder, indexFile);
    }

    return 0;
}
