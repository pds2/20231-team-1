#ifndef UI_H
#define UI_H

#include "document.hpp"
#include "ranking.hpp"
#include "weighting.hpp"

/**
 * @brief Processa o argumento do caminho do corpus
 */
DocumentsData handle_path_argument(int argc, char * argv[]);

/**
 * @brief Renderiza a interface do usuário
 * @param data DocumentsData Os dados do corpus do usuário
 * @param ranker Ranking O modelo de ranqueamento a ser usado
 */
void render_ui(DocumentsData & data, Ranking & ranker);

#endif /* UI_H */
