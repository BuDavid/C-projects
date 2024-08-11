#ifndef QUEEN_H_
#define QUEEN_H_

#include "qtable.hpp"

class Queen {
public:
	Queen(); 
	void start(int size = 15);
	bool find_solution(int queen);
	int evaluate(int);
	void clear();
private:
	QTable bord;
	int queens;
};

#endif  // QUEEN_H_
