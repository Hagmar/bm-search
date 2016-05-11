#ifndef A3SEARCH
#define A3SEARCH

#include "multisearch.h"

std::vector<std::pair<float, char*> > performSearch(MultiSearch*, char*, char*);
bool filesorter(std::pair<float, char*>, std::pair<float, char*>);
void printResults(std::vector<std::pair<float, char* > >);
int main(int, char**);

#endif
