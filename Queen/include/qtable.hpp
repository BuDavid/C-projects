#ifndef QTABLE_H_
#define QTABLE_H_

#include "table.hpp"

class QTable : public Table {
public:
	void set_queen(int, int);
	void undo(int, int);
	void print();
};

#endif  // QTABLE_H_
