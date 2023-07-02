#include <cstdio>
#include "../lib/document.hpp"
#include "../lib/inverted_list.hpp"
using namespace std;

bool inverted_list::write_to_disk() {
	if (filename_.size() == 0) {
		fprintf(stderr, "%s\n", "Empty file name while writing inverted list!"); // adicionar exceção
		return false;
	}
	FILE *f = fopen(filename_.c_str(), "wb");
	if (f == NULL) return false;
	for (size_t i = 0; i < size(); ++i) {
		posting_meta block = {(int)i, (int)(*this)[i].size()}; // modificar --> muito casting
		if (
			fwrite(&block, sizeof block, 1, f) != 1 ||
			fwrite(&(*this)[i][0], sizeof(index_unit), block.length, f) != (size_t)block.length
		) {
			perror("An error occurred while writing inverted list!");
			return false;
		}
	}
	fclose(f);
	return true;
}

bool inverted_list::load_from_disk() {
	if (filename_.size() == 0) {
		fprintf(stderr, "%s\n", "Empty file name while reading inverted list!");
		return false;
	}
	FILE *f = fopen(filename_.c_str(), "rb");
	if (f == NULL) return false;
	posting_meta block;
	this->clear();
	while (fread(&block, sizeof block, 1, f) == 1) {
		resize(size() + 1);
		this->back().resize(block.length);
		if (fread(&this->back()[0], sizeof(index_unit), block.length, f) != (size_t)block.length) {
			perror("An error occurred while reading inverted list!");
			return false;
		}
	}
	fclose(f);
	return true;
}

void inverted_list::set_file_name(const string& filename) {
    filename_ = filename;
}

void inverted_list::new_posting_list() {
    resize(size() + 1);
}