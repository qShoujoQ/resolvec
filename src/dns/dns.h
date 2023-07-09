#ifndef _DNS_H
#define _DNS_H

#include "../misc/misc.h"
#include "../net/net.h"

#include "packet.h"

/* Main function of whole program, returns first responce from server */
PCHAR resolve(PCHAR domain);

#endif // !_DNS_H