#include <stdio.h>
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

uint edit_distance_table(char* t1, uint t1_len, char* t2, uint t2_len) {
	uint table[t1_len + 1][t2_len + 1];

	// Initialise table
	table[0][0] = 0;
	for (uint i = 1; i <= t1_len; i++) {
		table[i][0] = i;
	}
	for (uint j = 1; j <= t2_len; j++) {
		table[0][j] = j;
	}

	for (uint i = 1; i <= t1_len; i++) {
		for (uint j = 1; j <= t2_len; j++) {
			if (t1[i-1] == t2[j-1]) {
				table[i][j] = table[i-1][j-1];
			} else {
				table[i][j] = MIN3(
					table[i-1][j-1] + 1,
					table[i-1][j] + 1,
					table[i][j-1] + 1
				);
			}
		}
	}

	return table[t1_len][t2_len];
}

uint edit_distance_table_with_print(char* t1, uint t1_len, char* t2, uint t2_len) {
	uint table[t1_len + 1][t2_len + 1];

	// Initialise table
	table[0][0] = 0;
	for (uint i = 1; i <= t1_len; i++) {
		table[i][0] = i;
	}
	for (uint j = 1; j <= t2_len; j++) {
		table[0][j] = j;
	}

	// Print out first rows of table
	printf("  |   ");
	for (uint j = 1; j <= t2_len; j++) {
		printf(" %2c", t2[j-1]);
	}
	putchar('\n');
	for (uint j = 0; j < t2_len; j++) {
		printf("---");
	}
	putchar('\n');
	printf("  | ");
	for (uint j = 0; j <= t2_len; j++) {
		printf("%2u ", table[0][j]);
	}
	putchar('\n');

	for (uint i = 1; i <= t1_len; i++) {
		printf("%c | %2u ", t1[i-1], table[i][0]);

		for (uint j = 1; j <= t2_len; j++) {
			char switch_cost = 1;
			if (t1[i-1] == t2[j-1]) switch_cost = 0;

			table[i][j] = MIN3(
				table[i-1][j-1] + switch_cost,
				table[i-1][j] + 1,
				table[i][j-1] + 1
			);
			printf("%2u ", table[i][j]);
		}
		putchar('\n');
	}

	return table[t1_len][t2_len];
}

#ifndef LIBRARY
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

	uint e_d = edit_distance_table_with_print(t1, t1_len, t2, t2_len);

	printf("Edit distance: %u\n", e_d);

	return 0;
}
#endif /* LIBRARY */
