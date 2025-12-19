typedef unsigned int uint;
typedef char bool;
#define FALSE 0;
#define TRUE 1;

static inline uint MIN2(uint x, uint y) {
	return x < y ? x : y;
}

static inline uint MIN3(uint x, uint y, uint z) {
	uint min_yz = MIN2(y, z);
	uint min = MIN2(x, min_yz);
	return min;
}

/* #include <stdio.h> */

bool has_max_edit_distance(
	char* t1, uint t1_len, char* t2, uint t2_len, uint max_distance
) {
	uint size_diff = t1_len > t2_len ? t1_len - t2_len : t2_len - t1_len;

	/* We assume that 'max_distance' will be small, so no switching */
	if (size_diff > max_distance) return FALSE;

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
			if (t1[i-1] == t2[j-1]) {
				rows[row][j] = rows[!row][j-1];
			} else {
				rows[row][j] = MIN3(
					rows[!row][j-1] + 1,
					rows[!row][j] + 1,
					rows[row][j-1] + 1
				);
			}
		}
	}

	return rows[row][t2_len] <= max_distance;
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
			if (t1[i-1] == t2[j-1]) {
				rows[row][j] = rows[!row][j-1];
			} else {
				rows[row][j] = MIN3(
					rows[!row][j-1] + 1,
					rows[!row][j] + 1,
					rows[row][j-1] + 1
				);
			}
		}
	}

	return rows[row][t2_len];
}

/* This function assumes that t1 and t2 are shorter then 33 chars */
/* TODO: benchmark, and why does this work again? */
uint edit_distance32(char* t1, uint t1_len, char* t2, uint t2_len) {
	uint peq[128] = { 0 };
	if (t1_len < t2_len) {
		char* _t = t1;
		t1 = t2;
		t2 = _t;

		uint _tl = t1_len;
		t1_len = t2_len;
		t2_len = _tl;
	}
	const uint lst = 1 << (t1_len - 1);
	uint pv = -1;
	uint mv = 0;
	uint sc = t1_len;
	uint i = t1_len;

	while (i--) {
		peq[t1[i]] |= 1 << i;
	}

	for (i = 0; i < t2_len; i++) {
		uint eq = peq[t2[i]];
		uint xv = eq | mv;
		eq |= ((eq & pv) + pv) ^ pv;
		mv |= ~(eq | pv);
		pv &= eq;
		if (mv & lst) sc++;
		if (pv & lst) sc--;
		mv = (mv << 1) | 1;
		pv = (pv << 1) | ~(xv | mv);
		mv &= xv;
	}

	return sc;
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

	uint e_d1 = edit_distance(t1, t1_len, t2, t2_len);
	uint e_d2 = edit_distance32(t1, t1_len, t2, t2_len);

	printf("Edit distance:    %u\n", e_d1);
	printf("Edit distance_32: %u\n", e_d2);

	return 0;
}
#endif /* !LIBRARY */
