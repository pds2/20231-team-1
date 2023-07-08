#ifndef DOCUMENT_HPP
#define DOCUMENT_HPP

#include <map>
#include <string>
#include <unordered_map>
#include <vector>

class dir_not_found_e {};

using DocumentIndex = std::map<std::string, std::vector<int>>;

class DocumentsData{
private:
    struct DocMetadata {
        int word_count;
        std::string name;
    };

    // TODO
    //double avg_doc_size; 
    DocumentIndex word_to_doc_index;

    std::unordered_map<std::string, std::unordered_map<int, int>> word_index;
    std::unordered_map<int, DocMetadata> doc_metadatas;
    DocumentIndex convertToDocumentIndex(const std::unordered_map<std::string, std::unordered_map<int, int>>& wordIndex); // private

public:
    DocumentsData(const char *dir_name);
    DocumentIndex& get_document_index();
    int get_size(int doc_idx); // número de palavras no arquivo
    double get_avg_size(); // número de palavras médio, considerando todos os arquivos
    int get_qt_docs(); // número de documentos na pasta input
    int get_frequence(std::string term, int doc_idx); // frequência de cada termo no arquivo
    std::string get_doc_name(int doc_idx); // fornece o nome do arquivo de um dado index
};

#endif
