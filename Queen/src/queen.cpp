#include "queen.hpp"

Queen::Queen() {
	queens = 0;
}

void Queen::clear() {
	queens = 0;
	bord.clear();
}

void Queen::start(int size) {
	bord.init(size);
	find_solution(0);
	bord.print();
}

bool Queen::find_solution(int queen) {
	int ans = evaluate(queen);
	if (ans) {
		if (ans == 1) {
			return 1;
		}
		return 0;
	}
	for (int i = 0; i < bord.get_size(); i++) {
		if (!(bord.is_free(queen, i))) {
			continue;
		}
		bord.set_queen(queen, i); 
		queens++;
		if (find_solution(queen+1)) {
			return 1;
		}
		bord.undo(queen, i);
		queens--;
	}
	return 0;
}

int Queen::evaluate(int queen) {
	if (queens == bord.get_size()) {
		return 1;
	}

	std::vector<char> tmp = bord.get_row(queen);
	for (int i = 0; i < bord.get_size(); i++) {
		if (tmp[i] == ' ') {
			return 0;
		}
	}
	return -1;
}
	
