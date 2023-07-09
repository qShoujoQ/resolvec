# 'DNS' module of resolvec

Implements core DNS functionality - packet creation, serialization and deserialization.

### Include functions using:
```c
#include "src/dns/dns.h"
```

## Structures and data types:
#### !!! All values should be stored in network byte order !!!

[ ] Is, and should be public:
```c
typedef struct {
    struct _dns_header header;
    struct _dns_question question;
    struct _dns_rr *answers;        // Can be NULL, code is ready for that
} DNS_PACKET;
typedef DNS_PACKET *PDNS_PACKET;
```

[ ] Should be private, but now I'm just trying to make it work:

Not realy needed, maybe if I plan on making full-fledged DNS server or something like that:
```c
/* Usefull data type for storing DNS flags */
union _dns_flags {
    struct {
        WORD qr : 1;
        WORD opcode : 4;
        WORD aa : 1;
        WORD tc : 1;
        WORD rd : 1;
        WORD ra : 1;
        WORD z : 3;
        WORD rcode : 4;
    } bits;
    WORD value;
};
```

treated as giant data type, not as structure, basicly no need for serialization / deserialization:
```c
struct _dns_header {
    WORD id;
    union _dns_flags flags;
    WORD qdcount;
    WORD ancount;
    WORD nscount;
    WORD arcount;
};
```

```c
struct _dns_question {
    PCHAR qname;    // stored in dns-friendly format
    WORD qtype;
    WORD qclass;
};
```

```c
struct _dns_rr {
    PCHAR name;
    WORD type;
    WORD dclass;    // idk why it won't let me use class
    DWORD ttl;
    WORD rdlength;
    PCHAR rdata;
};
```

## Functions (some will be moved in future):
```c
/* allocates memory for a dns packet and fills it with the given data */
PDNS_PACKET dns_query_create(PCHAR domain, WORD type, WORD dclass);

/* creates DNS_PACKET from raw data */
PDNS_PACKET dns_response_from_buffer(PCHAR buffer, DWORD buffer_size);

/* frees memory allocated for a dns packet */
VOID dns_packet_free(PDNS_PACKET packet);

/* returns ANCOUNT answers from the response */
PCHAR *read_answers(PDNS_PACKET response);

/* serializes DNS_PACKET to a buffer */
PCHAR dns_query_to_buffer(PDNS_PACKET packet, PDWORD buffer_size);

/* prints DNS_PACKET to stdout */
VOID dns_packet_print(PDNS_PACKET packet);

/* main function of program: resolves domain name to IP address and the other way around */
PCHAR dns_resolve(PCHAR domain);
```