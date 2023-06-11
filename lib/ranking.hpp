#ifndef RANKING_HPP
#define RANKING_HPP

#include "document.hpp"
#include "weighting.hpp"

class Ranking {
protected:
  DocumentIndex & index;
public:
  Ranking(DocumentIndex & index) : index(index) {}
  virtual std::vector<int> rank(Weighting & weightner, std::string query) const = 0;
};

#endif
