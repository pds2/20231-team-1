#ifndef DOCUMENT_HPP
#define DOCUMENT_HPP

#include <map>
#include <vector>

class Documents {
public:
    static int get_size(int doc_idx);
    static double get_avg_size();
    static int get_qtd_docs();
    static int get_frequence(std::string term, int doc_idx);
};  

using DocumentIndex = std::map<std::string, std::vector<int>>;

#endif
