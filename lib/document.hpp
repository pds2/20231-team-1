#ifndef DOCUMENT_HPP
#define DOCUMENT_HPP

#include <vector>
#include <map>

class Document {
public:
    std::map<std::string, int> terms; // Temp representation of a document
};

using DocumentIndex = std::vector<Document>;

#endif
