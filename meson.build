project('indexer', 'cpp',
        default_options: ['cpp_std=gnu++17'])

eigendep = dependency('eigen3')
testdep = dependency('doctest')

incdir = include_directories('lib')

add_global_arguments('-std=c++17', language: 'cpp')

src = [
    'src/bm25.cpp',
    'src/document.cpp',
    'src/lsa.cpp',
    'src/main.cpp',
    'src/tf_idf.cpp',
    'src/vector_space.cpp',
    'src/weightning.cpp',
]

executable(
    'idx',
#    sources: src,
    'src/main.cpp',
#    'src/inverted_list.cpp',
    dependencies: [eigendep],
)

vs_test = executable(
    'test_vs',
    'test/vector_space.cpp',
    'src/vector_space.cpp',
    include_directories : incdir,
    dependencies: [eigendep, testdep],
)

test('test vector space ranking', vs_test)

lsa_test = executable(
    'test_lsa',
    'test/lsa.cpp',
    'src/lsa.cpp',
    include_directories : incdir,
    dependencies: [eigendep, testdep],
)

test('test lsa ranking', lsa_test)

tfidf_test = executable(
    'test_tfidf',
    'test/tfidf.cpp',
    'src/tf_idf.cpp',
    include_directories : incdir,
    dependencies: [testdep],
)

test('test tfidf weighting', tfidf_test)

bm25_test = executable(
    'test_bm25',
    'test/bm25.cpp',
    'src/bm25.cpp',
    include_directories : incdir,
    dependencies: [testdep],
)

test('test bm25 weighting', bm25_test)
