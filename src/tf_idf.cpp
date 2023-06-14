#include <cmath>
#include <sstream>

#include "../lib/tf_idf.hpp"

TfIdf::TfIdf(DocumentIndex& index) : Weighting(index){

// df - Document Frequence
    for(auto term: index)
        idf_vals[term.first] = term.second.size();

// Turn df vals to idf - Inverse document frequence

    for(auto& term : idf_vals)
        term.second = log10(index.size()/term.second);

// Recipe vector

    for(auto term: idf_vals) this->recipe_vector.push_back(term.first);
}

double TfIdf::get_weight(int doc_idx, std::string term){
    // Maybe a exception of doc_idx no exists
    
    double tf = (double) Documents::get_frequence(term, doc_idx);
    tf = 1 + log10(tf);

    return tf * idf_vals[term];
}

std::vector<double> TfIdf::get_query_weights(std::string query){

    // Splitting the query and add its words to a map
    std::istringstream iss(query);
    std::map<std::string, int> words;

    while(iss){
        std::string substr;
        iss >> substr;
        words[substr] += 1;
    }

    
    // Following the recipe vector for mount the result vector 
    std::vector<double> res;
    for(auto term: recipe_vector){

        if(words.count(term) == 0) res.push_back(0);
        else {
            double tf = 1 + log10(words[term]);
            double weight = idf_vals[term] * tf; 
            res.push_back(weight);
        }
    }

    return res;
}

