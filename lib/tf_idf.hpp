#ifndef TF_IDF_HPP
#define TF_IDF_HPP

#include <map>
#include <set>
#include <vector>
#include "weighting.hpp"

/**
 * @brief Classe que implementa modelo de ponderamento por TF-IDF.
 *
 *        Seu funcionamento se baseia em calcular o número de aparições 
 *        de um termo num documento e relacionar com sua relevância no 
 *        conjunto de documentos observado. Consulte a wiki do projeto para mais detalhes.
 */
class TfIdf : public Weighting {

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
    TfIdf(DocumentIndex& index, DocumentsData &data);

    double get_weight(int doc_idx, std::string term) override;

    std::vector<double> get_query_weights(std::string query) override;
};

#endif
