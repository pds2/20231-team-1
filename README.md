# Indexador de Arquivos - Trabalho Prático Grupo 1

## User Stories

1. Como um usuário, gostaria de procurar arquivos em meus documentos pelo nome.
2. Como um usuário, gostaria de fazer buscas por data de criação, data de modificação, tamanho.
3. Como um usuário, gostaria de atualizar a indexação de arquivos de forma periódica.
4. Como um usuário, gostaria que os arquivos fossem automaticamente reindexados caso a indexação seja muito antiga.
5. Como um usuário, gostaria de categorizar ou atribuir atributos aos arquivos para separá-los.
6. Como um usuário, gostaria de selecionar o diretório a ser indexado.
7. Como um usuário, gostaria de filtrar minha busca a um subdiretório.

## Desenvolvimento

### Dependências

O projeto tem as seguintes dependências:
- meson
- pkg-config
- cmake
- eigen 3
- doctest

Para instalar todos as dependências em um ambiente Ubuntu LTS, basta rodar o comando:

``` shell
sudo apt install -y meson pkg-config cmake libeigen3-dev doctest-dev
```

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

