#include "stdio.h"
#include "stdlib.h"
#include "atomic.h"



void test_compare_and_swap_long() {
	unsigned long * atomic_counter = (unsigned long*)malloc(sizeof(unsigned long));
	*atomic_counter = 0;

	unsigned long oldvalue = *atomic_counter;
	unsigned long newvalue = oldvalue + 1;

	int cas_result = cas(atomic_counter, oldvalue, newvalue);

	printf("CAS (int): %d\n", cas_result);
	printf("atomic_counter: %lu\n", *atomic_counter);

	free(atomic_counter);
}

int main(int argc, char** argv) {
	test_compare_and_swap_long();
	return 0;
}



