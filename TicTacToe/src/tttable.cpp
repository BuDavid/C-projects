#include "tttable.hpp"

bool TTTable::won(std::vector<char> line) {
	for (int i = 0; i < size-1; i++) {
		if (line[i] != line[i+1] || line[i] == ' ') {
			return false;
		}
	}
	return true;
}
	
char TTTable::over() {
	if (cells < (size * 2) - 2) {
		return 0;
	}

	for (int i = 0; i < size; i++) {
		if (won(get_row(i))) {
			return get_cell(i, 0);
		} 
		if (won(get_col(i))) {
			return get_cell(0, i);
		}
	}
	if (won(get_diag())) {
		return get_cell(1, 1);
	}
	if (won(get_rev_diag())) {
		return get_cell(1, 1);
	}
	if (is_full()) {
		return 'D';
	}
	return 0;
}

void TTTable::print_table() {
	if (!size) {
		std::cout << "The table hasn't been initiated yet" << std::endl;
		return;
	}

	for (int i = 0; i < size; i++) {
		std::cout << "               |     |     " << '\n';
		std::cout << "          ";
		for (int j = 0; j < size; j++) {
			if (j != size-1) {
				std::cout << "  " << table[i][j] << "  |";
			} else {
				std::cout << "  " << table[i][j] << "   ";
			}
		}
		std::cout << std::endl;
		if (i != size-1) {
			std::cout << "          _____|_____|_____\n";
		} else {
			std::cout << "               |     |     \n";
		}
	}
	std::cout << std::endl;
}

void TTTable::reset() {
	table.clear();
	init(size);
	cells = 0;
}
