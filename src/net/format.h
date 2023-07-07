#ifndef _NET_FORMAT_H
#define _NET_FORMAT_H

#include "../misc/misc.h"

/* Converts IP address into dns reverse-lookup format */
PCHAR reverse_lookup(PCHAR ip);

/* Converts domain or IPv4 address into dns-friendly string of bytes */
PCHAR dns_format(PCHAR domain);

/* Converts dns-formatted string of bytes into domain or IPv4 address */
PCHAR dns_unformat(PCHAR domain);

#endif // !_NET_FORMAT_H
