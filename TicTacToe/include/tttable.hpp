#ifndef TTTABLE_H_
#define TTTABLE_H_

#include "table.hpp"

class TTTable : public Table {
public:
	void print_table();
	void reset();
	char over(); 
	bool won(std::vector<char> line);
};

#endif  // TTTABLE_H_
