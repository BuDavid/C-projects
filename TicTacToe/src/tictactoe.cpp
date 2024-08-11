#include "tictactoe.hpp"

TicTacToe::TicTacToe() {
	TTTable table;
}

Entity* TicTacToe::choose_player(int num) {
	std::string player = "";
	while (true) {
		std::cout << "     Choose Player " <<  num << "\n    0: Bot     1: You" << std::endl;
		std::cin >> player;
		if (player == "0") {
			return new Bot();;
		}
		if (player == "1") {
			return new Player();;
		}
	}
}

void TicTacToe::print_winner(char ch) {
	if (ch == 'D') {
		std::cout << "             It's a draw\n";
	} else if (ch == 'X') {
		std::cout << "                X Won\n";
	} else if (ch == 'O') {
		std::cout << "                O Won\n";
	}
	table.print_table();
}

void TicTacToe::start() {
	table.init(3);
	std::cout << "TicTacToe" << std::endl;
	Entity* p1 = choose_player(1);
	Entity* p2 = choose_player(2);
	p1->first_move();
	p2->last();
	char winner = 0;
	while (true) {
		while (true) {
			table.print_table();
			if (p1->is_first()) {
				while (!p1->move(table));
			} else {
				while (!p2->move(table));
			}

			if (winner = table.over()) {
				print_winner(winner);
				set_stats(winner, p1, p2);	
				break;
			}

			table.print_table();
			if (p2->is_first()) {
				while (!p1->move(table));
			} else {
				while (!p2->move(table));
			}

			if (winner = table.over()) {
				print_winner(winner);
				set_stats(winner, p1, p2);	
				break;
			}
		}
		if (!play_again()) {
			break;
		}
		table.reset();
	}
	print_stats(p1, p2);
	delete p1;
	delete p2;
}

void TicTacToe::print_stats(Entity* p1, Entity* p2) {
	std::cout << "\nPlayer 1:\n" << "   Wins: " << p1->get_wins() << "\n   Loses: " << p1->get_loses() << "\n   Draws: " << p1->get_draws() << std::endl;
	std::cout << "\nPlayer 2:\n" << "   Wins: " << p2->get_wins() << "\n   Loses: " << p2->get_loses() << "\n   Draws: " << p2->get_draws() << std::endl;
}

void TicTacToe::set_stats(char winner, Entity* p1, Entity* p2) {
	if (winner == 'D') {
		p1->draw();
		p2->draw();
		return;
	}
	if (p1->get_symbol() == winner) {
		p1->win();
		p1->first_move();
		p2->lose();
		p2->last();
		return;
	}

	p2->win();
	p2->first_move();
	p1->lose();
	p2->last();
}

bool TicTacToe::play_again() {
	std::string answer = "";
	while (true) {
		std::cout << "Want to play agan? y/n" << std::endl;
		std::cin >> answer;
		if (answer == "y" || answer == "Y") {
			return true;
		}
		if (answer == "n" || answer == "N") {
			return false;
		}
	}
	return false;
}

void TicTacToe::clear() {
	table.clear();
}

