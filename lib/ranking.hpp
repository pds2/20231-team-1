#ifndef RANKING_HPP
#define RANKING_HPP

#include "document.hpp"
#include "weighting.hpp"

class Ranking {
  virtual std::vector<int> * rank(DocumentIndex index, Weighting weightner, std::string query) = 0;
};

#endif
