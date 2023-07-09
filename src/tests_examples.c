#include <stdio.h>
#include "resolvec.h"

#include <assert.h>

int main() {
    PCHAR domain = "google.com";
    PCHAR ip = "10.20.123.111";

    //PCHAR dns_domain = "\x03""www\x06""google\x03""com\x00";
    PCHAR dns_domain = dns_format(domain);
    PCHAR reverse_ip = dns_format(ip);

    DBG_readable_x(dns_domain);
    DBG_readable_x(reverse_ip);

    PDNS_PACKET packet = dns_query_create(ip, 1, 1);
    dns_packet_print(packet);

    PDWORD bytes_size = (PDWORD)malloc(sizeof(DWORD));
    PCHAR dns_bytes = dns_query_to_buffer(packet, bytes_size);
    printf("dns_bytes size: %d\n", *bytes_size);
    DBG_bytes(dns_bytes, *bytes_size);

    dns_packet_free(packet);
    free(bytes_size);
    free(dns_bytes);

    return 0;
}