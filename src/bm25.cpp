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

double Bm25::get_weight(int doc_idx, std::string term){
    return weights[doc_idx][term];
}

std::vector<int> Bm25::get_query_weights(std::string query){

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

