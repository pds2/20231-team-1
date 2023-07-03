#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include <iostream>
#include <exception>

#include "../lib/document.hpp"
#include "../lib/inverted_list.hpp"

TEST_CASE("inverted_list without name") {
    InvertedList lista_test = InvertedList();
    try {
        lista_test.write_to_disk();
    } catch (no_file_name_e &e) {
        std::cout << "can't write to disk without a file name" << std::endl;
    }
}