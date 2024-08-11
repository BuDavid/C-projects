#ifndef ENTITY_H_
#define ENTITY_H_

#include <iostream>
#include <string>
#include <limits>
#include "tttable.hpp"

class Entity {
public:
	Entity();
	void reset();
	void clean();
	void first_move();
	void last();
	bool is_first();
	int get_wins();
	int get_loses();
	int get_draws();
	char get_symbol();
	std::string get_name();
	void win();
	void lose();
	void draw();
	void set_name(const std::string& new_name);
	void set_symbol();
	virtual bool move(TTTable& table) = 0;
protected:
	std::string name;
	int draws;
	int loses;
	int wins;
	char symbol;
	char symbol_op;
	bool first;
};

class Player : public Entity {
public:
	Player();
	bool move(TTTable& table) override;
};

class Bot : public Entity {
public:
	Bot();
	bool move(TTTable& table) override;
private:
	int minimax(TTTable& table, int depth, bool ismax, int alpha, int beta);
	int evaluate(TTTable& table);
};

#endif  // ENTITY_H_
