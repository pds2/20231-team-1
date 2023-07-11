#include "../lib/bm25.hpp"
#include "../lib/document.hpp"

Bm25::Bm25(DocumentIndex& index, DocumentsData& data) : Weighting(index), data(data){
    
    // df - Frequencia do Documento
    for(auto term: index)
        idf_vals[term.first] = term.second.size();

    // Transforma os valores df em idf - Frequencia Inversa do Documento
    int total_docs = data.get_qt_docs();
    for(auto& term : idf_vals){
        term.second = (total_docs - term.second + 0.5)/(term.second + 0.5);
        term.second = log(term.second + 1);
    }

    // Monta o recipe vector
    for(auto term: idf_vals) this->recipe_vector.push_back(term.first);
}

double Bm25::get_weight(int doc_idx, std::string term){

    // Calcula o valor tf
    double tf = (double) data.get_frequence(term, doc_idx);
    if(tf == 0) return 0.0; 
    
    tf = 1 + log10(tf);

    int size_doc = data.get_size(doc_idx);
    double avg_size = data.get_avg_size();

    // Escore de BM25. Veja o wiki do projeto para obter detalhes.
    double score = (BM25_K + 1) * tf;
    score /= BM25_K * (1 - BM25_B + BM25_B * size_doc/avg_size) + tf;
    score *= idf_vals[term];

    return score;
}

std::vector<double> Bm25::get_query_weights(std::string query){

    // Dividindo a consulta e adicionando suas palavras a um map
    std::istringstream iss(query);
    std::map<std::string, int> words;

    std::string substr;
    while(iss >> substr){
        words[substr] += 1;
    }

    // Seguindo o recipe vector para montar o vetor de resultado.
    std::vector<double> res;
    bool is_related = false;
    for(std::string term: recipe_vector){
        if(words.count(term) == 0) res.push_back(0);
        else {
            double tf = 1 + log10(words[term]);
            double weight = idf_vals[term] * (BM25_K + 1) * tf / (BM25_K + tf); 

            res.push_back(weight);
            is_related = true;
        }
    }

    if(!is_related) throw UnrelatedQueryException();

    return res;
}

