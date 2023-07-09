#include "../lib/ui.hpp"
#include "../lib/bm25.hpp"
#include "../lib/tf_idf.hpp"
#include "../lib/vector_space.hpp"
#include "../lib/lsa.hpp"
#include <memory>


int main(int argc, char* argv[]) {

  DocumentsData data = handle_path_argument(argc, argv);

  // TODO: permitir que o usuário troque essas escolhas
  std::shared_ptr<Weighting> weighter = std::make_shared<Bm25>(data.get_document_index(), data);
  std::shared_ptr<Ranking> ranker = std::make_shared<VectorSpaceRanking>(data, data.get_document_index(), *weighter);

  render_ui(data, *ranker);

  return 0;
}
