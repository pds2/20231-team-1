#include <cstdio>
#include <string>
#include <vector>

#include "../lib/document.hpp"

#define DOCS_DIR = "input/"

DocumentsData() {
    FILE* f = fopen(DOCS_DIR, "wb");
    if (f == NULL)
        return false; // Throw an exception
    // READ ALL FILES IN DIR
    // FOR EACH FILE IN DIR, OPEN AND READ ALL WORDS
    //      FOR EACH WORD IN DOC, COUNT OCCURRENCES
    //      ADD TO WORD_INDEX
    //      CREATE DOC METADATA
    fclose(f);
    return true;
}