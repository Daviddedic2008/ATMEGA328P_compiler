#include "variable_ops.h"
#include "flash_alloc.h"
#include "asm_commands.h"
#include "string"
#include <iostream>

void set_variable_value(const char* name, const char* value, int num_bytes) {
	memory_allocation m;
	std::list<memory_allocation>::iterator it = allocations.begin();
	int o = 0;
	for (; o < allocations.size(); o++, std::advance(it, 1)) {
		if (it->name.compare(name) == 0) {
			break;
		}
		if (o == allocations.size() - 1) {
			o++;
		}
	}
	if (o == allocations.size()) {
		std::cerr << "undefined variable access" << std::endl;
		return;
	}
	int tmp = it->startLocation;
	ldi(Z_LO, (char)tmp);
	ldi(Z_HI, ((char*)&tmp)[1]);
	push(16);
	for (int b = 0; b < it->size; b++, adiw(Z_LO, 1)) {
		int tmpsz = it->startLocation + b;
		char lo = (char)(tmpsz);
		char hi = ((char*)(&tmpsz))[1];
		ldi(16, value[b]);
		sts(Z, 16);
	}
	pop(16);
}

void set_variable_variable(const char* name, const char* name2) {
	memory_allocation m;
	std::list<memory_allocation>::iterator it = allocations.end();
	std::list<memory_allocation>::iterator it2 = allocations.end();
	bool found1, found2;
	found1 = false; found2 = false;
	int o = 0;

	for (std::list<memory_allocation>::iterator i = allocations.begin(); o < allocations.size(); o++, std::advance(i, 1)) {
		if (it->name.compare(name) == 0) {
			it = i;
			found1 = true;
		}

		if (it->name.compare(name2) == 0) {
			it2 = i;
			found2 = true;
		}

		if (o == allocations.size() - 1) {
			o++;
		}
	}
	if (!found1 || !found2) {
		std::cerr << "undefined variable access" << std::endl;
		return;
	}
	int tmp = it->startLocation;
	ldi(Z_LO, (char)tmp);
	ldi(Z_HI, ((char*)&tmp)[1]);

	int tmp2 = it2->startLocation;
	ldi(X_LO, (char)tmp2);
	ldi(X_HI, ((char*)&tmp2)[1]);

	if (regsInUse[16]) {
		push(16);
	}
	for (int b = 0; b < (it->size < it2->size) ? it->size : it2->size; b++, adiw(Z_LO, 1), adiw(Z_LO, 1)) {
		int tmpsz = it->startLocation + b;
		char lo = (char)(tmpsz);
		char hi = ((char*)(&tmpsz))[1];
		ld(16, X);
		sts(Z, 16);
	}
	if (regsInUse[16]) {
		pop(16);
	}
}

void add_const_to_var(const char* name, const char* val, int num_bytes) {
	memory_allocation m;
	std::list<memory_allocation>::iterator it = allocations.begin();
	int o = 0;
	for (; o < allocations.size(); o++, std::advance(it, o)) {
		if (it->name.compare(name) == 0) {
			break;
		}
		if (o == allocations.size() - 1) {
			o++;
		}
	}
	if (o == allocations.size()) {
		std::cerr << "undefined variable access" << std::endl;
		return;
	}
	it->move_to_regs();
	if (regsInUse[16]) {
		push(16);
	}
	ldi(16, val[0]);
	add(it->register_location, 16);
	for (int r = it->register_location+1; r < it->register_location + it->size; r++) {
		if (r - it->register_location < num_bytes) {
			ldi(16, val[r - it->register_location]);
			adc(r, 16);
		}
	}
	if (regsInUse[16]) {
		pop(16);
	}
	it->move_back_to_flash();
}

void add_var_to_var(const char* name, const char* name2) {
	memory_allocation m;
	std::list<memory_allocation>::iterator it = allocations.end();
	std::list<memory_allocation>::iterator it2 = allocations.end();
	bool found1, found2;
	found1 = false; found2 = false;
	int o = 0;

	for (std::list<memory_allocation>::iterator i = allocations.begin(); o < allocations.size(); o++, std::advance(i, 1)) {
		if (it->name.compare(name) == 0) {
			it = i;
			found1 = true;
		}

		if (it->name.compare(name2) == 0) {
			it2 = i;
			found2 = true;
		}

		if (o == allocations.size() - 1) {
			o++;
		}
	}
	if (!found1 || !found2) {
		std::cerr << "undefined variable access" << std::endl;
		return;
	}
	it->move_to_regs();
	it2->move_to_regs();
	add(it->register_location, it2->register_location);
	for (int o = 1; o < it->size; o++) {
		if (o < it2->size) {
			adc(it->register_location + o, it2->register_location + o);
		}
	}
	it->move_back_to_flash();
	it2->move_back_to_flash();
}

