#ifndef WEIGHTING_HPP
#define WEIGHTING_HPP

#include <cmath>
#include <sstream>
#include <string>
#include <unordered_map>
#include <set>
#include <vector>

#include "document.hpp"

class Weighting {

protected:
  DocumentIndex& index;
  std::vector<std::string> recipe_vector;
  
public:
  Weighting(DocumentIndex & index) : index(index) {}
  virtual double get_weight(int doc_idx, std::string term) = 0;
  virtual std::vector<double> get_query_weights(std::string query) = 0;
};

#endif
