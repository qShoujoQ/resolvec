/* malloc() failure is considered fatal, and in that case program will terminate immediately.*/

#include "format.h"

#include <string.h>

PCHAR reverse_lookup(PCHAR ip)
{
    if (!is_ipv4(ip))
    {
        DBG("Passed IP is not IPv4\n");
        return NULL;
    }

    const PCHAR delimiter = ".";
    const PCHAR suffix = ".in-addr.arpa";

    PCHAR result = (PCHAR)malloc(strlen(ip) + strlen(suffix) + 1);
    PCHAR domain_dup = strdup(ip);

    if (result == NULL || domain_dup == NULL)
    {
        DBG("Failed to allocate memory for reverse lookup\n");
        exit(EXIT_FAILURE);
    }

    PCHAR context = NULL;
    PCHAR token = strtok_s(domain_dup, delimiter, &context);

    BYTE octet[4] = {0};
    BYTE index = 0;

    while (token != NULL)
    {
        octet[index++] = atoi(token);
        token = strtok_s(NULL, delimiter, &context);
    }

    sprintf_s(result, strlen(ip) + strlen(suffix) + 1, "%d.%d.%d.%d%s", octet[3], octet[2], octet[1], octet[0], suffix);

    free(domain_dup);

    return result;
}

PCHAR dns_format(PCHAR domain)
{
    PCHAR domain_dup = NULL;

    if (is_ipv4(domain)) {
        domain_dup = reverse_lookup(domain);
    } else {
        domain_dup = strdup(domain);
    }

    if (domain_dup == NULL)
    {
        DBG("Failed to allocate memory for DNS format\n");
        exit(EXIT_FAILURE);
    }

    const DWORD MAX_DNS_LEN = 255;
    const PCHAR delimiter   = ".";

    PCHAR formatted_domain = (PCHAR)malloc(MAX_DNS_LEN + 1);

    if (formatted_domain == NULL)
    {
        DBG("Failed to allocate memory for DNS format\n");
        free(domain_dup);
        exit(EXIT_FAILURE);
    }

    memset(formatted_domain, 0, MAX_DNS_LEN);

    PCHAR context   = NULL;
    PCHAR token     = strtok_s(domain_dup, delimiter, &context);

    while (token != NULL)
    {
        DWORD token_len = strlen(token);

        if (token_len > MAX_DNS_LEN)
        {
            DBG("Domain name is too long\n");
            free(domain_dup);
            free(formatted_domain);
            exit(EXIT_FAILURE);
        }

        formatted_domain[strlen(formatted_domain)] = token_len;

        strcat_s(formatted_domain, MAX_DNS_LEN, token);

        token = strtok_s(NULL, delimiter, &context);
    }

    free(domain_dup);

    return formatted_domain;
}

PCHAR dns_unformat(PCHAR domain) {
    DBG_UNIMPL("dns_unformat");
    return NULL;
}