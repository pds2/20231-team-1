#include "../lib/ui.hpp"
#include "document.hpp"

#include <filesystem>
#include <ftxui/dom/elements.hpp>
#include <ftxui/dom/table.hpp>
#include <ftxui/screen/screen.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>

DocumentsData handle_path_argument(std::string dir) {
  namespace fs = std::filesystem;

  fs::path path = fs::path(dir);

  if (path.is_relative()) {
    if (!dir.empty() && dir.front() == '~') {
      std::string homeDir = fs::path(std::getenv("HOME"));
      path = homeDir / fs::path(dir.substr(1));
    } else {
      path = fs::current_path() / path;
    }
  }

  return DocumentsData(path.c_str());
}

DocumentsData handle_path_argument(int argc, char **argv) {
  namespace fs = std::filesystem;

  if (argc < 2) {
    throw std::exception();
  }

  std::string arg(argv[1]);
  fs::path path = fs::path(arg);

  if (path.is_relative()) {
    if (!arg.empty() && arg.front() == '~') {
      std::string homeDir = fs::path(std::getenv("HOME"));
      path = homeDir / fs::path(arg.substr(1));
    } else {
      path = fs::current_path() / path;
    }
  }

  return DocumentsData(path.c_str());
}

//! @brief Um ftxui::Component que serve como um wrapper responsivo de ftxui::Table
class TableComponent : public ftxui::ComponentBase {
 public:
  TableComponent(std::vector<std::vector<std::string>>* data) : data_(data) {}

  //! @brief Renderiza a ftxui::Table com o estado atual de data_
  ftxui::Element Render() override {
    using namespace ftxui;
    Table table(*data_);
    table.SelectAll().Separator();
    return table.Render();
  }

  //! @brief Esse componente não se responsabiliza por tratar nenhum evento
  bool OnEvent(ftxui::Event event) override {
    return false;
  }

 private:
  //! Dados a serem visualizados
  std::vector<std::vector<std::string>> * data_;
};

void render_ui(DocumentsData & data, Ranking & ranker) {
  using namespace ftxui;

  std::string query; // A busca do usuário
  std::vector<std::vector<std::string>> results; // Os dados da tabela

  // Callback para atualizar a TableComponent com os novos resultados
  auto input_option = InputOption();
  input_option.on_enter = [&query, &results, &ranker, &data] {
    // Passa a query para minusculas
    std::string lower_query = query;
    std::transform(lower_query.begin(), lower_query.end(), lower_query.begin(), ::tolower);

    results.clear();
    try{
    
      std::vector<std::pair<double, int>> ranking = ranker.rank(lower_query);
      // Atualiza results
      
      unsigned int results_count = 0;
      for (const auto& [score, doc_idx] : ranking) {
        // TODO: permitir que o usuário escolha quantos documentos mais relevantes são mostrados
        if (results_count++ >= 5 || score <= 0.0) break;
        results.push_back({std::to_string(score * 100), data.get_doc_name(doc_idx)});
      }

    }catch(UnrelatedQueryException &e){
      
      results.push_back({"ERRO", e.what()});

    }
    
  };

  auto query_input = Input(&query, "Digite sua busca", input_option);
  auto results_table = Make<TableComponent>(&results);

  auto doc = Container::Vertical({
      query_input,
      results_table,
    });

  doc->OnEvent(Event ev) override {

  }

  auto renderer = Renderer(doc, [&] {
    return vbox({
        hbox(results_table->Render()) | border,
        hbox(text("Busca: "), query_input->Render()) | border | flex,
      });
  });

  auto screen = ScreenInteractive::TerminalOutput();
  screen.Loop(renderer);
}
