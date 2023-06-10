#include <cmath>

#include "../lib/tf_idf.hpp"

TfIdf::TfIdf(DocumentIndex& index) : Weighting(index){

    // Each document I assume is a map of term to its quantity (Inverted list).
    // And the document index is a list of these documents

// df - Document Frequence
    std::unordered_map<std::string, double> idf_vals;
    for(auto document: index){
        for(auto term: document.terms){
            idf_vals[term.first] += 1;
        }
    }

// Turn df vals to idf - Inverse document frequence

    for(auto& term : idf_vals)
        term.second = log10(index.size()/term.second);
    
// Mount the matrix tf-idf

    this->weights.resize(index.size());
    for(int i = 0; i < index.size(); i++){ // For each document
        for(auto term : index[i].terms){
            weights[i][term.first] = term.second * idf_vals[term.first];
        }
    }
}

std::vector<double> TfIdf::get_weight(std::string term){

    std::vector<double> weights_per_doc;
    for(auto doc : weights) weights_per_doc.push_back(doc[term]);
    return weights_per_doc;
    
}

std::vector<int> TfIdf::get_query_weights(std::string query){



}

