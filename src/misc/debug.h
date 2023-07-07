#ifndef _MISC_DEBUG_H
#define _MISC_DEBUG_H

#include <stdio.h>

#define DBG_X(fmt, ...) fprintf(stderr, "[Error] " fmt " in %s:%d\n", __VA_ARGS__, __FILE__, __LINE__)
#define DBG(err) DBG_X("%s", err)
#define DBG_UNIMPL(function) DBG_X("%s is not implemented", function)


#include <windows.h>

/* Prints string in hex format*/
VOID DBG_bytes(PCHAR bytes, DWORD size);

/* Prints string, but replaces unprintable characters with their hex values */
VOID DBG_readable_x(PCHAR string);

/* Prints string, but replaces unprintable characters with their binary values */
VOID DBG_readable_b(PCHAR string);

#endif // !_MISC_DEBUG_H
