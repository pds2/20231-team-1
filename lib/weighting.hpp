#ifndef WEIGHTING_HPP
#define WEIGHTING_HPP

#include <string>

#include "document.hpp"

class Weighting {
public:
  virtual double get_weight(Document & doc, std::string term) = 0;
};

#endif
