#ifndef RANKING_HPP
#define RANKING_HPP

#include "document.hpp"
#include "weighting.hpp"

//! Classe abstrata que serve de interface para diferentes modelos de ranqueamento de relevância
class Ranking {
protected:
  DocumentsData & data;
  DocumentIndex & index;
public:
  //! Constroe uma instância do modelo de ranqueamento para um dado conjunto de documentos
  Ranking(DocumentsData & data, DocumentIndex & index) : data(data), index(index) {}
  //! \brief Ranquea os documentos de acordo com a relevância para a query
  /*!
    \param weightner o modelo de ponderamento a ser utilizado
    \param query a busca do usuário
   */
  virtual std::vector<int> rank(Weighting & weightner, std::string query) const = 0;
};

#endif
