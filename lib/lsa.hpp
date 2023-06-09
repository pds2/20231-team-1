#ifndef LSARANKING_HPP
#define LSARANKING_HPP

#include <armadillo>

#include "ranking.hpp"

class LsaRanking : public Ranking {
private:
  void get_rr_term_document_mat(Weighting & weighter, arma::mat & T, arma::vec & s, arma::mat & D) const;
  arma::vec get_query_vec(Weighting & weighter, std::string query) const;
public:
  std::vector<int> * rank(Weighting & weighter, std::string query) const override;
};

#endif
