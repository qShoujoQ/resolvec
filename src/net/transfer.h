/*
    ! TODO !
    *- exchange() function for sending buffer to server and receiving response
    *- send() function for sending buffer to server
    *- recv() function for receiving response from server
*/

#ifndef _NET_TRANSFER_H
#define _NET_TRANSFER_H

#include "../misc/misc.h"

INT send_query(SOCKET sock, PCHAR buffer, DWORD buffer_size, struct sockaddr_in* server_addr);
INT recv_response(SOCKET sock, PCHAR buffer, DWORD buffer_size);

// 'out' in this case means the buffer that is sent to the server, not like 'out' argument in functions
VOID exchange(SOCKET sock, PCHAR out_buffer, DWORD out_buffer_size, PCHAR in_buffer, DWORD in_buffer_size);

#endif // !_NET_TRAN
