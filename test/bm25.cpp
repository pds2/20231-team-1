#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include <filesystem>

#include "../lib/document.hpp"
#include "../lib/bm25.hpp"
#include "utils.cpp"

DocumentIndex idx_docs = {
        {"this", {0, 1}},
        {"is", {0, 1}},
        {"a", {0}},
        {"sample", {0}},
        {"another", {1}},
        {"example", {1}},
};

// temp file path 
fs::path temp = fs::temp_directory_path() / "test_bm25";

// File name -> File content
std::map<std::string, std::string> documents = {
    {"0.txt", "this is a sample a\n"},
    {"1.txt", "another example this is example another example\n"}
};

TEST_CASE("Test 1 - bm25 weighting"){
    utils::create_temp_corpus(temp, documents);

    DocumentsData data(temp.c_str());
    Bm25 weighter(idx_docs, data);

    //TODO: Remove print lines
    // Waiting for the tests of documentsdata class 
    std::cout << "AVG: " << data.get_avg_size() << std::endl;
    for(int i = 0; i < data.get_qt_docs(); i++){
        std::cout << "SIZE: " << data.get_size(i) << std::endl;

        for(auto term: idx_docs){
            std::cout << "------------- " << term.first << std::endl;
            std::cout << "FREQUENCE " << term.first << ": " << data.get_frequence(term.first, i) << std::endl;
            std::cout << "WEIGHT: " << weighter.get_weight(i, term.first) << std::endl;        
        }
    }


    double val_weight = weighter.get_weight(0, "example");

    // First weight must be equal 0
    double val_expected = 0.0;
    CHECK(fabs(val_weight - val_expected) <= std::numeric_limits<double>::epsilon()); 

    val_weight = weighter.get_weight(1, "example");
    val_expected = (log10(3) + 1) * (K + 1);
    val_expected /= K * (1 - B + B * 7/6) + (log10(3) + 1);
    val_expected *= log(2);

    CHECK(fabs(val_weight - val_expected) <= std::numeric_limits<double>::epsilon()); 
    
    fs::remove_all(temp);
}

//Fix this entire test case
TEST_CASE("Test 2 - weights from a query"){
    utils::create_temp_corpus(temp, documents);

    DocumentsData data(temp.c_str());
    Bm25 weighter(idx_docs, data);

    std::string query = "a sample or example sample";

    // recipe vector -> alphabetic ordered 
    std::vector<double> expected_weights = {
        log(2) * (K + 1) / (K + 1),
        0.0,
        log(2) * (K + 1) / (K + 1),
        0.0,
        log(2) * (K + 1) * (1 + log10(2)) /(K + (1 + log10(2))),
        0.0
    };
    auto weights_query = weighter.get_query_weights(query); 

    CHECK(
        std::equal(weights_query.begin(), weights_query.end(), expected_weights.begin(),
            [](double wq_val, double ew_val)
            {
                return fabs(wq_val - ew_val) <= std::numeric_limits<double>::epsilon();
            }
        )
    );

    fs::remove_all(temp);
}