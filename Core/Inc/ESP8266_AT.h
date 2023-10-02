/* ESP8266_AT.h by Abdul Hadi 2023
* Driver for ESP8266 wifi module using AT commands
* All functions are implemented per v3.0.5 of AT commands found at
* https://www.espressif.com/sites/default/files/documentation/4a-esp8266_at_instruction_set_en.pdf
* This project is maintained at
* https://github.com/2003abdulhadi/ESP8266_AT
*/

#ifndef ESP8266_AT_H
#define ESP8266_AT_H

#define ESP8266_USART huart1 //change this to fit your project

//basic AT commands

void ESP8266_AT();
void ESP8266_AT_RST();
void ESP8266_AT_GMR();
void ESP8266_AT_GSLP();
void ESP8266_ATE();
void ESP8266_RESTORE();
void ESP8266_AT_UART_CUR();
void ESP8266_AT_UART_DEF();
void ESP8266_AT_SLEEP();
void ESP8266_AT_WAKEUPGPIO();
void ESP8266_AT_RFPOWER();
void ESP8266_AT_RFVDD();
void ESP8266_AT_SYSRAM();
void ESP8266_AT_SYSADC();
void ESP8266_AT_SYSIOSETCFG();
void ESP8266_AT_SYSIOGETCFG();
void ESP8266_AT_SYSGPIODIR();
void ESP8266_AT_SYSGPIOWRITE();
void ESP8266_AT_SYSGPIOREAD();
void ESP8266_AT_SYSMSG_CUR();
void ESP8266_AT_SYSMSG_DEF();

#endif