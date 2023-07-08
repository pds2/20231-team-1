#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <doctest/doctest.h>
#include <exception>
#include <filesystem>
#include <iostream>
#include <set>

#include "../lib/document.hpp"

#include "utils.cpp"

namespace fs = std::filesystem;

using DocumentNames = std::map<std::string, std::vector<std::string>>;

TEST_CASE("01 - Inverted List Test without a valid dir") {
    DOCTEST_CHECK_THROWS_AS(DocumentsData("../include/"), dir_not_found_e);
}


// Compare two index
bool compareDocumentIndex(DocumentNames& names, DocumentIndex& index) {
    if (names.size() != index.size())
        return false;

    for (const auto& [word, doc_names_1] : names) {
        auto it = index.find(word);
        if (it == index.end())
            return false;

        const auto& doc_indices_2 = it->second;

        if (doc_names_1.size() != doc_indices_2.size())
            return false;

        for (size_t i = 0; i < doc_names_1.size(); i++) {
            int doc_idx = doc_indices_2[i];

            std::string doc_name_1 = doc_names_1[i];
            std::string doc_name_2 = std::to_string(doc_idx) + ".txt";
            std::cout << doc_name_2 << " , 2: " << doc_name_1 << std::endl;

            if (doc_name_1 != doc_name_2)
                return false;
        }
    }

    return true;
}

TEST_CASE("02 - Test with a temporary directory") {
    fs::path tmp_dir = fs::temp_directory_path() / "test_inverted_list";
    std::map<std::string, std::string> temp_corpus{{"0.txt", "test one"}, {"1.txt", "test two"}, {"2.txt", "test three"}};
    utils::create_temp_corpus(tmp_dir, temp_corpus);

    DocumentNames names = {{"test", {"0.txt", "1.txt", "2.txt"}}, 
                           {"one" , {"0.txt"}}, {"two" , {"1.txt"}}, 
                           {"three", {"2.txt"}}};

    DocumentsData data(tmp_dir.c_str());

    CHECK(compareDocumentIndex(names, data.get_document_index()));

    fs::remove_all(tmp_dir);
}