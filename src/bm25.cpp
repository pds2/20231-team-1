#include "../lib/bm25.hpp"

Bm25::Bm25(DocumentIndex& index, DocumentsData& data) : Weighting(index), data(data){
    
// df - Document Frequence
    for(auto term: index)
        idf_vals[term.first] = term.second.size();


// Turn df vals to idf - Inverse document frequence

    int total_docs = data.get_qt_docs();

    for(auto& term : idf_vals){
        term.second = (total_docs - term.second + 0.5)/(term.second + 0.5);
        term.second = log(term.second + 1);
    }

// Recipe vector

    for(auto term: idf_vals) this->recipe_vector.push_back(term.first);
}

double Bm25::get_weight(int doc_idx, std::string term){
    // Maybe a exception of doc_idx no exists
    
    double tf = (double) data.get_frequence(term, doc_idx);
    if(tf == 0) return 0.0; 
    
    tf = 1 + log10(tf);

    int size_doc = data.get_size(doc_idx);
    double avg_size = data.get_avg_size();

    double score = (K + 1) * tf;
    score /= K * (1 - B + B * size_doc/avg_size) + tf;
    score *= idf_vals[term];

    return score;
}

std::vector<double> Bm25::get_query_weights(std::string query){

    // Splitting the query and add its words to a map
    std::istringstream iss(query);
    std::map<std::string, int> words;

    while(iss){
        std::string substr;
        iss >> substr;
        words[substr] += 1;
    }

    // Following the recipe vector for mount the result vector.
    std::vector<double> res;
    for(std::string term: recipe_vector){
        if(words.count(term) == 0) res.push_back(0);
        else {
            double tf = 1 + log10(words[term]);
            
            //double weight = tf;

            double weight = idf_vals[term] * (K + 1) * tf / (K + tf); 
            res.push_back(weight);
        }
    }
    return res;
}

