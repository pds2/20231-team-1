#ifndef LSARANKING_HPP
#define LSARANKING_HPP

#include <Eigen/Core>

#include "document.hpp"
#include "ranking.hpp"

//! \brief Classe que implementa o modelo de ranqueamento de relevância LSA/LSI.
/*!
  Esse modelo utiliza da fatoração de matrizes SVD para melhorar os resultados do ranqueamento em relação ao modelo vetorial. Para mais detalhes, consulte a wiki do projeto no Github.
 */
class LsaRanking : public Ranking {
private:
  void get_rr_term_document_mat(Weighting & weighter, Eigen::MatrixXd & T, Eigen::VectorXd & s, Eigen::MatrixXd & D) const;
  Eigen::VectorXd get_query_vec(Weighting & weighter, std::string query) const;
public:
  //! Constroe uma instância do modelo LSA/LSI para um dado conjunto de documentos
  LsaRanking(DocumentsData & data, DocumentIndex & index) : Ranking(data, index) {}
  std::vector<int> rank(Weighting & weighter, std::string query) const override;
};

#endif
