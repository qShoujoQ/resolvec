#include "bytes.h"
#include "debug.h"

#include <stdarg.h>

BOOL compare_bytes(const PCHAR bytes1, const PCHAR bytes2, const DWORD size)
{
    for (DWORD i = 0; i < size; i++)
    {
        if (bytes1[i] != bytes2[i])
        {
            return FALSE;
        }
    }
    return TRUE;
}

BOOL is_ipv4(const PCHAR domain)
{
    const PCHAR delim = ".";

    size_t str_max = strlen(domain);
    PCHAR context = NULL;

    PCHAR temp = strdup(domain);

    if (temp == NULL)
    {
        DBG("strdup in is_ipv4 failed");
        exit(EXIT_FAILURE);
    }

    PCHAR token = strtok_s(temp, delim, &context);

    while (token != '\0')
    {
        if (strlen(token) > 3)
        {
            return FALSE;
        }

        for (size_t i = 0; i < strlen(token); i++)
        {
            if (!isdigit(token[i]))
            {
                return FALSE;
            }
        }

        if (atoi(token) > 255)
        {
            return FALSE;
        }

        token = strtok_s(NULL, delim, &context);
    }

    free(temp);

    return TRUE;
}

PCHAR format_bytes(PCHAR fmt, ...)
{
    va_list args;

    va_start(args, fmt);
    DWORD size = vsnprintf(NULL, 0, fmt, args);
    va_end(args);

    PCHAR buffer = (PCHAR)malloc(size + 1);

    if (buffer == NULL)
    {
        DBG("Failed to allocate memory for buffer");
        return NULL;
    }

    va_start(args, fmt);
    vsnprintf(buffer, size + 1, fmt, args);
    va_end(args);

    return buffer;
}

DWORD sizeof_buffer(PCHAR buffer, DWORD allocated_size)
{
    DWORD size = allocated_size;

    while (size > 0 && buffer[size - 1] == '\0')
    {
        size--;
    }

    return size;
}