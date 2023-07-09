#include "transfer.h"
#include "../misc/misc.h"

INT send_query(SOCKET sock, PCHAR buffer, DWORD buffer_size, struct sockaddr_in* server_addr) {
    INT send_result = sendto(sock, buffer, buffer_size, 0, (struct sockaddr*)server_addr, sizeof(*server_addr));
    if (send_result == SOCKET_ERROR) {
        DBG_X("sendto() failed with error: %d\n", WSAGetLastError());
    }

    return send_result;
}
