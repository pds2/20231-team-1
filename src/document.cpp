#include <cstdio>
#include <cctype>
#include <dirent.h>
#include <exception>
#include <string>
#include <unordered_map>
#include <vector>

#include "../lib/document.hpp"

//#define DOCS_DIR "../input/"

DocumentsData::DocumentsData(const char *dir_name) {
    word_to_doc_index = convertToDocumentIndex(word_index);

    // OPEN DIR
    DIR* dir = opendir(dir_name);
    if (dir == NULL) {
        throw dir_not_found_e();  // Throw an exception
    }

    struct dirent* entry;
    int doc_idx = 0; // Document index counter
    while ((entry = readdir(dir)) != NULL) { // TODO - determinístico?

        // READ ALL FILES IN DIR
        if (entry->d_type == DT_REG) {  // Check if entry is a regular file
            std::string filename = entry->d_name;
            std::string filepath = std::string(dir_name) + filename;

            // FOR EACH FILE IN DIR, OPEN AND READ ALL WORDS
            FILE* file = fopen(filepath.c_str(), "r");
            if (file == NULL) {
                throw file_not_found_e();  // Throw an exception
                continue;
            }

            std::string word;
            //word.resize(100); // buffer --> consertar

            while (fscanf(file, "%s", &word[0]) != EOF) {
                // Convert the word to lowercase --> TODO
                for (char& c : word) {
                    c = std::tolower(c);
                }
                
                // FOR EACH WORD IN DOC, COUNT OCCURRENCES
                word_index[word][doc_idx]++;
            }
            fclose(file);
            
            // CREATE DOC METADATA
            DocMetadata doc_metadata;
            // ADD TO WORD_INDEX
            doc_metadata.word_count = word_index.size();
            doc_metadata.name = filename;

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
    if (doc_metadata.find(doc_idx) != doc_metadata.end()) {
        return doc_metadata[doc_idx].word_count;
    }
    return 0; // Index não encontrado
}

double DocumentsData::get_avg_size() {
    double total_word_count = 0.0;
    int total_docs = doc_metadata.size();
    for (const auto& pair : doc_metadata) {
        total_word_count += pair.second.word_count;
    }
    if (total_docs > 0) {
        return total_word_count / total_docs;
    }
    return 0.0; // Nenhum documento encontrado
}

int DocumentsData::get_qt_docs() {
    return doc_metadata.size();
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