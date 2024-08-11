#ifndef TABLE_H_
#define TABLE_H_

#include <iostream>
#include <vector>
#include <map>
#include <array>

class Table {
public:
	Table();
	void clear();
	std::vector<char> get_row(int);
	std::vector<char> get_col(int);
	std::vector<char> get_diag();
	std::vector<char> get_rev_diag();
	char get_cell(int, int);
	void set_cell(char, int, int);
	void translate(int&, int&);
	int get_cells();
	bool is_full(); 
	int get_size();
	bool empty(); 
	int filled_cells();
	bool is_free(int, int);
	void clear_cell(int, int);
	void init(int);
	bool in_range(int, int);
protected:
	void init_translate_table();
protected:
	std::map<int, std::array<int, 2>> translate_table;
	std::vector<std::vector<char>> table;
	int size;
	int cells;
};

#endif  // TABLE_H_
