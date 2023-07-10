#ifndef TEST_UTILS
#define TEST_UTILS

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <map>
#include <string>
#include <vector>

namespace fs = std::filesystem;

namespace utils {

  /**
   * @brief Cria um corpus temporário
   * @param tmp O caminho para a pasta temporária para o corpus
   * @param documents std::map<std::string, std::string> Define os documentos do corpus, a chave é o nome do arquivo e o valor o conteúdo
   *
   * Essa função cria a árvore de documentos espeficicada em @p documents no caminho @p tmp, que é criado caso não exista. É responsabilidade do código que chama essa função deletar a pasta após o uso.
   */
  void create_temp_corpus(fs::path tmp, std::map<std::string, std::string> documents) {

    if (!fs::exists(tmp)) fs::create_directory(tmp);

    for (auto const& [name, content] : documents) {
      fs::path doc = tmp / name ;
      std::ofstream{doc} << content;
    }
  }

  /**
   * @brief Extrai os indices de documentos do vetor retornado por `Ranking.rank`
   */
  std::vector<int> extract_doc_idxs(std::vector<std::pair<double, int>> ranking) {
    std::vector<int> doc_idxs(ranking.size());

    std::transform(ranking.begin(),
                   ranking.end(),
                   doc_idxs.begin(),
                   [](const std::pair<double, int> r) {return r.second;});

    return doc_idxs;
  }
}
#endif
