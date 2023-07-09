#include <stdio.h>
#include "resolvec.h"

#include <assert.h>

int main() {
    PCHAR domain = "www.google.com";
    PCHAR ip = "10.20.123.111";

    //PCHAR dns_domain = "\x03""www\x06""google\x03""com\x00";
    PCHAR dns_domain = dns_format(domain);
    PCHAR reverse_ip = dns_format(ip);

    DBG_readable_x(dns_domain);
    DBG_readable_x(reverse_ip);

    PDNS_PACKET packet = dns_query_create(domain, 0x0001, 0x0001);
    dns_packet_print(packet);

    PDWORD bytes_size = (PDWORD)malloc(sizeof(DWORD));
    PCHAR dns_bytes = dns_query_to_buffer(packet, bytes_size);
    printf("dns_bytes size: %d\n", *bytes_size);
    DBG_bytes(dns_bytes, *bytes_size);

    // init wsa
    WSADATA wsa_data;
    WORD wsa_version = MAKEWORD(2, 2);
    INT wsa_result = WSAStartup(wsa_version, &wsa_data);
    if (wsa_result != 0) {
        DBG_X("WSA failed with error: %d\n", wsa_result);
        return -1;
    }

    SOCKET sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sock == INVALID_SOCKET) {
        DBG_X("socket() failed with error: %d\n", WSAGetLastError());
        WSACleanup();
        return -1;
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(53);
    server_addr.sin_addr.s_addr = inet_addr("1.1.1.1");

    INT send_result = send_query(sock, dns_bytes, *bytes_size, &server_addr);

    dns_packet_free(packet);
    free(bytes_size);
    free(dns_bytes);

    return 0;
}