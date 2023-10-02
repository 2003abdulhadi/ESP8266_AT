#include "ESP8266_AT.h"

void ESP8266_INIT(UART_HandleTypeDef *usart)
{
    ESP8266_USART = usart;
}

void ESP8266_AT()
{
    HAL_UART_Transmit(&ESP8266_USART, (uint8_t *)"AT\r\n", strlen("AT\r\n"), 100);
}

void ESP8266_AT_RST()
{
}

void ESP8266_AT_GMR()
{
}

void ESP8266_AT_GSLP(uint8_t time)
{
}

void ESP8266_ATE(bool state)
{
}

void ESP8266_RESTORE()
{
}

void ESP8266_AT_UART_CUR_QUERY()
{
}

void ESP8266_AT_UART_CUR_SET(uint8_t baudrate, uint8_t databits, uint8_t stopbits, uint8_t parity, uint8_t flow_control)
{
}

void ESP8266_AT_UART_DEF_QUERY()
{
}

void ESP8266_AT_UART_DEF_SET()
{
}

void ESP8266_AT_SLEEP_QUERY()
{
}

void ESP8266_AT_SLEEP_SET(uint8_t sleep_mode)
{
}
