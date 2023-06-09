#ifndef VECTOR_SPACE_HPP
#define VECTOR_SPACE_HPP

#include <armadillo>

#include "ranking.hpp"
#include "document.hpp"

class VectorSpaceRanking : public Ranking {
private:
  arma::vec get_query_vec(Weighting & weighter, std::string query) const;
public:
  std::vector<int> * rank(Weighting & weighter, std::string query) const override;
};

#endif
