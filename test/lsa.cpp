#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include "../lib/document.hpp"
#include "../lib/weighting.hpp"
#include "../lib/lsa.hpp"


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

// int DocumentsData::get_qt_docs() {
//   return 2;
// }

TEST_CASE("testing the lsa ranking") {
  DocumentIndex index = {{"casa", {0, 1}}, {"teto", {0}}, {"agora", {1}}};
  BinaryWeighting w(index);
  DocumentsData data;
  LsaRanking l(data, index);

  std::vector<int> r = l.rank(w, "casa nova agora");

  CHECK(r == std::vector<int>{1, 0});
}
