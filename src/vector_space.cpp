#include "../lib/vector_space.hpp"

arma::vec VectorSpaceRanking::get_query_vec(Weighting & weighter, std::string query) const{
  arma::vec query_vec = arma::vec(index.size());

  std::vector<double> query_weights = weighter.get_query_weights(query);

  for (int i = 0; i < query_weights.size(); i++) {
    query_vec[i] = query_weights[i];
  }

  return query_vec;
}

std::vector<int> * VectorSpaceRanking::rank(Weighting & weighter, std::string query) const {
  const arma::vec query_vec = get_query_vec(weighter, query);
  
  const int N_DOCS = 100; // FIXME
  const int N_TERMS = index.size();

  std::vector<arma::vec> vectors(N_DOCS, arma::vec(N_TERMS));

  // Preenche os vetores dos documentos com seus pesos de cada termo
  int term_idx = 0;
  for (auto [term, docs] : index) {
    for (int i = 0; i < docs.size(); i++) {
      vectors[i][term_idx] = weighter.get_weight(docs[i], term);
    }
    term_idx++;
  }

  // Calcula a relevância de cada documento através do cosseno do ângulo entre eles
  std::vector<std::pair<double, int>> ranking;
  int doc_idx = 0;
  for (auto &v : vectors) {
    // cos(a, b) = (a . b) / (||a|| * ||b||)
    const double cos = dot(query_vec, v) / (norm(query_vec) * norm(v));
    ranking.push_back({cos, doc_idx});
    doc_idx++;
  }

  // Ordenamos os documentos da maior à menor relevância
  sort(ranking.begin(), ranking.end(), std::greater<std::pair<double, int>>());

  // Extraímos a lista de índices de documentos ordenados pela relevância
  std::vector<int> * res = new std::vector<int>();
  for (auto &[_, v] : ranking) {
    res->push_back(v);
  }

  return res;
}
