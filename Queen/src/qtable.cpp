#include "qtable.hpp"

void QTable::print() {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			std::cout << table[i][j] << " |";
		}
		std::cout << std::endl;
	}
		std::cout << std::endl;
}

void QTable::set_queen(int x, int y) {
	char ch = '0' + x;
	for (int i = x, j = y; j < size; i++, j++) {
		if ( i == size) {
			break;
		}
		if (get_cell(i,j) == ' ') {
			set_cell(ch, i, j);
		}
	}

	for (int i = x, j = y; i < size; i++, j--) {
		if ( i == size) {
			break;
		}
		if (get_cell(i,j) == ' ') {
			set_cell(ch, i, j);
		}
	}

	for (int i = x; i < size; i++) {
		if (get_cell(i,y) == ' ') {
			set_cell(ch, i, y);
		}
	}

	set_cell('Q', x, y);
}

void QTable::undo(int x, int y) {
	char ch = '0' + x;
	for (int i = x, j = y; j < size; i++, j++) {

		if ( i == size) {
			break;
		}
		if (get_cell(i,j) == ch) {
			set_cell(' ', i, j);
		}
	}

	for (int i = x, j = y; i < size; i++, j--) {

		if ( i == size) {
			break;
		}
		if (get_cell(i,j) == ch) {
			set_cell(' ', i, j);
		}
	}

	for (int i = x; i < size; i++) {
		if (get_cell(i,y) == ch) {
			set_cell(' ', i, y);
		}
	}
	set_cell(' ', x, y);
}
