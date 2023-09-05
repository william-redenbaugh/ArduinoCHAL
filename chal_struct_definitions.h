#ifndef _CHAL_STRUCT_DEFINITIONS_H
#define _CHAL_STRUCT_DEFINITIONS_H

#include "Arduino.h"
#include "enabled_modules.h"
#ifdef WIFI_UDP

#include "WiFiUdp.h"

typedef struct os_udp_server_t
{
    WiFiUDP udp;
} os_udp_server_t;
#endif

#endif