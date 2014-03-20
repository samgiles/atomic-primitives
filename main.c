#include "stdio.h"
#include "stdlib.h"
#include "atomic.h"



void test_compare_and_swap_long() {
	unsigned long * atomic_counter = (unsigned long*)malloc(sizeof(unsigned long));
	*atomic_counter = 0;

	unsigned long oldvalue = *atomic_counter;
	unsigned long newvalue = oldvalue + 1;

	int cas_result = compare_and_swap(atomic_counter, oldvalue, newvalue);

	printf("CAS (int): %d\n", cas_result);
	printf("atomic_counter: %lu\n", *atomic_counter);

	free(atomic_counter);
}

void test_fetch_and_add() {
	unsigned long * atomic_counter = (unsigned long*)malloc(sizeof(unsigned long));
	*atomic_counter = 0;

	unsigned long faa_result = fetch_and_add(atomic_counter, 13);

	printf("FAA (int): %lu\n", faa_result);
	printf("atomic_counter: %lu\n", *atomic_counter);

	free(atomic_counter);
}

int main(int argc, char** argv) {
	test_compare_and_swap_long();
	test_fetch_and_add();
	return 0;
}



