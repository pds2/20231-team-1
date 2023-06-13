#ifndef LSARANKING_HPP
#define LSARANKING_HPP

#include <Eigen/Core>

#include "ranking.hpp"

class LsaRanking : public Ranking {
private:
  void get_rr_term_document_mat(Weighting & weighter, Eigen::MatrixXd & T, Eigen::VectorXd & s, Eigen::MatrixXd & D) const;
  Eigen::VectorXd get_query_vec(Weighting & weighter, std::string query) const;
public:
  LsaRanking(DocumentIndex & index) : Ranking(index) {}
  std::vector<int> rank(Weighting & weighter, std::string query) const override;
};

#endif
