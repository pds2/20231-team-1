#ifndef BM25_HPP
#define BM25_HPP

#include "weighting.hpp"

#define K 1.5 // The values are between 1.2 and 2.0. The K constant controls the saturation curve of terms.
#define B 0.75 // The B constant controls the documents normalization.

class Bm25 : public Weighting {

public:

    Bm25(DocumentIndex& index): Weighting(index){}
    double get_weight(int doc_idx, std::string term) override;
    std::vector<int> get_query_weights(std::string query) override;

};

#endif
