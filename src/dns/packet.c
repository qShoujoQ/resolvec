#include "packet.h"

#include "../misc/misc.h"
#include "../net/net.h"

PDNS_PACKET dns_query_create(PCHAR domain, WORD type, WORD dclass)
{
    PDNS_PACKET packet = (PDNS_PACKET)malloc(sizeof(DNS_PACKET));
    if (packet == NULL)
    {
        DBG("dns_query_create: malloc failed\n");
        exit(EXIT_FAILURE);
    }

    packet->header.id = htons(GetProcessId(GetCurrentProcess()));
    packet->header.flags.value = htons(0x0100);
    packet->header.qdcount = htons(0x0001);
    packet->header.ancount = 0x0000;
    packet->header.nscount = 0x0000;
    packet->header.arcount = 0x0000;

    packet->question.qname = dns_format(domain);
    packet->question.qtype = htons(type);
    packet->question.qclass = htons(dclass);
    // to reverse htons, use ntohs

    packet->answers = NULL;

    return packet;
}

VOID dns_packet_free(PDNS_PACKET packet)
{
    if (packet == NULL)
    {
        DBG("dns_packet_free: packet is NULL\n");
        return;
    }

    if (packet->question.qname != NULL)
        free(packet->question.qname);

    if (packet->answers != NULL)
        free(packet->answers);

    free(packet);
}

VOID dns_packet_print(PDNS_PACKET packet)
{
    // printf("DNS Packet:\n\tHeader:\n\t\tid: %d\n", packet->header.id);
    printf("DNS Packet:\n\tHeader:\n\t\tid: %d\n", ntohs(packet->header.id));
    printf("\t\tflags: %#04X\n", ntohs(packet->header.flags.value));
    printf("\t\tqdcount: %d\n", ntohs(packet->header.qdcount));
    printf("\t\tancount: %d\n", ntohs(packet->header.ancount));
    printf("\t\tnscount: %d\n", ntohs(packet->header.nscount));
    printf("\t\tarcount: %d\n", ntohs(packet->header.arcount));
    printf("\tQuestion:\n\t\tqname:");
    DBG_readable_x(packet->question.qname);
    printf("\t\tqtype: %d\n", ntohs(packet->question.qtype));
    printf("\t\tqclass: %d\n", ntohs(packet->question.qclass));
    printf("\tAnswers:\n\t\t");
    if (packet->answers == NULL)
    {
        printf("NULL\n");
    }
    else
    {
        for (WORD i = 0; i < packet->header.ancount; i++)
        {
            printf("Answer %d:\n\t\t\tname: ", i);
            DBG_readable_x(packet->answers[i].name);
            printf("\t\t\ttype: %d\n", ntohs(packet->answers[i].type));
            printf("\t\t\tdclass: %d\n", ntohs(packet->answers[i].dclass));
            printf("\t\t\tttl: %d\n", ntohl(packet->answers[i].ttl));
            printf("\t\t\trdlength: %d\n", ntohs(packet->answers[i].rdlength));
            printf("\t\t\trdata: ");
            DBG_readable_x(packet->answers[i].rdata);
        }
    }
}

PCHAR *read_answers(PDNS_PACKET response)
{
    if (response->header.ancount == 0)
    {
        DBG("read_answers: response has no answers\n");
        exit(EXIT_FAILURE);
    }

    PCHAR *answers = (PCHAR *)malloc(sizeof(PCHAR) * response->header.ancount);
    if (answers == NULL)
    {
        DBG("read_answers: malloc failed\n");
        exit(EXIT_FAILURE);
    }

    for (WORD i = 0; i < response->header.ancount; i++)
    {
        answers[i] = (PCHAR)malloc(sizeof(PCHAR) * DNS_MAX_NAME_LEN);
        if (answers[i] == NULL)
        {
            DBG("read_answers: malloc failed\n");
            exit(EXIT_FAILURE);
        }
        memset(answers[i], 0, DNS_MAX_NAME_LEN);

        memcpy(answers[i], response->answers[i].rdata, response->answers[i].rdlength);
    }

    return answers;
}

// where buffer size if out parameter
PCHAR dns_query_to_buffer(PDNS_PACKET packet, PDWORD buffer_size)
{
    *buffer_size = sizeof(struct _dns_header) + strlen(packet->question.qname) + sizeof(WORD) * 2;

    PCHAR buffer = (PCHAR)malloc(*buffer_size);
    
    if (buffer == NULL)
    {
        DBG("dns_query_to_buffer: malloc failed\n");
        exit(EXIT_FAILURE);
    }

    memcpy(buffer, &packet->header, sizeof(struct _dns_header));
    memcpy(buffer + sizeof(struct _dns_header), packet->question.qname, strlen(packet->question.qname));
    memcpy(buffer + sizeof(struct _dns_header) + strlen(packet->question.qname), &packet->question.qtype, sizeof(WORD));
    memcpy(buffer + sizeof(struct _dns_header) + strlen(packet->question.qname) + sizeof(WORD), &packet->question.qclass, sizeof(WORD));

    return buffer;
}
