#ifndef TF_IDF_HPP
#define TF_IDF_HPP

#include <set>
#include <unordered_map>
#include <vector>
#include "weighting.hpp"

class TfIdf : public Weighting {
private:

    // All tf-idf weights for each term of each document. 
    std::vector<std::unordered_map<std::string, double>> weights;

    std::set<std::string> recipe_vector;

public:

    // The constructor will mount the weight matrix
    TfIdf(DocumentIndex& index);

    // Get weights from the matrix for a specific term
    std::vector<double> TfIdf::get_weight(std::string term) override;

    // Get weight for the query search
    std::vector<int> TfIdf::get_query_weights(std::string query) override;
};

#endif
