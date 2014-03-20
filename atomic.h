#ifndef _ATOMIC_H
#define _ATOMIC_H

#if defined(__llvm__) || (defined(__GNUC__) && ( __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 1)))
#define HAS_SYNC_BOOL_COMPARE_AND_SWAP
#define HAS_SYNC_FETCH_AND_ADD
#endif

#ifdef HAS_SYNC_BOOL_COMPARE_AND_SWAP

#define compare_and_swap __sync_bool_compare_and_swap

// If __sync_bool_compare_and_swap is not available but architecture is x86,
// use inline asm with cmpxchgq or cmpxchgl
#elif defined(__amd64__) || defined(__i386__)

static inline int compare_and_swap(unsigned long *thevalue, unsigned long oldvalue, unsigned long newvalue) {
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
#elif defined(_WIN32) || defined(_WIN64)
#include <Windows.h>
static inline unsigned long compare_and_swap(unsigned long *thevalue, unsigned long oldvalue, unsigned long newvalue) {
	unsigned long originalvalue = InterlockedCompareExchange(thevalue, newvalue, oldvalue);
	return originalvalue == oldvalue;
}
#else
#error define cmpxchg (compare and swap) for your architecture - (cas)
#endif

#ifdef HAS_SYNC_FETCH_AND_ADD
#	define fetch_and_add __sync_fetch_and_add
#elif defined(__amd64__) || defined(__i386__)
static inline unsigned long fetch_and_add(unsigned long* ptr, unsigned long value) {
	unsigned long previous;
	// xadd r0, r1   - Exchange r0 and r1 loading sum into r1
	asm volatile ("lock;"
#if defined(__amd64__)
		"xaddq %1, %2;"
#else
		"xaddl %1, %2;"
#endif
		: "=r"(previous)
		: "0"(value), "m"(*ptr)
		: "memory");
	return previous;
}
#elif  defined(_WIN32) || defined(_WIN64)
#include <Windows.h>
#define fetch_and_add InterlockedExchangeAdd
#else
#error define fetch and add for your architecture - (faa)
#endif
#endif
