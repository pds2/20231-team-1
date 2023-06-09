#include "../lib/lsa.hpp"

arma::vec LsaRanking::get_query_vec(Weighting & weighter, std::string query) const {
  arma::vec query_vec = arma::vec(index.size());

  std::vector<double> query_weights = weighter.get_query_weights(query);

  for (int i = 0; i < query_weights.size(); i++) {
    query_vec[i] = query_weights[i];
  }

  return query_vec;
}

void LsaRanking::get_rr_term_document_mat(Weighting & weighter, arma::mat & T, arma::vec & s, arma::mat & D) const {
  const int N_TERMS = index.size();
  const int N_DOCS = 100; // FIXME

  arma::sp_mat term_doc(N_TERMS, N_DOCS);

  // Preenche a matriz termos-documentos com o valor ij correspondendo
  // ao peso do termo i no documento j
  int term_idx = 0;
  for (auto [term, docs] : index) {
    for (auto doc : docs) {
      term_doc(term_idx, doc) = weighter.get_weight(doc, term);
    }

    term_idx++;
  }

  const unsigned int k = 100; // define a precisão da aproximaçaõ

  // Calcula a aproximação de rank k da matriz termo-documento via SVD
  arma::svds(T, s, D, term_doc, k);
}

std::vector<int> * LsaRanking::rank(Weighting & weighter, std::string query) const {
  const int N_DOCS = 100; // FIXME

  // Computa a matriz termo-documento reduzida 
  arma::mat T, D;
  arma::vec s;
  get_rr_term_document_mat(weighter, T, s, D);

  arma::mat S_i = diagmat(s).i();

  // Computa o vetor da query e o converte para o espaço vetorial reduzido
  arma::vec query_vec = get_query_vec(weighter, query);
  arma::vec hat_query_vec = S_i * T.t() * query_vec;

  // Calcula a relevância de cada documento através do cosseno do ângulo entre eles
  std::vector<std::pair<double, int>> ranking;
  for (int i = 0; i < N_DOCS; i++) {
    const arma::vec & d = D.col(i);
    const double cos = dot(hat_query_vec, d) / (norm(hat_query_vec) * norm(d));
    ranking.push_back({cos, i});
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
