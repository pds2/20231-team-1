#ifndef DOCUMENT_HPP
#define DOCUMENT_HPP

#include <map>
#include <string>
#include <unordered_map>
#include <vector>

/**
 * @brief Exceção usada quando o diretório passado não é encontrado
 * 
 */
class DirNotFoundException : public std::exception {
public:
  /**
   * @brief Função que mostra o que aconteceu para essa exceção ser lançada.
   * 
   * @return const char* Explicação.
   */
  virtual const char* what() const noexcept{
    return "Diretorio nao encontrado";
  }

};

using DocumentIndex = std::map<std::string, std::vector<int>>;

//! @brief Classe abstrata que organiza os documentos implementando uma lista invertida
class DocumentsData{
private:
    struct DocMetadata {
        int word_count;
        std::string name;
    };
    
    DocumentIndex word_to_doc_index;

    std::unordered_map<std::string, std::unordered_map<int, int>> word_index;
    std::unordered_map<int, DocMetadata> doc_metadatas;
    /**
     * @brief Converte o indice de palavras para o indice de arquivos 
     * 
     * @param wordIndex Indice de palavras
     * @return DocumentIndex Indice de arquivos
     */
    DocumentIndex convertToDocumentIndex(const std::unordered_map<std::string, std::unordered_map<int, int>>& wordIndex); // private

public:
    /**
     * @brief Constroe as dependencias das funcoes, bem como o indice e os dados.
     * 
     * @param dir_name Nome do diretorio desejado para utilizacao.
     */
    DocumentsData(const char *dir_name);
    /**
     * @brief Calcula o indice dos arquivos presentes no diretorio utilizado.
     * 
     * @return DocumentIndex& Indice de arquivos a partir das palavras.
     */
    DocumentIndex& get_document_index();
    /**
     * @brief Calcula o numero de palavras presentes no arquivo desejado.
     * 
     * @param doc_idx Indice do arquivo requerido.
     * @return int Numero de palavras presentes.
     */
    int get_size(int doc_idx);
    /**
     * @brief Calcula o numero medio de palavras presentes em todos os arquivos do diretorio
     * 
     * @return double Numero medio de palavras do diretorio
     */
    double get_avg_size();
    /**
     * @brief Retorna a quantidade de documentos presentes no diretorio analisado
     * 
     * @return int Quantidade de documentos do diretorio
     */
    int get_qt_docs();
    /**
     * @brief Calcula a frequencia de um termo no arquivo requerido
     * 
     * @param term Termo utilizado para a analise da frequencia
     * @param doc_idx Indice do arquivo a ser analisado
     * @return int Frequencia do termo no arquivo
     */
    int get_frequence(std::string term, int doc_idx);
    /**
     * @brief Retorna o nome do documento a partir de seu indice
     * 
     * @param doc_idx Indice do arquivo requerido
     * @return std::string Nome do arquivo
     */
    std::string get_doc_name(int doc_idx); 
};

#endif
