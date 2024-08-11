#include "table.hpp"

Table::Table() {
	size = 0;
	cells = 0;
}

void Table::translate(int& x, int& y) {
	if (translate_table.empty()) {
		init_translate_table();
	}

	y = translate_table[x][1];
	x = translate_table[x][0];
}

void Table::init_translate_table() {
	int k = 1;
	int iter = size*size;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
		translate_table[k++] = {i, j};
		}
	}
}

int Table::get_size() {
	return size;
}

int Table::get_cells() {
	return cells;
}

void Table::clear() {
	table.clear();
	translate_table.clear();
	size = 0;
	cells = 0;
}

std::vector<char> Table::get_row(int x) {
	return table[x];
}

std::vector<char> Table::get_col(int y) {
	std::vector<char> tmp;
	for (int i = 0; i < size; i++) {
		tmp.push_back(table[i][y]);
	}
	return tmp;
}

std::vector<char> Table::get_diag() {
	std::vector<char> tmp;
	for (int i = 0; i < size; i++) {
		tmp.push_back(table[i][i]);
	}
	return tmp;
}

std::vector<char> Table::get_rev_diag() {
	std::vector<char> tmp;
	for (int i = 0; i < size; i++) {
		tmp.push_back(table[i][size-1-i]);
	}
	return tmp;
}

char Table::get_cell(int x, int y) {
	return table[x][y];
}

bool Table::is_full() {
	if (size != 0) {
		return cells == size * size;
	}
	return 0;
}

bool Table::empty() {
	return !cells;
}

int Table::filled_cells() {
	return cells;
}

bool Table::in_range(int x, int y) {
	if (size) {
		return !(x >= size || y >= size || x < 0 || y < 0);
	}
	return 0;
}

bool Table::is_free(int x, int y) {
	return table[x][y] == ' ';
}

void Table::clear_cell(int x, int y) {
	cells--;
	table[x][y] = ' ';
}

void Table::set_cell(char ch, int x, int y) {
	cells++;
	table[x][y] = ch;
}
	
void Table::init(int s) {
	if (s < 1) {
		std::cout << "The table must be bigger";
		return;
	}
	size = s;
	std::vector<char> tmp;
	for (int i = 0; i < size; i++) {
		tmp.push_back(' ');
	}
	for (int i = 0; i < size; i++) {
		table.push_back(tmp);
	}
}

