#ifndef TICTACTOE_H_
#define TICTACTOE_H_

#include "tttable.hpp"
#include "entity.hpp"

class TicTacToe {
public:
	TicTacToe(); 
public:
	void start(); 
	void clear();
private:
	Entity* choose_player(int num);
	void print_winner(char ch);
	void print_stats(Entity* p1, Entity* p2);
	void set_stats(char winner, Entity* p1, Entity* p2);
	bool play_again();
private:
	TTTable table;
};

#endif  // TICTACTOE_H_
