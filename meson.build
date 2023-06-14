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