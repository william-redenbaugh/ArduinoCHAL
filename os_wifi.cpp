#include "os_wifi.h"

int os_wifi_connect_sta(char *ssid, char *password) {
  WiFi.begin(ssid, password);
  return WiFi.status();
}

int os_wifi_disconnect_sta() {
  WiFi.disconnect();
  return WiFi.status();
}

os_udp_server_t *os_wifi_setup_udp_server(int port) {
    if(WiFi.status() != WL_CONNECTED){
        return NULL;
    }

    os_udp_server_t *udp_server =  new os_udp_server_t; 
    udp_server->udp.begin(port);

    return udp_server;
}

int os_wifi_start_udp_multicast_transmission(os_udp_server_t *udp, char *ip, uint16_t port){
    
}

int os_wifi_start_udp_transmission(os_udp_server_t *udp, char *ip, uint16_t port) {
    if(WiFi.status() != WL_CONNECTED){
        return OS_RET_NOT_INITIALIZED;
    }

    if(udp->udp.beginPacket(ip, port) < 0){
        return OS_RET_INT_ERR;
    }

    return 0;
}

int os_wifi_stop_udp_transmission(os_udp_server_t *udp) {
  udp->udp.endPacket();
  return 0;
}

int os_wifi_transmit_udp_packet(os_udp_server_t *udp, uint16_t packet_size, uint8_t *arr) {
  return udp->udp.write(arr, packet_size);
}

int os_wifi_receive_packet(os_udp_server_t *udp, uint16_t *packet_size, uint8_t *arr, uint32_t timeout_ms) {
  int packetSize = udp->udp.parsePacket();
  if (packetSize > 0) {
    *packet_size = packetSize;
    return udp->udp.read(arr, packetSize);
  }
  return 0;
}