#include "ESP8266_AT.h"

void ESP8266_AT(UART_HandleTypeDef *uart, uint8_t timeout)
{
    _Transmit(uart, "AT", timeout);
}

void ESP8266_AT_RST(UART_HandleTypeDef *uart, uint8_t timeout)
{
    _Transmit(uart, "AT+RST", timeout);
}

void ESP8266_AT_GMR(UART_HandleTypeDef *uart, uint8_t timeout)
{
    _Transmit(uart, "AT+GMR", timeout);
}

void ESP8266_AT_GSLP(UART_HandleTypeDef *uart, uint8_t time, uint8_t timeout)
{
    int length = snprintf(NULL, 0, "%d", time);
    char time_as_str[length + 1];
    strncpy(time_as_str, snprintf(time_as_str, length + 1, "%d", time), length); // remove null terminator

    _Transmit(uart, strcat("AT+GSLP=", time_as_str), timeout);
}

void ESP8266_ATE(UART_HandleTypeDef *uart, bool echo_on, uint8_t timeout)
{
    if (echo_on)
        _Transmit(uart, "ATE1", timeout);
    else
        _Transmit(uart, "ATE0", timeout);
}

void ESP8266_RESTORE(UART_HandleTypeDef *uart, uint8_t timeout)
{
    _Transmit(uart, "AT+RESTORE", timeout);
}

void ESP8266_AT_UART_CUR_QUERY(UART_HandleTypeDef *uart, uint8_t timeout)
{
    _Transmit(uart, "AT+UART_CUR?", timeout);
}

void ESP8266_AT_UART_CUR_SET(UART_HandleTypeDef *uart, uint8_t baudrate, uint8_t databits, uint8_t stopbits, uint8_t parity, uint8_t flow_control, uint8_t timeout)
{
}

void ESP8266_AT_UART_DEF_QUERY(UART_HandleTypeDef *uart, uint8_t timeout)
{
    _Transmit(uart, "AT+UART_DEF?", timeout);
}

void ESP8266_AT_UART_DEF_SET(UART_HandleTypeDef *uart, uint8_t timeout)
{
}

void ESP8266_AT_SLEEP_QUERY(UART_HandleTypeDef *uart, uint8_t timeout)
{
    _Transmit(uart, "AT+SLEEP?", timeout);
}

void ESP8266_AT_SLEEP_SET(UART_HandleTypeDef *uart, uint8_t sleep_mode, uint8_t timeout)
{
}
