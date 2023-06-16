project('indexer', 'cpp')

eigendep = dependency('eigen3')

incdir = include_directories('lib')

executable(
    'idx',
    'src/main.cpp',
    dependencies: [eigendep])

vs_test = executable(
    'test_vs',
    'test/vector_space.cpp',
    'src/vector_space.cpp',
    include_directories : incdir,
    dependencies: [eigendep])

test('test vector space ranking', vs_test)

lsa_test = executable(
    'test_lsa',
    'test/lsa.cpp',
    'src/lsa.cpp',
    include_directories : incdir,
    dependencies: [eigendep])

test('test lsa ranking', lsa_test)

tfidf_test = executable(
    'test_tfidf',
    'test/tfidf.cpp',
    'src/tf_idf.cpp',
    include_directories : incdir
)

test('test tfidf weighting', tfidf_test)

bm25_test = executable(
    'test_bm25',
    'test/bm25.cpp',
    'src/bm25.cpp',
    include_directories : incdir
)

test('test bm25 weighting', bm25_test)
