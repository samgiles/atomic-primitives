#include "atomic.h"
#if _WIN32
#include "Windows.h"
#elif __ENVIRONMENT_MAC_OS_X_VERSION_MIN_REQUIRED__ >= 1050
#include <libkern/OSAtomic.h>
#endif


int compare_and_swap_int(int *thevalue, int oldvalue, int newvalue) {
#ifdef _WIN32
	return InterlockedCompareExchange(thevalue, newvalue, oldvalue)
#elif __ENVIRONMENT_MAC_OS_X_VERSION_MIN_REQUIRED__ >= 1050
	return OSAtomicCompareAndSwapIntBarrier(oldvalue, newvalue, thevalue);
#elif (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__) > 40100
	return __sync_bool_compare_and_swap(thevalue, oldvalue, newvalue);
#endif
}
