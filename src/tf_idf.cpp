#include <cmath>
#include <sstream>

#include "../lib/document.hpp"
#include "../lib/tf_idf.hpp"

TfIdf::TfIdf(DocumentIndex& index, DocumentsData &data) : Weighting(index), data(data){

    // df - Document Frequence
    for(auto term: index)
        idf_vals[term.first] = term.second.size();

    // Turn df vals to idf - Inverse document frequence
    for(auto& term : idf_vals)  
        term.second = log10(data.get_qt_docs()/term.second);
	
    // Mount the recipe vector
    for(auto term: idf_vals) this->recipe_vector.push_back(term.first);
}

double TfIdf::get_weight(int doc_idx, std::string term){
    // Calculate the tf value
    double tf = (double) data.get_frequence(term, doc_idx);
    if(tf != 0) tf = 1 + log10(tf);

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
    bool is_related = false; 

    for(auto term: recipe_vector){
        if(words.count(term) == 0) res.push_back(0);
        else {
            double tf = 1 + log10(words[term]);
            double weight = idf_vals[term] * tf; 
            res.push_back(weight);
            is_related = true;
        }
    }
    if(!is_related) throw UnrelatedQueryException();

    return res;
}

