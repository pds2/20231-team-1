#ifndef TF_IDF_HPP
#define TF_IDF_HPP

#include <map>
#include <vector>
#include "weighting.hpp"

class TfIdf : public Weighting {
private:

    // All tf-idf weights for each term of each document. 
    std::vector<std::vector<double>> weights;

public:

    // The constructor will mount the weight matrix
    TfIdf(DocumentIndex& index);

    // Get weight from the matrix for a specific term and document
    std::vector<double> TfIdf::get_weight(int doc_idx, std::string term) override;

    // Get weight for the query search
    std::vector<int> TfIdf::get_query_weights(std::string query) override;
};

#endif
