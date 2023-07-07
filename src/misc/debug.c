#include "debug.h"

VOID DBG_bytes(PCHAR bytes, DWORD size)
{
    for (DWORD i = 0; i < size; i++)
    {
        printf("0x%02X ", bytes[i]);
    }
    printf("\n");
}

VOID DBG_readable_x(PCHAR string)
{
    for (DWORD i = 0; i < strlen(string); i++)
    {
        if (isprint(string[i]))
        {
            printf("%c", string[i]);
        }
        else
        {
            printf("\\%#02x\\", (unsigned char) string[i]);
        }
    }
    printf("\n");
}

VOID DBG_readable_b(PCHAR string)
{
    for (DWORD i = 0; i < strlen(string); i++)
    {
        if (isprint(string[i]))
        {
            printf("%c", string[i]);
        }
        else
        {
            printf("\\0b");
            for (DWORD j = 0; j < 8; j++)
            {
                printf("%d", (unsigned char) (string[i] >> (7 - j)) & 1);
            }
            printf("\\");
        }
    }
    printf("\n");
}
