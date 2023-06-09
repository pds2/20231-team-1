#ifndef WEIGHTING_HPP
#define WEIGHTING_HPP

#include <string>
#include <vector>

#include "document.hpp"

class Weighting {
protected:
  DocumentIndex & index;
public:
  Weighting(DocumentIndex & index) : index(index) {}
  virtual double get_weight(int doc_idx, std::string term) = 0;
  virtual std::vector<double> get_query_weights(std::string query) = 0;
};

#endif
