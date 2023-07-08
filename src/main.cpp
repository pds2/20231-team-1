#include "../lib/ui.hpp"
#include "document.hpp"
#include "tf_idf.hpp"
#include "vector_space.hpp"
#include "weighting.hpp"
#include <memory>


int main(int argc, char* argv[]) {

  DocumentsData data = handle_path_argument(argc, argv);

  // TODO: permitir que o usuário troque essas escolhas
  std::unique_ptr<Weighting> weighter = std::make_unique<TfIdf>(data.get_document_index(), data);
  std::unique_ptr<Ranking> ranker = std::make_unique<VectorSpaceRanking>(data, data.get_document_index(), *weighter);

  render_ui(data, *ranker);

  return 0;
}
