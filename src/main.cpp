#include "../lib/ui.hpp"
#include "document.hpp"

#include "weighting.hpp"
#include "bm25.hpp"
#include "tf_idf.hpp"

#include "lsa.hpp"
#include "vector_space.hpp"

#include <memory>

#include <CLI/CLI.hpp>

int main(int argc, char* argv[]) {

  CLI::App app{"Files Indexer"};

  // Option directory
  std::string directory = "";  
  app.add_option("--directory, -d", directory, "Set the directory in which the ranker will work. Required flag.")->required();

  std::string weighter_name = "TFIDF"; // The default weighter is the tfidf
  app.add_option("--weighter, -w", weighter_name, "Set the weighter, can be //TODO Optional flag");

  bool lsi_wanted = false;

  app.add_flag("--lsi, --lsa", lsi_wanted, "Use lsi ranker instead vector-space ranker (Default ranker).");

  CLI11_PARSE(app, argc, argv);

  // Setting the path
  DocumentsData data = handle_path_argument(directory); // Maybe a exception here??
  

  // Setting the weighter
  std::shared_ptr<Weighting> weighter;
  if(weighter_name == "TFIDF") weighter = std::make_shared<TfIdf>(data.get_document_index(), data);
  else weighter = std::make_shared<Bm25>(data.get_document_index(), data);

  //Setting the ranker
  std::unique_ptr<Ranking> ranker;
  if(lsi_wanted) ranker = std::make_unique<LsaRanking>(data, data.get_document_index(), *weighter);
  else ranker = std::make_unique<VectorSpaceRanking>(data, data.get_document_index(), *weighter);

  render_ui(data, *ranker);

  //// TODO: permitir que o usuário troque essas escolhas

  return 0;
}
