#ifndef _DNS_PACKET_H
#define _DNS_PACKET_H

#include "../misc/misc.h"

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

struct _dns_header {
    WORD id;
    union _dns_flags flags;
    WORD qdcount;
    WORD ancount;
    WORD nscount;
    WORD arcount;
};

struct _dns_question {
    PCHAR qname;
    WORD qtype;
    WORD qclass;
};

struct _dns_rr {
    PCHAR name;
    WORD type;
    WORD dclass;    // idk why it won't let me use class
    DWORD ttl;
    WORD rdlength;
    PCHAR rdata;
};

typedef struct {
    struct _dns_header header;
    struct _dns_question question;
    struct _dns_rr *answers;  
} DNS_PACKET;
typedef DNS_PACKET *PDNS_PACKET;

/* allocates memory for a dns packet and fills it with the given data */
PDNS_PACKET dns_query_create(PCHAR domain, WORD type, WORD dclass);

/* creates DNS_PACKET from raw data */
PDNS_PACKET dns_response_from_buffer(PCHAR buffer, DWORD buffer_size);

/* frees memory allocated for a dns packet */
VOID dns_packet_free(PDNS_PACKET packet);

/* returns ANCOUNT answers from the response */
PCHAR read_answers(PDNS_PACKET response);

VOID dns_packet_print(PDNS_PACKET packet);

#endif // !_DNS_PACKET_H