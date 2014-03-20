int compare_and_swap_int(int *thevalue, int oldvalue, int newvalue);
int compare_and_swap_ptr(void *volatile *thevalue, void *oldvalue, void *newvalue);
int x86_cas(unsigned long *thevalue, unsigned long oldvalue, unsigned long newvalue);
