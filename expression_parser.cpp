#include "variable_ops.h"
#include "asm_commands.h"
#include "microcontroller_consts.h"
#include "flash_alloc.h"
#include "expression_parser.h"
#include <string>
#include <list>

// decode an expression into a linear series of instructions

struct instruction {
	char op; // '+' or '-', etc.
	const char* varName; // name of variable being added
	int val; // val being added
	memory_allocation location; // being operated on

	instruction(memory_allocation m, const char* vn, char o) : varName(vn), op(o), val(0), location(m) {}
	instruction(memory_allocation m, int v, char o) : varName(nullptr), op(o), val(v), location(m) {}
};

std::list<instruction> parse_expression(std::string expression) {
	
	size_t cur_index = expression.find(' ');

	std::string varname = expression.substr(0, cur_index);
	expression = expression.substr(cur_index + 1, expression.size() - cur_index-1);

	std::list<instruction> ret;
	return ret;

}