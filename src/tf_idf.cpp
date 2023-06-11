#include <cmath>
#include <sstream>

#include "../lib/tf_idf.hpp"

TfIdf::TfIdf(DocumentIndex& index) : Weighting(index){

    // Each document I assume is a map of term to its quantity (Inverted list).
    // And the document index is a vector of these documents

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

// Mounting the recipe of vector

    for(auto term : idf_vals) recipe_vector.insert(term.first);

}

std::vector<double> TfIdf::get_weight(std::string term){

    std::vector<double> weights_per_doc;
    for(auto doc : weights) weights_per_doc.push_back(doc[term]);
    return weights_per_doc;
    
}

std::vector<int> TfIdf::get_query_weights(std::string query){

    // Splitting the query and add its words to a map
    std::istringstream iss(query);
    std::map<std::string, int> count_words;

    while(iss){
        std::string substr;
        iss >> substr;
        count_words[substr] += 1;
    }

    // Following the recipe vector for mount the result vector 
    std::vector<int> res;
    auto it = recipe_vector.begin();
    while(it != recipe_vector.end()){

        if(count_words.count(*it) == 0) res.push_back(0);
        else res.push_back(count_words[*it]);

        ++ it;
    }

    return res;
}

