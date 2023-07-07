#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <filesystem>

#include "../lib/document.hpp"
#include "../lib/weighting.hpp"
#include "../lib/vector_space.hpp"

#include "utils.cpp"

namespace fs = std::filesystem;

class BinaryWeighting : public Weighting {
public:
  BinaryWeighting(DocumentIndex & index) : Weighting(index) {}
  virtual double get_weight(int doc_idx,std::string term) override {
    if (find(index[term].begin(), index[term].end(), doc_idx) != index[term].end()) {
      return 1;
    }
    else return 0;
  }
  virtual std::vector<double> get_query_weights(std::string query) override {
    std::vector<double> weights;
    for (auto const &[term, _] : index) {
      if (query.find(term) != std::string::npos) weights.push_back(1);
      else weights.push_back(0);
    }

    return weights;
  }
};

TEST_CASE("testing the vector space ranking") {
  fs::path tmp = fs::temp_directory_path() / "test_vs";
  std::map<std::string, std::string> corpus{{"0.txt", "casa teto\n"}, {"1.txt", "casa agora\n"}};
  utils::create_temp_corpus(tmp, corpus);

  DocumentIndex index = {{"casa", {0, 1}}, {"teto", {0}}, {"agora", {1}}};
  BinaryWeighting w(index);

  DocumentsData data(tmp.c_str());

  VectorSpaceRanking vs(data, index, w);

  std::vector<int> r = vs.rank("casa nova agora");

  CHECK(r == std::vector<int>{1, 0});

  fs::remove_all(tmp);
}
