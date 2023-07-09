#include "../lib/document.hpp"
#include "../lib/lsa.hpp"

#include <Eigen/SVD>
#include <Eigen/SparseCore>

Eigen::VectorXd LsaRanking::get_query_vec(Weighting & weighter, std::string query) const {
  Eigen::VectorXd query_vec = Eigen::VectorXd(index.size());

  std::vector<double> query_weights = weighter.get_query_weights(query);

  for (int i = 0; i < query_weights.size(); i++) {
    query_vec[i] = query_weights[i];
  }

  return query_vec;
}

void LsaRanking::get_rr_term_document_mat(Weighting & weighter) {
  const int N_TERMS = index.size();
  const int N_DOCS = data.get_qt_docs();

  Eigen::SparseMatrix<double> term_doc(N_TERMS, N_DOCS);

  // Preenche a matriz termos-documentos com o valor ij correspondendo
  // ao peso do termo i no documento j
  int term_idx = 0;
  for (auto const& [term, docs] : index) {
    for (auto doc : docs) {
      term_doc.coeffRef(term_idx, doc) = weighter.get_weight(doc, term);
    }

    term_idx++;
  }

  const unsigned int k = std::min({N_TERMS, N_DOCS, 100}); // define a precisão da aproximação

  // Calcula a fatoração svd da matrix termo-documento
  Eigen::BDCSVD<Eigen::MatrixXd> svd(term_doc, Eigen::ComputeThinU | Eigen::ComputeThinV);

  T = svd.matrixU();
  s = svd.singularValues();
  D = svd.matrixV();

  // trunca as respostas em k (Low-rank approximation)
  T.conservativeResize(Eigen::NoChange_t(), k);
  s.conservativeResize(k);
  D.conservativeResize(Eigen::NoChange_t(), k);
}

LsaRanking::LsaRanking(DocumentsData & data, DocumentIndex & index, Weighting & weighter): Ranking(data, index, weighter) {
  get_rr_term_document_mat(weighter);
}

std::vector<int> LsaRanking::rank(std::string query) const {
  const unsigned int N_DOCS = data.get_qt_docs();

  // Computa o vetor da query e o converte para o espaço vetorial reduzido
  Eigen::VectorXd query_vec = get_query_vec(weighter, query);
  Eigen::VectorXd hat_query_vec = T.transpose() * query_vec;

  // Calcula a relevância de cada documento através do cosseno do ângulo entre eles
  std::vector<std::pair<double, int>> ranking;
  for (unsigned int i = 0; i < N_DOCS; i++) {
    const Eigen::VectorXd & d = D.row(i) * s.asDiagonal();
    const double cos = hat_query_vec.dot(d) / (hat_query_vec.norm() * d.norm());
    ranking.push_back({cos, i});
  }

  // Ordenamos os documentos da maior à menor relevância
  sort(ranking.begin(), ranking.end(), std::greater<std::pair<double, int>>());

  // Extraímos a lista de índices de documentos ordenados pela relevância
  std::vector<int> res;
  for (auto &[_, v] : ranking) {
    res.push_back(v);
  }

  return res;
}
