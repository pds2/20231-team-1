#ifndef RANKING_HPP
#define RANKING_HPP

#include "document.hpp"
#include "weighting.hpp"

//! @brief Classe abstrata que serve de interface para diferentes modelos de ranqueamento de relevância
class Ranking {
protected:
  //! Dados gerais sobre o corpus a ser ranqueado
  DocumentsData & data;
  //! A lista invertida do corpus
  DocumentIndex & index;
  //! O modelo de ponderamento utilizado
  Weighting & weighter;
public:

  virtual ~Ranking(){}
  /**
   * @brief Constroe uma instância do modelo de ranqueamento para um dado conjunto de documentos
   * @param data Dados gerais sobre o corpus a ser ranqueado
   * @param index A lista invertida do corpus
   * @param weighter o modelo de ponderamento a ser utilizado
   */
  Ranking(DocumentsData & data, DocumentIndex & index, Weighting & weighter) : data(data), index(index), weighter(weighter) {}
  /**
   * @brief Ranquea os documentos de acordo com a relevância para a query
   * @param query a busca do usuário
   */
  virtual std::vector<int> rank(std::string query) const = 0;
};

#endif
