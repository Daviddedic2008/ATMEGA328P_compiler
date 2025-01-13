#include "microcontroller_consts.h"
#include "branching.h"
#include "flash_alloc.h"
#include "asm_commands.h"

#define abs_i(i) (i * (i < 0 * -1))


// generates header for if statement involving 2 vars being compared
void if_vars(general_allocation v1, general_allocation v2, int comparison_type, const char* tag_after) {

	// offset for smallest var
	const int diff = v1.alloc.size - v2.alloc.size;
	const int sz_smallest = (v1.alloc.size > v2.alloc.size) ? v1.alloc.size : v2.alloc.size;

	ldi(Z_LO, ((char)(v1.alloc.startLocation+v1.alloc.size)));
	int tmp = v1.alloc.startLocation + v1.alloc.size;
	ldi(Z_HI, ((char*)&(tmp))[1]);

	ldi(X_LO, ((char)(v2.alloc.startLocation + v2.alloc.size)));
	tmp = v2.alloc.startLocation + v2.alloc.size;
	ldi(X_HI, ((char*)&(tmp))[1]);

	if (comparison_type == LESS) {
		// check greater sized var
		int o = 0;
		for(; o < diff; o++, sbiw(Z_LO, 1)) {
			ld(16, Z);
			cpi(16, 0);
			brge(tag_after);
		}
		for (int o2 = 0; o2 < sz_smallest; o2++, sbiw(Z_LO, 1), sbiw(X_LO, 1)) {
			ld(16, Z);
			ld(17, X);
			cp(16, 17);
			brge(tag_after);
		}
	}

	if (comparison_type == GREATER) {
		// check greater sized var
		int o = 0;
		for (; o < -diff; o++, sbiw(X_LO, 1)) {
			ld(16, X);
			cpi(16, 0);
			brge(tag_after);
		}
		for (int o2 = 0; o2 < sz_smallest; o2++, sbiw(Z_LO, 1), sbiw(X_LO, 1)) {
			ld(16, Z);
			ld(17, X);
			cp(16, 17);
			brlt(tag_after);
		}
	}
	if (comparison_type == EQUAL) {
		// check greater sized var
		int o = 0;
		for (; o < -diff; o++, sbiw(X_LO, 1)) {
			ld(16, X);
			cpi(16, 0);
			brne(tag_after);
		}
		for (int o2 = 0; o2 < sz_smallest; o2++, sbiw(Z_LO, 1), sbiw(X_LO, 1)) {
			ld(16, Z);
			ld(17, X);
			cp(16, 17);
			brne(tag_after);
		}
	}
}