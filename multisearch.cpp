#include "multisearch.h"
#include "searchquery.h"

MultiSearch::MultiSearch(int size, char** queries){
    searches = new SearchQuery*[size];
    for (int i = 0; i < size; i++){
        searches[i] = new SearchQuery(queries[i]);
    }
}
