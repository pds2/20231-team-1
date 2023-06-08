#ifndef QUERY_RESOLVER_HPP
#define QUERY_RESOLVER_HPP

#include <string>

#include "document.hpp"

class QueryResolver {
  std::vector<int> * resolve(DocumentIndex index, std::string query);
};

#endif 
