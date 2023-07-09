# 'Net' module of resolvec

Implements network communication itself in addition to some useful formating code.

### Include functions using:
```c
#include "src/net/net.h"
```

## Functions:
format sub-module:
```c
/* Converts IP address into dns reverse-lookup format */
PCHAR reverse_lookup(PCHAR ip);

/* Converts domain or IPv4 address into dns-friendly string of bytes */
PCHAR dns_format(PCHAR domain);

/* Converts dns-formatted string of bytes into domain or IPv4 address */
PCHAR dns_unformat(PCHAR domain);
```
transfer sub-module:

## is not yet implemented
