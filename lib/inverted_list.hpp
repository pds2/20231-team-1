#ifndef _INVERTED_LIST_HPP_
#define _INVERTED_LIST_HPP_

#include <vector>
#include <string>

#include "document.hpp"

using std::vector;
using std::string;

typedef struct {
	int doc, freq, pos_info_offset;
} index_unit;

typedef vector<index_unit> posting_list; // mudar o nome

typedef struct {
	int termid, length;
} posting_meta;

class inverted_list : public vector<posting_list> {
public:
	inverted_list() {}
	inverted_list(const string& filename)  filename_(filename) {}
	void set_file_name(const string& filename) {}
	bool write_to_disk();
	bool load_from_disk();
	void new_posting_list() {}
private:
	string filename_;
};

#endif