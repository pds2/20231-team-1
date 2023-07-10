#ifndef VECTOR_SPACE_HPP
#define VECTOR_SPACE_HPP

#include <Eigen/Core>
#include <Eigen/SparseCore>

#include "ranking.hpp"
#include "document.hpp"

//! @brief Classe que implementa o modelo vetorial de ranqueamento de relevância.
/*!
  Esse modelo representa os documentos e a busca como vetores em um espaço vetorial dos termos, utilizando do ângulo entre eles como um indicador de relevância/similaridade. Para mais detalhes, consulte a wiki do projeto no Github.
*/
class VectorSpaceRanking : public Ranking {
private:
  std::vector<Eigen::SparseVector<double>> document_vectors;
  Eigen::SparseVector<double> get_query_vec(Weighting & weighter, std::string query) const;
public:
  /**
   * @brief Constroe uma instância do modelo vetorial de ranqueamento para um dado conjunto de documentos
   *
   * Ao construir a instância desse modelo, os documentos do corpus são pré-processados para as buscas.
   */
  VectorSpaceRanking(DocumentsData & data, DocumentIndex & index, Weighting & weighter);
  std::vector<std::pair<double, int>> rank(std::string query) const override;
};

#endif
