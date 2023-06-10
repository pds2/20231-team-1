#include <cmath>

#include "../lib/bm25.hpp"

Bm25::Bm25(DocumentIndex& index) : Weighting(index){
    
// df - Document Frequence, and count words
    std::unordered_map<std::string, double> idf_vals;
    int total_words = 0;
    for(auto document: index){
        for(auto term: document.terms){
            idf_vals[term.first] += 1;
            total_words += term.second; 
        }
    }

// Turn df vals to idf - Inverse document frequence
// TODO: Change the way how idf is calculated

    for(auto& term : idf_vals)
        term.second = log10(index.size()/term.second);
    
// Mount the matrix 
// TODO: Organize the calc of weight matrix

    double avg_words_doc = total_words/index.size();

    this->weights.resize(index.size());
    for(int i = 0; i < index.size(); i++){ // For each document
        for(auto term : index[i].terms){
            weights[i][term.first] = idf_vals[term.first] * ((term.second * (K + 1))/(term.second + K * (1 - B + B * total_words/avg_words_doc)));
        }
    }
}

std::vector<double> Bm25::get_weight(std::string term){

    std::vector<double> weights_per_doc;
    for(auto doc : weights) weights_per_doc.push_back(doc[term]);
    return weights_per_doc;
    
}

std::vector<int> Bm25::get_query_weights(std::string query){



}

