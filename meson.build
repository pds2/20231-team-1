project('indexer', 'cpp',
        default_options: ['cpp_std=gnu++17'])

add_global_arguments('-std=c++17', language: 'cpp')

eigendep = dependency('eigen3')

system_tui = dependency('ftxui', required: false, modules: ['ftxui::screen', 'ftxui::dom', 'ftxui::component'])

if system_tui.found()
  tuidep = system_tui
else
  # Use Wrap ftxui
  ftxui_proj = subproject('ftxui')
  tuidep = [
    ftxui_proj.get_variable('screen_dep'),
    ftxui_proj.get_variable('dom_dep'),
    ftxui_proj.get_variable('component_dep')
  ]
endif


testdep = dependency('doctest')

clidep = dependency('CLI11')

incdir = include_directories('lib')

src = [
    'src/bm25.cpp',
    'src/document.cpp',
    'src/lsa.cpp',
    'src/main.cpp',
    'src/tf_idf.cpp',
    'src/ui.cpp',
    'src/vector_space.cpp',
]

executable(
    'idx',
    sources: src,
    include_directories: incdir,
    dependencies: [eigendep, tuidep, clidep],
    link_args: ['-no-pie'],
)

vs_test = executable(
    'test_vs',
    'test/vector_space.cpp',
    'src/vector_space.cpp',
    'src/document.cpp',
    include_directories : incdir,
    dependencies: [eigendep, testdep],
)

test('test vector space ranking', vs_test)

lsa_test = executable(
    'test_lsa',
    'test/lsa.cpp',
    'src/lsa.cpp',
    'src/document.cpp',
    include_directories : incdir,
    dependencies: [eigendep, testdep],
)

test('test lsa ranking', lsa_test)

tfidf_test = executable(
    'test_tfidf',
    'test/tfidf.cpp',
    'src/tf_idf.cpp',
    'src/document.cpp',
    include_directories : incdir,
    dependencies: [testdep],
)

test('test tfidf weighting', tfidf_test)

bm25_test = executable(
    'test_bm25',
    'test/bm25.cpp',
    'src/bm25.cpp',
    'src/document.cpp',
    include_directories : incdir,
    dependencies: [testdep],
)

test('test bm25 weighting', bm25_test)

inverted_list_test = executable(
  'test_il',
  'test/inverted_list.cpp',
  'src/document.cpp',
  include_directories: incdir,
  dependencies: [testdep],
)

test('test inverted list', inverted_list_test)
