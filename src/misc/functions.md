# "Misc" module of resolvec

Implements some useful functions, macros and debug functions. It's more or less complete and tested.

### Include functions using:
```c
#include "src/misc/misc.h"
```

## Macros:
```c
/* prints formatted error message with file and line number */
#define DBG_X(fmt, ...) fprintf(stderr, "[Error] " fmt " in %s:%d\n", __VA_ARGS__, __FILE__, __LINE__)

/* prints error message with file and line number */
#define DBG(err) DBG_X("%s", err)

/* used for not implemented functions */
#define DBG_UNIMPL(function) DBG_X("%s is not implemented", function)
```

## Functions:
bytes sub-module:
```c
/* compare two byte arrays */
BOOL compare_bytes(const PCHAR bytes1, const PCHAR bytes2, const DWORD size);

/* check if string is IPv4 address */
BOOL is_ipv4(PCHAR domain); // It shouldn't be here, but there is no better place for it.

/* replacement of sprintf, i just hate it :< */
PCHAR format_bytes(PCHAR fmt, ...);

/* returns real size of buffer allocated with calloc / memseted to 0 */
DWORD sizeof_buffer(PCHAR buffer, DWORD allocated_size);
```
debug sub-module:
```c
/* Prints string in hex format*/
VOID DBG_bytes(PCHAR bytes, DWORD size);

/* Prints string, but replaces unprintable characters with their hex values */
VOID DBG_readable_x(PCHAR string);

/* Prints string, but replaces unprintable characters with their binary values */
VOID DBG_readable_b(PCHAR string);
```
