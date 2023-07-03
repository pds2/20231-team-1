#include <cstdio>
#include <string>
#include <vector>

#include "../lib/inverted_list.hpp"

bool InvertedList::write_to_disk() {
    if (_filename.empty()) {
        throw no_file_name_e(); // Throw an exception for an empty file name
        return false;
    }
    FILE* f = fopen(_filename.c_str(), "wb");
    if (f == NULL) {
        return false; // Throw an exception
    }
    for (size_t i = 0; i < size(); ++i) {
        posting_meta block = {static_cast<int>(i), static_cast<int>((*this)[i].size())};
        if (fwrite(&block, sizeof(block), 1, f) != 1 ||
            fwrite(&(*this)[i][0], sizeof(index_unit), block.length, f) != static_cast<size_t>(block.length)) {
            perror("An error occurred while writing inverted list!"); // Handle error
            return false;
        }
    }
    fclose(f);
    return true;
}

bool InvertedList::load_from_disk() {
    if (_filename.empty()) {
        throw no_file_name_e(); // Throw an exception for an empty file name
        return false;
    }
    FILE* f = fopen(_filename.c_str(), "rb");
    if (f == NULL)
        return false;
    posting_meta block;
    this->clear();
    while (fread(&block, sizeof(block), 1, f) == 1) {
        resize(size() + 1);
        this->back().resize(block.length);
        if (fread(&this->back()[0], sizeof(index_unit), block.length, f) != static_cast<size_t>(block.length)) {
            perror("An error occurred while reading inverted list!"); // Handle error
            return false;
        }
    }
    fclose(f);
    return true;
}
