project('indexer', 'cpp')
armadep = dependency('armadillo')
armaargs = '-larmadillo -llapack -lblas'
executable(
    'idx',
    'src/main.cpp',
    dependencies: [armadep],
    cpp_args: armaargs)