typedef unsigned int uint;

static inline uint MIN2(uint x, uint y) {
	if (x < y) return x;
	return y;
}

static inline uint MIN3(uint x, uint y, uint z) {
	uint min_yz = MIN2(y, z);
	uint min = MIN2(x, min_yz);
	return min;
}

uint edit_distance(char* t1, uint t1_len, char* t2, uint t2_len) {
	/* To use the least amount of memory, we make sure that t2 is the shortest one */
	if (t2_len > t1_len) {
		char* _t = t1;
		t1 = t2;
		t2 = _t;

		uint _tl = t1_len;
		t1_len = t2_len;
		t2_len = _tl;
	}

	/* To avoid having to copy data from the current row to the previous
	 * row, we keep 2 rows with the variable 'row' pointing to the current one */
	uint rows[2][t2_len + 1];
	uint row = 0;

	// Initialise table
	rows[0][0] = 0;
	for (uint j = 1; j <= t2_len; j++) {
		rows[0][j] = j;
	}

	for (uint i = 1; i <= t1_len; i++) {
		row = !row;
		rows[row][0] = i;

		for (uint j = 1; j <= t2_len; j++) {
			char switch_cost = 1;
			if (t1[i-1] == t2[j-1]) switch_cost = 0;

			rows[row][j] = MIN3(
				rows[!row][j-1] + switch_cost,
				rows[!row][j] + 1,
				rows[row][j-1] + 1
			);
		}
	}

	return rows[row][t2_len];
}

#ifndef LIBRARY
#include <stdio.h>
#include <string.h>
int main(int argc, char** argv) {
	if (argc != 3) {
		fprintf(stderr, "You need to pass exactly 2 arguments\n");
		return 1;
	}

	char* t1 = argv[1];
	unsigned long t1_len = strlen(t1);
	char* t2 = argv[2];
	unsigned long t2_len = strlen(t2);

	uint e_d = edit_distance(t1, t1_len, t2, t2_len);

	printf("Edit distance: %u\n", e_d);

	return 0;
}
#endif /* !LIBRARY */
