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

void edit_distance_table_with_print(char* t1, uint t1_len, char* t2, uint t2_len) {
	if (t1_len > t2_len) {
		char* temp = t1;
		uint temp_len = t1_len;
		t1 = t2;
		t1_len = t2_len;
		t2 = temp;
		t2_len = temp_len;
	}

	uint table[t1_len + 1][t2_len + 1];

	// Initialise table
	table[0][0] = 0;
	for (uint i = 1; i <= t1_len; i++) {
		table[i][0] = i;
	}
	for (uint j = 1; j <= t2_len; j++) {
		table[0][j] = 0;
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
		if (i < t1_len) printf("%c | %2u ", t1[i-1], table[i][0]);

		for (uint j = 1; j <= t2_len; j++) {
			char switch_cost = 1;
			if (t1[i-1] == t2[j-1]) switch_cost = 0;

			table[i][j] = MIN3(
				table[i-1][j-1] + switch_cost,
				table[i-1][j] + 1,
				table[i][j-1] + 1
			);
			if (i < t1_len) printf("%2u ", table[i][j]);
		}
		if (i < t1_len) putchar('\n');
	}

	// NOTE: undefined behaviour in C, but will work for most compilers
	uint smallest = (uint) -1;
	for (uint j = 0; j <= t2_len; j++) {
		if (table[t1_len][j] < smallest) smallest = table[t1_len][j];
	}

	printf("%c | %2u ", t1[t1_len - 1], table[t1_len][0]);
	for (uint j = 1; j <= t2_len; j++) {
		if (table[t1_len][j] == smallest) {
			printf("\x1b[1;4m%2u\x1b[0m ", table[t1_len][j]);
		} else {
			printf("%2u ", table[t1_len][j]);
		}
	}
	putchar('\n');
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

	edit_distance_table_with_print(t1, t1_len, t2, t2_len);

	return 0;
}
#endif /* LIBRARY */
