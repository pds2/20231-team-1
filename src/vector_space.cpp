#include "../lib/document.hpp"
#include "../lib/vector_space.hpp"

Eigen::SparseVector<double> VectorSpaceRanking::get_query_vec(Weighting & weighter, std::string query) const {
  Eigen::SparseVector<double> query_vec(index.size());

  std::vector<double> query_weights = weighter.get_query_weights(query);

  for (int i = 0; i < query_weights.size(); i++) {
    query_vec.coeffRef(i) = query_weights[i];
  }

  return query_vec;
}

VectorSpaceRanking::VectorSpaceRanking(DocumentsData & data, DocumentIndex & index, Weighting & weighter): Ranking(data, index, weighter) {
  const int N_TERMS = index.size();
  const int N_DOCS = data.get_qt_docs();

  document_vectors.assign(N_DOCS, Eigen::SparseVector<double>(N_TERMS));

  // Preenche os vetores dos documentos com seus pesos de cada termo
  int term_idx = 0;
  for (auto [term, docs] : index) {
    for (auto doc : docs) {
      document_vectors[doc].coeffRef(term_idx) = weighter.get_weight(doc, term);
    }
    term_idx++;
  }

}

std::vector<std::pair<double, int>> VectorSpaceRanking::rank(std::string query) const {
  const unsigned int N_DOCS = data.get_qt_docs();

  const Eigen::SparseVector<double> query_vec = get_query_vec(weighter, query);

  // Calcula a relevância de cada documento através do cosseno do ângulo entre eles
  std::vector<std::pair<double, int>> ranking;
  for (unsigned int i = 0 ; i < N_DOCS; i++) {
    // cos(a, b) = (a . b) / (||a|| * ||b||)
    const Eigen::SparseVector<double> & d = document_vectors[i];
    const double cos = query_vec.dot(d) / (query_vec.norm() * d.norm());
    ranking.push_back({cos, i});
  }

  // Ordenamos os documentos da maior à menor relevância
  sort(ranking.begin(), ranking.end(), std::greater<std::pair<double, int>>());

  return ranking;
}
