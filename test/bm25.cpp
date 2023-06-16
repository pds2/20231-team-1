#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include "../lib/document.hpp"
#include "../lib/bm25.hpp"

int DocumentsData::get_frequence(std::string term, int doc_idx){
    std::vector<std::map<std::string, int>> vals = {
        {
            {"this", 1}, {"is", 1}, {"a", 2}, {"sample", 1}
        },
        {
            {"this", 1}, {"is", 1}, {"another", 2}, {"example", 3}
        }
    };
    if(vals[doc_idx].count(term) == 0) return 0;
    return vals[doc_idx][term];
}
int DocumentsData::get_qt_docs(){
    return 2;
}
int DocumentsData::get_size(int doc_idx){
    if(doc_idx == 0) return 5;
    return 7;
}
double DocumentsData::get_avg_size(){
    return 6.0;
}

DocumentIndex idx_docs = {
        {"this", {0, 1}},
        {"is", {0, 1}},
        {"a", {0}},
        {"sample", {0}},
        {"another", {1}},
        {"example", {1}},
};
DocumentsData data;
Bm25 weighter(idx_docs, data);

TEST_CASE("Test 1 - bm25 weighting"){
    double val_weight = weighter.get_weight(0, "example");

    // First weight must be equal 0
    double val_expected = 0.0;
    CHECK(fabs(val_weight - val_expected) <= std::numeric_limits<double>::epsilon()); 

    val_weight = weighter.get_weight(1, "example");
    val_expected = (log10(3) + 1) * (K + 1);
    val_expected /= K * (1 - B + B * 7/6) + (log10(3) + 1);
    val_expected *= log(2);

    CHECK(fabs(val_weight - val_expected) <= std::numeric_limits<double>::epsilon()); 
}

//Fix this entire test case
TEST_CASE("Test 2 - weights from a query"){
    std::string query = "a sample or example sample";

    // recipe vector ->  this, sample, is, example, another, a   
    std::vector<double> expected_weights = {
        0.0,
        log(2) * (K + 1) * (1 + log10(2)) /(K + (1 + log10(2))),
        0.0,
        log(2) * (K + 1) / (K + 1),
        0.0,
        log(2) * (K + 1) / (K + 1),
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
}