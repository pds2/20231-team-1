#include <cmath>
#include <sstream>

#include "../lib/document.hpp"
#include "../lib/tf_idf.hpp"

TfIdf::TfIdf(DocumentIndex& index, DocumentsData &data) : Weighting(index), data(data){

    // df - Frequencia do Documento
    for(auto term: index)
        idf_vals[term.first] = term.second.size();

    // Transforma os valores df em idf - Frequencia Inversa do Documento
    for(auto& term : idf_vals)  
        term.second = log10(data.get_qt_docs()/term.second);
	
    // Monta o recipe vector
    for(auto term: idf_vals) this->recipe_vector.push_back(term.first);
}

double TfIdf::get_weight(int doc_idx, std::string term){

    // Calcula o valor tf
    double tf = (double) data.get_frequence(term, doc_idx);
    if(tf != 0) tf = 1 + log10(tf);

    return tf * idf_vals[term];
}

std::vector<double> TfIdf::get_query_weights(std::string query){
    // Dividindo a consulta e adicionando suas palavras a um map
    std::istringstream iss(query);
    std::map<std::string, int> words;

    while(iss){
        std::string substr;
        iss >> substr;
        words[substr] += 1;
    }
    
    // Seguindo o recipe vector para montar o vetor de resultado.
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

