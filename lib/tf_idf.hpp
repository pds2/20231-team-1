#ifndef TF_IDF_HPP
#define TF_IDF_HPP

#include <set>
#include <unordered_map>
#include <vector>
#include "weighting.hpp"

class TfIdf : public Weighting {

public:

    // The constructor will mount the weight matrix
    TfIdf(DocumentIndex& index);

    // Get weights from the matrix for a specific term
    double TfIdf::get_weight(int doc_idx, std::string term) override;

    // Get weight for the query search
    std::vector<int> TfIdf::get_query_weights(std::string query) override;
};

#endif
