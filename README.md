# Indexador de Arquivos - Trabalho Prático Grupo 1

## User Stories

1. Como um usuário, gostaria de fazer uma busca em meus documentos.
2. Como um usuário, gostaria de escolher o modelo de ranqueamento.
3. Como um usuário, gostaria de escolher o modelo de ponderamento.
4. Como um usuário, gostaria de escolher o número de resultados.

## Desenvolvimento

### Dependências

O projeto tem as seguintes dependências de desenvolvimento:
- meson
- pkg-config
- cmake
- eigen 3
- FTXUI
- CLI11
- doctest

Para instalar todos as dependências em um ambiente Ubuntu LTS, basta rodar o comando:

``` shell
sudo apt install -y meson pkg-config cmake libeigen3-dev doctest-dev libcli11-dev
```

**OBS:** a biblioteca [FTXUI](https://github.com/ArthurSonzogni/FTXUI) não está disponivel nos repositórios do Ubuntu. Por isso, o projeto contém um [Meson Wrap](https://mesonbuild.com/Wrap-dependency-system-manual.html) dela. Caso a biblioteca esteja instalada no sistema, essa instalação será usada, caso contrário o wrap é usado automaticamente durante a compilação.

### Compilação

Após clonar o projeto, rode o seguinte comando na pasta raiz:

``` shell
meson setup build
```

Após a confirmação de que todas as dependências estão instaladas no sistema, basta rodar o comando abaixo para compilar (e recompilar):

``` shell
meson compile -C build
```

Para rodar os testes unitários, basta rodar o comando abaixo:

``` shell
meson test -C build
```
### WIKI

Para detalhes sobre os algoritmos usados no projeto consulte nossa wiki.

