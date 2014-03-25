atomic primitives
=================

Examples of atomic primitives and their cross platform implementations

# Usage

Test by running 'make && ./cas'

### Primitives

#### CAS

The `compare_and_swap(*ptr, oldvalue, newvalue)` implements the CAS atomic primitive. This uses `__sync_bool_compare_and_swap` gcc builtin if available, falling back to inline assembly if not, and uses `InterlockCompareExchange` if on Windows.

#### FAA

The `fetch_and_add(*ptr, value)` implements the FAA atomic primitive. This uses `__sync_fetch_and_add` gcc builtin if available, falling back to inline x86 assembly if not, and uses `InterlockedExchangeAdd` on Windows (NOTE: I've just realised this might be the wrong method to use, will need to check when I get back onto a Windows machine).

### Current Status

Tested on OS X (Intel \_\_amd64\_\_)

Tested on Windows 7 with MSVC 2k13 _WIN32

Tested on Ubuntu 13.10 (Kernel 3.11.0-12-generic) (Intel x86_64)
