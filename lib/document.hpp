#ifndef DOCUMENT_HPP
#define DOCUMENT_HPP

#include <map>
#include <string>
#include <vector>

class DocumentsData{
private:
    struct WordCount {
        int doc_idx;
        int frequency;
    };
    struct DocMetadata {
        int word_count;
        std::string name;
    };
    double avg_doc_size;
    std::unordered_map<std::string, std::vector<WordCount>> word_index;
    std::unordered_map<int, DocMetadata> doc_metadata;
public:
    DocumentsData();
    int get_size(int doc_idx); // número de palavras no arquivo
    double get_avg_size(); // número de palavras médio, considerando todos os arquivos
    int get_qt_docs(); // número de documentos na pasta input
    int get_frequence(std::string term, int doc_idx); // frequência de cada termo no arquivo
}

#endif
