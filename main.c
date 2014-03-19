#include "stdio.h"
#include "stdlib.h"
#include "atomic.h"

void test_compare_and_swap_ptr() {
	char* atomic_counter = malloc(sizeof(char));
	*atomic_counter = 0;

	char* old_value = atomic_counter;

	char* new_value = malloc(sizeof(char));
	*new_value = (*old_value) + 1;

	int cas_result;
	cas_result = compare_and_swap_ptr(((void*)&atomic_counter), old_value, new_value);



	printf("CAS (ptr): %d\n", cas_result);
	printf("atomic_counter: %d\n", *atomic_counter);

	free(new_value);
	free(old_value);
}

void test_compare_and_swap_int() {
	int* atomic_counter = (int*)malloc(sizeof(int));
	*atomic_counter = 0;

	int oldvalue = *atomic_counter;
	int newvalue = oldvalue + 1;

	int cas_result = compare_and_swap_int(atomic_counter, oldvalue, newvalue);

	printf("CAS (int): %d\n", cas_result);
	printf("atomic_counter: %d\n", *atomic_counter);

	free(atomic_counter);
}

int main(int argc, char** argv) {
	test_compare_and_swap_int();
	test_compare_and_swap_ptr();
	return 0;
}



