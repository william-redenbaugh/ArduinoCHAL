#include "global_includes.h"
#include "Arduino.h"
#ifdef WIFI_UDP
#include "WiFi.h"
#include "WiFiUdp.h"

#define DEBUG_WIFI

#ifdef DEBUG_WIFI
#define wifi_println(...) os_println(__VA_ARGS__)
#define wifi_print(...) print(__VA_ARGS__)
#define wifi_printf(...) printf(__VA_ARGS__)
#endif

#ifdef OS_WIFI_ARDUINO

int os_wifi_connect_sta(char *ssid, char *password)
{
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    print(".");
    delay(500);
  }
  wifi_println("Connected! IP address: ");
  wifi_println(WiFi.localIP());

  return OS_RET_OK;
}

int os_wifi_disconnect_sta()
{
  WiFi.disconnect();
  return OS_RET_OK;
}

os_udp_server_t *os_wifi_setup_udp_server(int port)
{

  if (WiFi.status() != WL_CONNECTED)
  {
    return NULL;
  }

  os_udp_server_t *udp_server = new os_udp_server_t;
  udp_server->udp.begin(port);

  return udp_server;
}

int os_wifi_deconstruct_udp_server(os_udp_server_t *udp)
{
  if (udp == NULL)
  {
    return OS_RET_NULL_PTR;
  }

  delete udp;

  return OS_RET_OK;
}

int os_wifi_start_udp_transmission(os_udp_server_t *udp, char *ip, uint16_t port)
{
  if (WiFi.status() != WL_CONNECTED)
  {
    return OS_RET_NOT_INITIALIZED;
  }

  if (udp == NULL)
  {
    return OS_RET_NULL_PTR;
  }

  if (udp->udp.beginPacket(ip, port) < 0)
  {
    return OS_RET_INT_ERR;
  }

  return OS_RET_OK;
}

int os_wifi_stop_udp_transmission(os_udp_server_t *udp)
{
  if (udp == NULL)
  {
    return OS_RET_NULL_PTR;
  }

  udp->udp.endPacket();
  return OS_RET_OK;
}

int os_wifi_transmit_udp_packet(os_udp_server_t *udp, uint16_t packet_size, uint8_t *arr)
{
  if (udp == NULL)
  {
    return OS_RET_NULL_PTR;
  }

  return udp->udp.write(arr, packet_size);
}

static inline int read_packet(os_udp_server_t *udp, uint16_t *packet_size, uint8_t *arr)
{
  if (udp == NULL)
  {
    return OS_RET_NULL_PTR;
  }

  int packetSize = udp->udp.parsePacket();
  if (packetSize > 0)
  {
    // Max allowed size
    if (*packet_size > packetSize)
    {
      *packet_size = packetSize;
    }

    if (udp->udp.read(arr, packetSize) == 0)
    {
      return OS_RET_NO_AVAILABLE_DATA;
    }
  }
  return OS_RET_OK;
  ;
}

int os_wifi_receive_packet(os_udp_server_t *udp, uint16_t *packet_size, uint8_t *arr, uint32_t timeout_ms)
{
  if (udp == NULL)
  {
    return OS_RET_NULL_PTR;
  }

  if (timeout_ms == 0)
  {
    return read_packet(udp, packet_size, arr);
  }
  else
  {
    uint32_t start_millis = millis();
    // Timeout handler
    while (start_millis + timeout_ms > millis())
    {
      if (read_packet(udp, packet_size, arr) == OS_RET_OK)
      {
        return OS_RET_OK;
      }

      delay(OS_WIFI_CHECK_PACKET_INTERVAL);
    }
  }

  return OS_RET_NO_AVAILABLE_DATA;
}

int os_wifi_receive_packet_indefinite(os_udp_server_t *udp, uint16_t *packet_size, uint8_t *arr)
{
  if (udp == NULL)
  {
    return OS_RET_NULL_PTR;
  }

  while (read_packet(udp, packet_size, arr) != OS_RET_OK)
    delay(OS_WIFI_CHECK_PACKET_INTERVAL);

  return OS_RET_OK;
}

#endif
#endif