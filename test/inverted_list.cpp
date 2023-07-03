#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include <iostream>
#include <exception>

#include "../lib/document.hpp"
#include "../lib/inverted_list.hpp"

TEST_CASE("inverted_list without name") {
    InvertedList test_list = InvertedList();
    try {
        bool writed = test_list.write_to_disk();
    } catch (no_file_name_e &e) {
        std::cout << "can't write to disk without a file name." << std::endl;
    }
    try {
        bool loaded = test_list.load_to_disk();
    } catch (no_file_name_e &e) {
        std::cout << "can't load file without a file name." << std::endl;
    }
}

TEST_CASE("inverted list with a file that does not exist") {
    InvertedList test_list = InvertedList("not_exist");
    try {
        bool writed = test_list.write_to_disk();
    } catch (file_not_found_e &e) {
        std::cout << "that file does not exist." << std::endl;
    }
    try {
        bool loaded = test_list.load_to_disk();
    } catch (file_not_found_e &e) {
        std::cout << "that file does not exist." << std::endl;
    }
}