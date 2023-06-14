#ifndef DOCUMENT_HPP
#define DOCUMENT_HPP

#include <unordered_map>
#include <map>
#include <vector>
#include <string>

class Document {
public:
    std::unordered_map<std::string, int> terms; // Temp representation of a document
};

using DocumentIndex = std::map<std::string, std::vector<int>>;

#endif
