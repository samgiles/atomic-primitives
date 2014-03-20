// If available use __sync_bool_compare_and_swap
#if (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__) > 40100
	#define cas __sync_bool_compare_and_swap

// If __sync_bool_compare_and_swap is not available but architecture is x86,
// use inline asm with cmpxchgq or cmpxchgl
#elif defined(__amd64__) || defined(__i386__)

static inline int cas(unsigned long *thevalue, unsigned long oldvalue, unsigned long newvalue) {
	unsigned long prev;
	asm volatile("lock;"
#if defined(__amd64__)
			"cmpxchgq %1, %2;"
#else
			"cmpxchgl %1, %2;"
#endif
			: "=a"(prev)
			: "q"(newvalue), "m"(*thevalue), "a"(oldvalue)
			: "memory");
	return prev == oldvalue;
}
#else
# error "define cmpxchg (compare and swap) for your architecture - (cas)"
#endif
