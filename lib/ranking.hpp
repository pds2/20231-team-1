#ifndef RANKING_HPP
#define RANKING_HPP

#include "document.hpp"
#include "weighting.hpp"

class Ranking {
protected:
  DocumentsData & data;
  DocumentIndex & index;
public:
  Ranking(DocumentsData & data, DocumentIndex & index) : data(data), index(index) {}
  virtual std::vector<int> rank(Weighting & weightner, std::string query) const = 0;
};

#endif
