#include <iostream>
#include <sstream>
#include <dirent.h>
#include <vector>
#include <utility>
#include <algorithm>
#include <cstring>
#include "a3search.h"
#include "multisearch.h"

std::vector<std::pair<float, char*> > performSearch(MultiSearch* ms,
        char* folder, char* indexFile){
    DIR *dir;
    dirent *ent;
    std::string folderString(folder);
    folderString += "/";
    std::vector<std::pair<float, char*> > files;
    if ((dir = opendir(folder)) != NULL){
        std::string fileNameString;
        char* fileName;
        float occurrences;
        unsigned int length;
        while ((ent = readdir(dir)) != NULL){
            fileName = ent->d_name;
            fileNameString = std::string(fileName);
            if (fileNameString != "." && fileNameString != ".."){
                fileNameString = folderString + fileNameString;
                occurrences = ms->performSearch(fileNameString.c_str());
                if (occurrences){
                    length = strlen(fileName);
                    char* fileNameDyn = new char[length+1];
                    strncpy(fileNameDyn, fileName, length);
                    fileNameDyn[length] = 0;
                    std::pair <float,char*> pair (occurrences,fileNameDyn);
                    files.push_back(pair);
                }
            }
        }
        closedir(dir);
    }
    return files;
}

bool filesorter(std::pair<float, char*> a, std::pair<float, char*> b){
    if (a.first > b.first){
        return true;
    } else if (a.first < b.first) {
        return false;
    } else {
        int comparison = strcmp(a.second, b.second);
        return comparison < 0;
    }
}

void printResults(std::vector<std::pair<float, char*> > vector){
    std::sort(vector.begin(), vector.end(), filesorter);
    std::vector<std::pair<float, char*> >::iterator it;
    for (it = vector.begin(); it != vector.end(); it++){
        std::cout << (*it).second << " (" << (*it).first << ")" << std::endl;
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

        std::vector<std::pair<float, char*> > results;
        results = performSearch(searchQueries, folder, indexFile);
        printResults(results);
    }

    return 0;
}
