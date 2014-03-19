#include "stdio.h"
#include "stdlib.h"
#include "atomic.h"

int main(int argc, char** argv) {
	int atomic_counter = 0;

	int oldvalue = atomic_counter;

	int newvalue = atomic_counter + 1;

	int cas_result = compare_and_swap_int(&atomic_counter, oldvalue, newvalue);

	printf("CAS: %d\n", cas_result);
	return 0;
}
