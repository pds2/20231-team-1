#ifndef WEIGHTING_HPP
#define WEIGHTING_HPP

#include <cmath>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

#include "document.hpp"

class UnrelatedQueryException : public std::exception {
public:
  virtual const char* what() const noexcept{
    return "Essa busca nao esta relaciona a nenhum documento";
  }
};

/**
 * @brief Classe abstrata usada como interface de um modelo de ponderamento.
 */
class Weighting {

protected:
  DocumentIndex& index;
  std::vector<std::string> recipe_vector;
  
public:

  virtual ~Weighting(){}

  /**
   * @brief Contrói uma instância de um poderador.
   * 
   * @param index Referência ao índice de documentos
   */
  Weighting(DocumentIndex & index) : index(index) {}

  /**
   * @brief Calcula o peso de um dado termo em um específico documento.
   * 
   * @param doc_idx Índice do documento
   * @param term O termo do qual será calculado seu peso
   * @return double Peso do termo dado
   */
  virtual double get_weight(int doc_idx, std::string term) = 0;

  /**
   * @brief Calcula o respectivo vetor de pesos de uma pesquisa.
   * 
   * @param query Pesquisa requerida. Um conjunto de termos.
   * @return std::vector<double> Respectivo vetor de pesos.
   */
  virtual std::vector<double> get_query_weights(std::string query) = 0;
};

#endif
