#ifndef VECTOR_SPACE_HPP
#define VECTOR_SPACE_HPP

#include <Eigen/Core>

#include "ranking.hpp"
#include "document.hpp"

class VectorSpaceRanking : public Ranking {
private:
  Eigen::VectorXd get_query_vec(Weighting & weighter, std::string query) const;
public:
  VectorSpaceRanking(DocumentsData & data, DocumentIndex & index) : Ranking(data, index) {}
  std::vector<int> rank(Weighting & weighter, std::string query) const override;
};

#endif
