#ifndef TF_IDF_HPP
#define TF_IDF_HPP

#include <set>
#include <unordered_map>
#include <vector>
#include "weighting.hpp"

class TfIdf : public Weighting {

private:
    std::unordered_map<std::string, double> idf_vals;
    DocumentsData& data;

public:

    // The constructor will mount the weight matrix
    TfIdf(DocumentIndex& index, DocumentsData &data);

    // Get weights from the matrix for a specific term
    double get_weight(int doc_idx, std::string term) override;

    // Get weight for the query search
    std::vector<double> get_query_weights(std::string query) override;
};

#endif
