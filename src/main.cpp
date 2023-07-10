#include "../lib/ui.hpp"
#include "../lib/document.hpp"

#include "../lib/weighting.hpp"
#include "../lib/bm25.hpp"
#include "../lib/tf_idf.hpp"

#include "../lib/lsa.hpp"
#include "../lib/vector_space.hpp"

#include <memory>

#include <CLI/CLI.hpp>

int main(int argc, char* argv[]) {

  CLI::App app{"Files Indexer"};

  // Option directory
  std::string directory = "";  
  app.add_option("directory", directory, "Set the directory in which the ranker will work. Required value")->required();

  std::string weighter_name = "TFIDF"; // The default weighter is the tfidf
  app.add_option("--weighter, -w", weighter_name, "Set the weighter - TFIDF(Default) or BM25. Optional flag");

  int max_results = 5;
  app.add_option("--maxres, -n", max_results, "Set the max results on table of results (Default=5). Optional flag ");

  bool lsi_wanted = false;

  app.add_flag("--lsi, --lsa", lsi_wanted, "Use lsi ranker instead vector-space ranker (Default ranker)");

  CLI11_PARSE(app, argc, argv);

  // Setting the path
  DocumentsData data = handle_path_argument(directory);
  

  // Setting the weighter
  std::shared_ptr<Weighting> weighter;
  if(weighter_name == "TFIDF") weighter = std::make_shared<TfIdf>(data.get_document_index(), data);
  else weighter = std::make_shared<Bm25>(data.get_document_index(), data);

  //Setting the ranker
  std::unique_ptr<Ranking> ranker;
  if(lsi_wanted) ranker = std::make_unique<LsaRanking>(data, data.get_document_index(), *weighter);
  else ranker = std::make_unique<VectorSpaceRanking>(data, data.get_document_index(), *weighter);

  render_ui(data, *ranker, max_results);

  return 0;
}
