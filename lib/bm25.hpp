#ifndef BM25_HPP
#define BM25_HPP

#include "weighting.hpp"


#define BM25_K 1.5 // The values are between 1.2 and 2.0. The K constant controls the saturation curve of terms.
#define BM25_B 0.75 // The B constant controls the documents normalization.

/**
 * @brief Classe que implementa modelo de ponderamento por BM25.
 *
 *        Seu funcionamento estende conceitos avaliados pelo algoritmo TF-IDF,
 *        mas considera por exemplo o tamanho dos documentos. 
 *        Consulte a wiki do projeto para mais detalhes.
 */
class Bm25 : public Weighting {

private:
    std::map<std::string, double> idf_vals;
    DocumentsData& data;

public:

    /**
     * @brief Contrói uma instância deste modelo de ponderamento.
     * 
     * @param index Lista invertida dos documentos.
     * @param data Conjunto de dados importantes referente aos documentos observados.
     */
    Bm25(DocumentIndex& index, DocumentsData& data);

    double get_weight(int doc_idx, std::string term) override;
    
    std::vector<double> get_query_weights(std::string query) override;

};

#endif
