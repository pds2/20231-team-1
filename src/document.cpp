#include <cstdio>
#include <cctype>
#include <dirent.h>
#include <filesystem>
#include <fstream> 
#include <exception>
#include <string>
#include <unordered_map>
#include <vector>

#include "../lib/document.hpp"

namespace fs = std::filesystem;

DocumentsData::DocumentsData(const char *dir_name) {
    word_to_doc_index = convertToDocumentIndex(word_index);

    // Abre o diretorio
    DIR* dir = opendir(dir_name);
    if (dir == NULL) {
        throw dir_not_found_e();  // Lança uma excecao
    }

    struct dirent* entry;
    int doc_idx = 0; // Contador de índice de documentos
    
    // Cria doc metadata
    DocMetadata doc_metadata;
    
    while ((entry = readdir(dir)) != NULL) { 

        // Le todos os arquivos no dir
        if (entry->d_type == DT_REG) {  // Verificar se a entrada é um arquivo normal            
            std::string filename = entry->d_name;
            fs::path filepath = fs::path(dir_name) / filename;

            // Para cada arquivo em dir, abre e le todas as palavras
            std::ifstream file(filepath);

            std::string word;
            int word_count = 0;
            while (file >> word) {
                // Converte a palavra para minusculo
                for (char& c : word) {
                    c = std::tolower(c);
                }
                
                // Para cada palavra no documento, conta ocorrências
                word_index[word][doc_idx]++;
                word_count++;
            }
            
            // Adiciona para word_index
            doc_metadata.word_count = word_count;
            doc_metadata.name = filename;

            doc_metadatas.insert({doc_idx, doc_metadata});

            doc_idx++;
        }
    }
    closedir(dir);
}

DocumentIndex DocumentsData::convertToDocumentIndex(const std::unordered_map<std::string, std::unordered_map<int, int>>& wordIndex) {
    DocumentIndex docIndex;
    for (const auto& wordEntry : wordIndex) {
        const std::string& word = wordEntry.first;
        const auto& occurrences = wordEntry.second;
        for (const auto& occurrence : occurrences) {
            int docIdx = occurrence.first;
            docIndex[word].push_back(docIdx);
        }
    }
    return docIndex;
}

DocumentIndex& DocumentsData::get_document_index() {
    word_to_doc_index.clear();
    // Mesmos dados de word_index --> não mexer na estrutura
    for (const auto& word_entry : word_index) {
        const std::unordered_map<int, int>& word_counts = word_entry.second;
        for (const auto& wc : word_counts) {
            word_to_doc_index[word_entry.first].push_back(wc.first);
        }
    }
    return word_to_doc_index;
}

int DocumentsData::get_size(int doc_idx) {
    if (doc_metadatas.find(doc_idx) != doc_metadatas.end()) {
        return doc_metadatas[doc_idx].word_count;
    }
    return 0; // Index não encontrado
}

double DocumentsData::get_avg_size() {
    double total_word_count = 0.0;
    int total_docs = doc_metadatas.size();
    for (const auto& pair : doc_metadatas) {
        total_word_count += pair.second.word_count;
    }
    if (total_docs > 0) {
        return total_word_count / total_docs;
    }
    return 0.0; // Nenhum documento encontrado
}

int DocumentsData::get_qt_docs() {
    return doc_metadatas.size();
}

int DocumentsData::get_frequence(std::string term, int doc_idx) {
    if (word_index.find(term) != word_index.end()) {
        const std::unordered_map<int, int>& word_counts = word_index[term];
        for (const auto& wc : word_counts) {
            if (wc.first == doc_idx) {
                return wc.second;
            }
        }
    }
    return 0; // Termo ou documento não encontrado
}

std::string DocumentsData::get_doc_name(int doc_idx) {
    return doc_metadatas[doc_idx].name;
}
