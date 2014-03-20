#include "atomic.h"
#include "stdio.h"
#if _WIN32
#include "Windows.h"
#elif __ENVIRONMENT_MAC_OS_X_VERSION_MIN_REQUIRED__ >= 1050
#include <libkern/OSAtomic.h>
#endif

int x86_cas(unsigned long *thevalue, unsigned long oldvalue, unsigned long newvalue) {
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

int compare_and_swap_int(int *thevalue, int oldvalue, int newvalue) {
#ifdef _WIN32
	return InterlockedCompareExchange(thevalue, newvalue, oldvalue)
#elif __ENVIRONMENT_MAC_OS_X_VERSION_MIN_REQUIRED__ >= 1050
	return OSAtomicCompareAndSwapIntBarrier(oldvalue, newvalue, thevalue);
#elif (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__) > 40100
	return __sync_bool_compare_and_swap(thevalue, oldvalue, newvalue);
#endif
}

int compare_and_swap_ptr(void *volatile *thevalue, void *oldvalue, void *newvalue) {
#ifdef _WIN32
	return InterlockedCompareExchange(thevalue, newvalue, oldvalue)
#elif __ENVIRONMENT_MAC_OS_X_VERSION_MIN_REQUIRED__ >= 1050
	return OSAtomicCompareAndSwapPtrBarrier(oldvalue, newvalue, thevalue);
#elif (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__) > 40100
	return __sync_bool_compare_and_swap(thevalue, oldvalue, newvalue);
#endif
}
