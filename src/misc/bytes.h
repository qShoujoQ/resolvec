#ifndef _MISC_BYTES_H
#define _MISC_BYTES_H

#include <windows.h>

/* compare two byte arrays */
BOOL compare_bytes(const PCHAR bytes1, const PCHAR bytes2, const DWORD size);

/* check if string is IPv4 address */
BOOL is_ipv4(PCHAR domain);

/* replacement of sprintf, i just hate it :< */
PCHAR format_bytes(PCHAR fmt, ...);

/* returns real size of buffer allocated with calloc / memseted to 0 */
DWORD sizeof_buffer(PCHAR buffer, DWORD allocated_size);

#endif // !_MISC_BYTES_H
