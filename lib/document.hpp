#ifndef DOCUMENT_HPP
#define DOCUMENT_HPP

#include <map>
#include <vector>

class DocumentsData{
public:
    int get_size(int doc_idx);
    double get_avg_size();
    int get_qt_docs();
    int get_frequence(std::string term, int doc_idx);
};  

using DocumentIndex = std::map<std::string, std::vector<int>>;

#endif
