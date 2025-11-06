#include <stdio.h>
#include <string.h>

extern unsigned int edit_distance(
	char* t1, unsigned int t1_len, char* t2, unsigned int t2_len
);

int main(int argc, char** argv) {
	if (argc != 3) {
		fprintf(stderr, "You need to pass exactly 2 arguments\n");
		return 1;
	}

	char* t1 = argv[1];
	unsigned long t1_len = strlen(t1);
	char* t2 = argv[2];
	unsigned long t2_len = strlen(t2);

	unsigned int e_d = edit_distance(t1, t1_len, t2, t2_len);

	printf("Edit distance: %u\n", e_d);

	return 0;
}
