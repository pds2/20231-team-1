#ifndef INVERTED_LIST_HPP
#define INVERTED_LIST_HPP

#include <cstdio>
#include <vector>
#include <string>

#include "document.hpp"

// Define the posting_list class
class posting_list : public std::vector<int> {
    // Add any additional members or functions as needed
};

class InvertedList : public std::vector<posting_list> {
public:
    InvertedList() {}
    InvertedList(const std::string& filename) : _filename(filename) {}
    void set_file_name(const std::string& filename) {}
    bool write_to_disk();
    bool load_from_disk();
    void new_posting_list() {}
private:
    std::string _filename;
    using index_unit = int;
    struct posting_meta {
        int index;
        int length;
    };
};

#endif
