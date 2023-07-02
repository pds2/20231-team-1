#ifndef VECTOR_SPACE_HPP
#define VECTOR_SPACE_HPP

#include <Eigen/Core>

#include "ranking.hpp"
#include "document.hpp"

//! \brief Classe que implementa o modelo vetorial de ranqueamento de relevância.
/*!
  Esse modelo representa os documentos e a busca como vetores em um espaço vetorial dos termos, utilizando do ângulo entre eles como um indicador de relevância/similaridade. Para mais detalhes, consulte a wiki do projeto no Github.
*/
class VectorSpaceRanking : public Ranking {
private:
  Eigen::VectorXd get_query_vec(Weighting & weighter, std::string query) const;
public:
  //! Constroe uma instância do modelo vetorial de ranqueamento para um dado conjunto de documentos
  VectorSpaceRanking(DocumentsData & data, DocumentIndex & index) : Ranking(data, index) {}
  std::vector<int> rank(Weighting & weighter, std::string query) const override;
};

#endif
