#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include <exception>
#include <iostream>

#include "../lib/document.hpp"

TEST_CASE("Inverted List Test without a valid dir") {
    try {
        DocumentsData docData = DocumentsData("../include/");
    } catch (dir_not_found_e& e) {
        std::cout << "Erro" << std::endl;
    }
}