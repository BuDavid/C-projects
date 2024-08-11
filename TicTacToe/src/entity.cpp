#include "entity.hpp"

bool Bot::move(TTTable& table) {
	int best_score = 1 << 31;
	int x = -1;
	int y = -1;

	for (int i = 0; i < table.get_size(); i++) {
		for (int j = 0; j < table.get_size(); j++) {
			if (table.get_cell(i, j) == ' ') {
				table.set_cell(symbol, i, j);

				int score = minimax(table, 0, false, std::numeric_limits<int>::min(), std::numeric_limits<int>::max());

				table.clear_cell(i, j);

				if (score > best_score) {
					best_score = score;
					x = i;
					y = j;
				}
			}
		}
	}
	table.set_cell(symbol, x, y);
	return 1;
}

int Bot::minimax(TTTable& table, int depth, bool ismax, int alpha, int beta) {
	if (table.get_cells() > (table.get_size() * 2)-2) {
		int score = evaluate(table);

		if (score == 10) {
			return score - depth;
		}

		if (score == -10) {
			return score + depth;
		}

		if (table.is_full()) {
			return 0;
		}
	}

	if (ismax) {
		int best = std::numeric_limits<int>::min();

		for (int i = 0; i < table.get_size(); i++) {
			for (int j = 0; j < table.get_size(); j++) {
				if (table.get_cell(i, j) == ' ') {
					table.set_cell(symbol, i, j);

					int tmp = minimax(table, depth+1, !ismax, alpha, beta);

					table.clear_cell(i, j);
					best = std::max(best, tmp);
					alpha = std::max(alpha, tmp);
					if (beta <= alpha) {
						break;
					}
				}
			}
		}
		return best;
	} else {
		int best = std::numeric_limits<int>::max();

		for (int i = 0; i < table.get_size(); i++) {
			for (int j = 0; j < table.get_size(); j++) {
				if (table.get_cell(i, j) == ' ') {
					table.set_cell(symbol_op, i, j);

					int tmp = minimax(table, depth+1, !ismax, alpha, beta);

					table.clear_cell(i, j);
					best = std::min(best, tmp);
					beta = std::min(beta, tmp);

					if (beta <= alpha) {
						break;
					}
				}
			}
		}
		return best;
	}
}

int Bot::evaluate(TTTable& table) {
	char ch = table.over();
	if (ch == symbol) {
		return 10;
	}
	if (ch == symbol_op) {
		return -10;
	}
	return 0;
}

bool Player::move(TTTable& table) {
	std::cout << "Your move:\n";
	int x = 0;
	while (!(std::cin >> x)) {
		std::cout << "Invalid input give a number.\n";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	if (x < 1 || x > 9) {
		std::cout << "Cell is out of reach." << std::endl;
		return 0;
	}
	
	int y = 0;
	table.translate(x, y);

	if (table.is_free(x, y)) {
		table.set_cell(symbol, x, y);
		return 1;
	}
	std::cout << "The cell is occupied." << std::endl;
	return 0;
}

Entity::Entity() {
	name = "";
	wins = 0;
	first = false;
	loses = 0;
	draws = 0;
	symbol = 0;
	symbol_op = 0;
}

Bot::Bot() {
	name = "";
	wins = 0;
	first = false;
	loses = 0;
	draws = 0;
	symbol = 0;
	symbol_op = 0;
}

Player::Player() {
	name = "";
	wins = 0;
	first = false;
	loses = 0;
	draws = 0;
	symbol = 0;
	symbol_op = 0;
}

char Entity::get_symbol() {
	return symbol ? symbol : 0;
}

void Entity::reset() {
	wins = 0;
	loses = 0;
	draws = 0;
}

void Entity::clean() {
	name = "";
	wins = 0;
	first = false;
	loses = 0;
	draws = 0;
	symbol = 0;
	symbol_op = 0;
}

void Entity::first_move() {
	first = true;
	symbol = 'X';
	symbol_op = 'O';
}

void Entity::last() {
	first = false;
	symbol = 'O';
	symbol_op = 'X';
}

bool Entity::is_first() {
	return first;
}

int Entity::get_wins() {
	return wins;
}   

int Entity::get_loses() {
	return loses;
}

int Entity::get_draws() {
	return draws;
}

std::string Entity::get_name() {
	return name;
}

void Entity::win() {
	wins++;
}   

void Entity::lose() {
	loses++;
}

void Entity::draw() {
	draws++;
}

void Entity::set_name(const std::string& new_name) {
	name = new_name;
}

void Entity::set_symbol() {
	if (first) {
		symbol = 'X';
		return;
	}
	symbol = 'O';
}

