#ifndef LSARANKING_HPP
#define LSARANKING_HPP

#include <Eigen/Core>

#include "document.hpp"
#include "ranking.hpp"

/**
 * @brief Classe que implementa o modelo de ranqueamento de relevância LSA/LSI.
 *
 * Esse modelo utiliza da fatoração de matrizes SVD para melhorar os resultados do ranqueamento em relação ao modelo vetorial. Para mais detalhes, consulte a wiki do projeto no Github.
 */
class LsaRanking : public Ranking {
private:
  Eigen::MatrixXd T, D;
  Eigen::VectorXd s;
  void get_rr_term_document_mat(Weighting & weighter);
  Eigen::VectorXd get_query_vec(Weighting & weighter, std::string query) const;
public:
  /**
   * @brief Constroe uma instância do modelo LSA de ranqueamento para um dado corpus
   *
   * Ao construir a instância desse modelo, os documentos do corpus são pré-processados para as buscas.
   */
  LsaRanking(DocumentsData & data, DocumentIndex & index, Weighting & weighter);
  /**
   * @brief Ranquea os documentos de acordo com a relevância para a query
   * @param query A busca do usuário
   */
  std::vector<int> rank(std::string query) const override;
};

#endif
