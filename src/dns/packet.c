#include "packet.h"

#include "../net/net.h"

PDNS_PACKET dns_query_create(PCHAR domain, WORD type, WORD dclass) {
    PDNS_PACKET packet = (PDNS_PACKET)malloc(sizeof(DNS_PACKET));
    if (packet == NULL) {
        DBG("dns_query_create: malloc failed\n");
        return NULL;
    }

    packet->header.id = GetProcessId(GetCurrentProcess());
    packet->header.flags.value = 0x0100;
    packet->header.qdcount = 0x0001;
    packet->header.ancount = 0x0000;
    packet->header.nscount = 0x0000;
    packet->header.arcount = 0x0000;

    packet->question.qname = dns_format(domain);
    packet->question.qtype = type;
    packet->question.qclass = dclass;

    packet->answers = NULL;

    return packet;
}

VOID dns_packet_free(PDNS_PACKET packet) {
    if (packet == NULL) {
        DBG("dns_packet_free: packet is NULL\n");
        return;
    }

    if (packet->question.qname != NULL) {
        free(packet->question.qname);
    }

    if (packet->answers != NULL) {
        free(packet->answers);
    }

    free(packet);
}

VOID dns_packet_print(PDNS_PACKET packet) {
    if (packet == NULL) {
        DBG("dns_packet_print: packet is NULL\n");
        return;
    }

    // use printf, DBG is just for errors.
    printf("DNS Packet:\n\tHeader:\n\t\tid: %d\n", packet->header.id);
    printf("\t\tflags: %#04X\n", packet->header.flags.value);
    printf("\t\tqdcount: %d\n", packet->header.qdcount);
    printf("\t\tancount: %d\n", packet->header.ancount);
    printf("\t\tnscount: %d\n", packet->header.nscount);
    printf("\t\tarcount: %d\n", packet->header.arcount);
    printf("\tQuestion:\n\t\tqname:");
    DBG_readable_x(packet->question.qname);
    printf("\t\tqtype: %d\n", packet->question.qtype);
    printf("\t\tqclass: %d\n", packet->question.qclass);
    printf("\tAnswers:\n\t\t");
    if (packet->answers == NULL) {
        printf("NULL\n");
    } else {
        printf("NOT NULL\n");
        // ! TODO: ! //
    }
}