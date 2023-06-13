#ifndef WEIGHTING_HPP
#define WEIGHTING_HPP

#include <cmath>
#include <sstream>
#include <string>
#include <unordered_map>
#include <set>

#include "document.hpp"

class Weighting {

protected:
  DocumentIndex& index;

  // All tf-idf weights for each term of each document.
  std::vector<std::unordered_map<std::string, double>> weights;
  std::set<std::string> recipe_vector;
  
public:

  Weighting(DocumentIndex& index): index(index){};
  virtual double get_weight(int doc_idx, std::string term) = 0;
  virtual std::vector<int> get_query_weights(std::string query) = 0;

};

#endif
