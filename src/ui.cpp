#include "../lib/ui.hpp"
#include "document.hpp"

#include <filesystem>
#include <ftxui/dom/elements.hpp>
#include <ftxui/dom/table.hpp>
#include <ftxui/screen/screen.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>

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

// Um ftxui::component que serve como um wrapper responsivo de ftxui::Table
class TableComponent : public ftxui::ComponentBase {
 public:
  TableComponent(std::vector<std::vector<std::string>>* data) : data_(data) {}

  // Renderiza a ftxui::Table com o estado atual de data_
  ftxui::Element Render() override {
    using namespace ftxui;
    Table table(*data_);
    table.SelectAll().Separator();
    return table.Render();
  }

  // Esse componente não se responsabiliza por tratar nenhum evento
  bool OnEvent(ftxui::Event event) override {
    return false;
  }

 private:
  std::vector<std::vector<std::string>> * data_;
};

void render_ui(DocumentsData & data, Ranking & ranker) {
  using namespace ftxui;

  std::string query;
  std::vector<std::vector<std::string>> results;

  auto input_option = InputOption();
  input_option.on_enter = [&] {
    std::vector<int> ranking = ranker.rank(query);
    results.clear();
    for (const int& doc_idx : ranking) {
      results.push_back({std::to_string(doc_idx), data.get_doc_name(doc_idx)});
    }
  };

  auto query_input = Input(&query, "query", input_option);
  auto results_table = Make<TableComponent>(&results);

  auto doc = Container::Vertical({
      query_input,
      results_table,
    });

  auto renderer = Renderer(doc, [&] {
    return vbox({
        hbox(results_table->Render()) | border,
        hbox(text("Digite sua query: "), query_input->Render()) | border | flex,
      });
  });

  auto screen = ScreenInteractive::TerminalOutput();
  screen.Loop(renderer);
}
