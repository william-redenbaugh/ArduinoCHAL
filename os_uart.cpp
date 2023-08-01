#include "global_includes.h"
#include <Arduino.h>

static inline Stream *which_interface(int fd)
{
    switch (fd)
    {
    case 1:
        return &Serial;
    case 2:
        return &Serial1;
    case 3:
#ifdef CONFIG_IDF_TARGET_ESP32S3
        &Serial2;
#endif
    default:
        return NULL;
    }
}

static inline void init_which_interface(int fd, int baud)
{
    switch (fd)
    {
    case 1:
        Serial.begin(baud);
    case 2:
        Serial1.begin(baud);
    case 3:
#ifdef CONFIG_IDF_TARGET_ESP32S3
        Serial2.begin(baud);
#endif
    default:
        return;
    }
}

static inline void deinit_which_interface(int fd)
{
    switch (fd)
    {
    case 1:
        Serial.end();
    case 2:
        Serial1.end();
    case 3:
#ifdef CONFIG_IDF_TARGET_ESP32S3
        Serial2.end();
#endif
    default:
        return;
    }
}

int os_uart_begin(os_uart_t *uart, int fd, int baud)
{
    if (uart == NULL)
        return OS_RET_NULL_PTR;

    uart->fd = fd;
    uart->baud = baud;
    init_which_interface(uart->fd, uart->baud);
    return 0;
}

int os_uart_end(os_uart_t *uart)
{
    if (uart == NULL)
        return OS_RET_NULL_PTR;
    deinit_which_interface(uart->fd);
    return 0;
}

void os_uart_printf(os_uart_t *uart, const char *format, ...)
{
    static char data[512];
    int size = sprintf(data, format);

    os_uart_send(uart, (uint8_t *)data, (size_t)size);
}

int os_uart_readstring_until(os_uart_t *uart, char terminator, uint8_t *data, size_t size)
{
    if (uart == NULL)
        return OS_RET_NULL_PTR;

    Stream *interface = which_interface(uart->fd);
    if (interface == NULL)
        return OS_RET_NULL_PTR;

    size_t len = interface->readBytesUntil(terminator, data, size);

    return (int)len;
}

int os_uart_readstring(os_uart_t *uart, uint8_t *data, size_t size)
{
    return os_uart_readstring_until(uart, '\n', data, size);
}

int os_uart_setbus(os_uart_t *uart, uint32_t freq_baud)
{
    if (uart == NULL)
        return OS_RET_NULL_PTR;

    init_which_interface(uart->fd, uart->baud);

    uart->baud = freq_baud;

    return 0;
}

int os_uart_transfer(os_uart_t *uart, uint8_t *rx, uint8_t *tx, size_t size)
{
    if (uart == NULL || rx == NULL || tx == NULL || size == 0)
        return OS_RET_NULL_PTR;

    // Check if the selected Serial interface is available
    Stream *interface = which_interface(uart->fd);
    if (interface == NULL)
        return OS_RET_NULL_PTR;

    // Clear the receive buffer
    while (interface->available() > 0)
        interface->read();

    // Send data
    for (size_t i = 0; i < size; i++)
        interface->write(tx[i]);

    // Receive data
    size_t bytesRead = 0;
    while (bytesRead < size)
    {
        if (interface->available() > 0)
        {
            rx[bytesRead] = interface->read();
            bytesRead++;
        }
    }

    return bytesRead;
}

int os_uart_send(os_uart_t *uart, uint8_t *buf, size_t size)
{
    if (uart == NULL || buf == NULL || size == 0)
        return OS_RET_NULL_PTR;

    // Check if the selected Serial interface is available
    Stream *interface = which_interface(uart->fd);
    if (interface == NULL)
        return OS_RET_NULL_PTR;

    // Send data
    for (size_t i = 0; i < size; i++)
        interface->write(buf[i]);

    return size;
}

int os_uart_receive(os_uart_t *uart, uint8_t *buf, size_t size)
{
    if (uart == NULL || buf == NULL || size == 0)
        return OS_RET_NULL_PTR;

    // Check if the selected Serial interface is available
    Stream *interface = which_interface(uart->fd);
    if (interface == NULL)
        return OS_RET_NULL_PTR;

    // Receive data
    size_t bytesRead = 0;
    while (bytesRead < size)
    {
        if (interface->available() > 0)
        {
            buf[bytesRead] = interface->read();
            bytesRead++;
        }
    }

    return bytesRead;
}