void add_const_to_var_regs(const char* name, const char* val, int num_bytes) { // dont move back to flash
	memory_allocation m;
	std::list<memory_allocation>::iterator it = allocations.begin();
	int o = 0;
	for (; o < allocations.size(); o++, std::advance(it, o)) {
		if (it->name.compare(name) == 0) {
			break;
		}
		if (o == allocations.size() - 1) {
			o++;
		}
	}
	if (o == allocations.size()) {
		std::cerr << "undefined variable access" << std::endl;
		return;
	}
	it->move_to_regs();
	if (regsInUse[16]) {
		push(16);
	}
	ldi(16, val[0]);
	add(it->register_location, 16);
	for (int r = it->register_location + 1; r < it->register_location + it->size; r++) {
		if (r - it->register_location < num_bytes) {
			ldi(16, val[r - it->register_location]);
			adc(r, 16);
		}
	}
	if (regsInUse[16]) {
		pop(16);
	}
}

void add_var_to_var_regs(const char* name, const char* name2) { // dont move back to flash
	memory_allocation m;
	std::list<memory_allocation>::iterator it = allocations.end();
	std::list<memory_allocation>::iterator it2 = allocations.end();
	bool found1, found2;
	found1 = false; found2 = false;
	int o = 0;

	for (std::list<memory_allocation>::iterator i = allocations.begin(); o < allocations.size(); o++, std::advance(i, 1)) {
		if (it->name.compare(name) == 0) {
			it = i;
			found1 = true;
		}

		if (it->name.compare(name2) == 0) {
			it2 = i;
			found2 = true;
		}

		if (o == allocations.size() - 1) {
			o++;
		}
	}
	if (!found1 || !found2) {
		std::cerr << "undefined variable access" << std::endl;
		return;
	}
	it->move_to_regs();
	it2->move_to_regs();
	add(it->register_location, it2->register_location);
	for (int o = 1; o < it->size; o++) {
		if (o < it2->size) {
			adc(it->register_location + o, it2->register_location + o);
		}
	}
	it2->move_back_to_flash();
}

void mul_var_const(const char* name, char* val, int num_bytes) {
	memory_allocation m;
	std::list<memory_allocation>::iterator it = allocations.begin();
	int o = 0;
	for (; o < allocations.size(); o++, std::advance(it, 1)) {
		if (it->name.compare(name) == 0) {
			break;
		}
		if (o == allocations.size() - 1) {
			o++;
		}
	}
	if (o == allocations.size()) {
		std::cerr << "undefined variable access" << std::endl;
		return;
	}

	if (regsInUse[16]) {
		push(16);
	}
	if (regsInUse[17]) {
		push(17);
	}
	if (regsInUse[18]) {
		push(18);
	}
	if (regsInUse[19]) {
		push(19);
	}
	if (regsInUse[20]) {
		push(20);
	}

	it->move_to_regs();

	ldi(16, val[0]);
	mul(it->register_location, 16);
	mov(16, 0);
	mov(17, 1);

	for (int b = 1; b < (it->size < num_bytes ? it->size : num_bytes); b++) {
		ldi(20, val[b]);
		mul(it->register_location + b, 20);
		if (16 + b <= 19) {
			add(16 + b, 0);
		}
		if (16 + b < 19) {
			adc(16 + b + 1, 1);
		}
	}

	it->move_back_to_flash();

	if (regsInUse[16]) {
		pop(16);
	}
	if (regsInUse[17]) {
		pop(17);
	}
	if (regsInUse[18]) {
		pop(18);
	}
	if (regsInUse[19]) {
		pop(19);
	}
	if (regsInUse[20]) {
		pop(20);
	}
}

void mul_var_var(const char* name1, const char* name2, int num_bytes) {
	memory_allocation m;
	std::list<memory_allocation>::iterator it = allocations.begin();
	std::list<memory_allocation>::iterator it2 = allocations.begin();
	int o = 0;
	for (; o < allocations.size(); o++, std::advance(it, 1), std::advance(it2, 1)) {
		if (it->name.compare(name1) == 0) {
			break;
		}
		if (o == allocations.size() - 1) {
			o++;
		}
	}
	if (o == allocations.size()) {
		std::cerr << "undefined variable access" << std::endl;
		return;
	}

	if (regsInUse[16]) {
		push(16);
	}
	if (regsInUse[17]) {
		push(17);
	}
	if (regsInUse[18]) {
		push(18);
	}
	if (regsInUse[19]) {
		push(19);
	}
	if (regsInUse[20]) {
		push(20);
	}

	it->move_to_regs();
	

	ld(16, it->startLocation);
	mul(it->register_location, 16);
	mov(16, 0);
	mov(17, 1);

	for (int b = 1; b < (it->size < num_bytes ? it->size : num_bytes); b++) {
		ld(20, it->startLocation+b);
		mul(it->register_location + b, 20);
		if (16 + b <= 19) {
			add(16 + b, 0);
		}
		if (16 + b < 19) {
			adc(16 + b + 1, 1);
		}
	}
	it->move_back_to_flash();

	if (regsInUse[16]) {
		pop(16);
	}
	if (regsInUse[17]) {
		pop(17);
	}
	if (regsInUse[18]) {
		pop(18);
	}
	if (regsInUse[19]) {
		pop(19);
	}
	if (regsInUse[20]) {
		pop(20);
	}
}