/**
 * ESP8266_AT.h by Abdul Hadi 2023
 * Driver for ESP8266 wifi module using AT commands
 * All functions are implemented per v3.0.5 of AT commands found at
 * https://www.espressif.com/sites/default/files/documentation/4a-esp8266_at_instruction_set_en.pdf
 * This project is maintained at
 * https://github.com/2003abdulhadi/ESP8266_AT
 */

#ifndef ESP8266_AT_H
#define ESP8266_AT_H

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "stm32f4xx_hal_uart.h"

#define _Transmit(uart, str, timeout) HAL_UART_Transmit(&uart, (uint8_t *)strcat(str, "\r\n"), strlen(strcat(str, "\r\n")), timeout)

// basic AT commands

/*
 * @brief Tests AT Startup
 * @returns OK
 */
void ESP8266_AT(UART_HandleTypeDef *uart, uint8_t timeout);

/*
 * @brief Restarts the Module
 * @returns OK
 */
void ESP8266_AT_RST(UART_HandleTypeDef *uart, uint8_t timeout);

/*
 * @brief Checks Version Information
 * @returns <AT version info>: information about the AT version,
 * @returns <SDK version info>: information about the SDK version,
 * @returns <compile time>: the duration of time for compiling the BIN,
 * @returns OK
 */
void ESP8266_AT_GMR(UART_HandleTypeDef *uart, uint8_t timeout);

/*
 * @brief Enters Deep-sleep Mode. ESP8266 will wake up after
 * Deep-sleep for as many milliseconds (ms) as <time> indicates
 * @param <time>: the duration of ESP8266's sleep. Unit: ms
 * @returns <time>, OK
 * @note A minor adjustment has to be made before the module
 * enter the Deep-sleep mode, i.e., connecting XPD_DCDC to
 * EXT_RSTB via a 0-ohm resistor.
 */
void ESP8266_AT_GSLP(UART_HandleTypeDef *uart, uint8_t time, uint8_t timeout);

/*
 * @brief AT Commands Echoing, This command ATE is used to trigger
 * command echo. It means that entered commands can be echoed back
 * to the sender when ATE command is used.
 * @param bool, true: Switches echo on, false: switches echo off
 * @returns OK
 */
void ESP8266_ATE(UART_HandleTypeDef *uart, bool echo_on, uint8_t timeout);

/*
 * @brief Restores the Factory Default Settings. The execution of
 * this command will reset all parameters saved in flash, and restore
 * the factory default settings of the module. The chip will be
 * restarted when this command is executed.
 * @returns OK
 */
void ESP8266_RESTORE(UART_HandleTypeDef *uart, uint8_t timeout);

/*
 * @brief Query Current UART Configuration; Not Saved in the
 * Flash. Command AT+UART_CUR? will return the actual value of
 * UART configuration parameters, which may have allowable errors
 * compared with the set value because of the clock division.
 * For example, if the UART baud rate is set as 115200, the baud
 * rate returned by using command AT+UART_CUR? could be 115273.
 * @returns +UART_CUR:<baudrate>,<databits>,<stop bits>,<parity>,
 * <flow control>, OK
 */
void ESP8266_AT_UART_CUR_QUERY(UART_HandleTypeDef *uart, uint8_t timeout);

/*
 * @brief Set Current UART Configuration; Not Saved in the Flash.
 * The configuration changes will NOT be saved in the flash. The
 * use of flow control requires the support of hardware. MTCK is
 * UART0 CTS. MTDO is UART0 RTS
 * @param <baudrate>: UART baud rate. 110 <= baud 4,608,000.
 * @param <databits>: data bits. data bits :={5,6,7,8} for 5, 6,
 * 7, or 8 bit data respectively
 * @param <stopbits>: stop bits. stop bits :={1,2,3} for 1, 1.5,
 * or 2 bit stop bits respectively
 * @param <parity>: parity bit. parity :={0,1,2} for None, Odd,
 * or Even respectively
 * @param <flow control>: flow control. flow control={0,1,2,3}.
 * 0: flow control is not enabled. 1: enable RTS. 2: enable CTS.
 * 3: enable both RTS and CTS
 * @returns OK
 */
void ESP8266_AT_UART_CUR_SET(UART_HandleTypeDef *uart, uint8_t baudrate,
                             uint8_t databits, uint8_t stopbits,
                             uint8_t parity, uint8_t flow_control,
                             uint8_t timeout);

/*
 * @brief Query Current UART Configuration; Saved in the Flash.
 * @returns +UART_DEF:<baudrate>,<databits>,<stop bits>,<parity>,
 * <flow control>, OK
 */
void ESP8266_AT_UART_DEF_QUERY(UART_HandleTypeDef *uart, uint8_t timeout);

/*
 * @brief Set Current UART Configuration; Saved in the Flash.
 * The configuration changes will be saved in the user parameter
 * area in the flash, and will still be valid when the chip is
 * powered on again. The use of flow control requires the support
 * of hardware. MTCK is UART0 CTS. MTDO is UART0 RTS
 * @param <baudrate>: UART baud rate. 110 <= baud 4,608,000.
 * @param <databits>: data bits. data bits :={5,6,7,8} for 5, 6,
 * 7, or 8 bit data respectively
 * @param <stopbits>: stop bits. stop bits :={1,2,3} for 1, 1.5,
 * or 2 bit stop bits respectively
 * @param <parity>: parity bit. parity :={0,1,2} for None, Odd,
 * or Even respectively
 * @param <flow control>: flow control. flow control={0,1,2,3}.
 * 0: flow control is not enabled. 1: enable RTS. 2: enable CTS.
 * 3: enable both RTS and CTS
 * @returns OK
 */
void ESP8266_AT_UART_DEF_SET(UART_HandleTypeDef *uart, uint8_t timeout);

/*
 * @breif Query Sleep Mode. 0: sleep mode disabled. 1; Light-sleep
 * mode. 2: Modem-sleep mode. This command can only be used in
 * Station mode.
 * @returns +SLEEP:<sleep mode>, OK
 */
void ESP8266_AT_SLEEP_QUERY(UART_HandleTypeDef *uart, uint8_t timeout);

/*
 * @brief Set Sleep Mode.
 * @param <sleep mode>. sleep mode := {0,1,2}. 0: disables sleep mode.
 * 1: Light-sleep mode. 2: Modem-sleep mode. This command can only be
 * used in Station mode. Modem-sleep is the default sleep mode.
 * @returns OK
 */
void ESP8266_AT_SLEEP_SET(UART_HandleTypeDef *uart, uint8_t sleep_mode,
                          uint8_t timeout);

// to be implemented

// void ESP8266_AT_WAKEUPGPIO();
// void ESP8266_AT_RFPOWER();
// void ESP8266_AT_RFVDD();
// void ESP8266_AT_SYSRAM();
// void ESP8266_AT_SYSADC();
// void ESP8266_AT_SYSIOSETCFG();
// void ESP8266_AT_SYSIOGETCFG();
// void ESP8266_AT_SYSGPIODIR();
// void ESP8266_AT_SYSGPIOWRITE();
// void ESP8266_AT_SYSGPIOREAD();
// void ESP8266_AT_SYSMSG_CUR();
// void ESP8266_AT_SYSMSG_DEF();

// Wi-Fi AT Commands

// void ESP8266_AT_CWMODE_CUR();
// void ESP8266_AT_CWMODE_DEF();
// void ESP8266_AT_CWJAP_CUR();
// void ESP8266_AT_CWJAP_DEF();
// void ESP8266_AT_CWLAPOPT();
// void ESP8266_AT_CWLAP();
// void ESP8266_AT_CWQAP();
// void ESP8266_AT_CWSAP_CUR();
// void ESP8266_AT_CWSAP_DEF();
// void ESP8266_AT_CWLIF();
// void ESP8266_AT_CWDHCP_CUR();
// void ESP8266_AT_CWDHCP_DEF();
// void ESP8266_AT_CWDHCPS_CUR();
// void ESP8266_AT_CWDHCPS_DEF();
// void ESP8266_AT_CWAUTOCONN();
// void ESP8266_AT_CIPSTAMAC_CUR();
// void ESP8266_AT_CIPSTAMAC_DEF();
// void ESP8266_AT_CIPAPMAC_CUR();
// void ESP8266_AT_CIPAPMAC_DEF();
// void ESP8266_AT_CIPSTA_CUR();
// void ESP8266_AT_CIPSTA_DEF();
// void ESP8266_AT_CIPAP_CUR();
// void ESP8266_AT_CIPAP_DEF();
// void ESP8266_AT_CWSTARTSMART();
// void ESP8266_AT_CWSTOPSMART();
// void ESP8266_AT_CWSTARTDISCOVER();
// void ESP8266_AT_CWSTOPDISCOVER();
// void ESP8266_AT_WPS();
// void ESP8266_AT_MDNS();
// void ESP8266_AT_CWHOSTNAME();
// void ESP8266_AT_CWCOUNTRY_CUR();
// void ESP8266_AT_CWCOUNTRY_DEF();

// TCP/IP-Related AT Commands

// void ESP8266_AT_CIPSTATUS();
// void ESP8266_AT_CIPDOMAIN();
// void ESP8266_AT_CIPSTART();
// void ESP8266_AT_CIPSSLSIZE();
// void ESP8266_AT_CIPSSLCONF();
// void ESP8266_AT_CIPSEND();
// void ESP8266_AT_CIPSENDEX();
// void ESP8266_AT_CIPSENDBUF();
// void ESP8266_AT_CIPBUFRESET();
// void ESP8266_AT_CIPBUFSTATUS();
// void ESP8266_AT_CIPCHECKSEQ();
// void ESP8266_AT_CIPCLOSE();
// void ESP8266_AT_CIFSR();
// void ESP8266_AT_CIPMUX();
// void ESP8266_AT_CIPSERVER();
// void ESP8266_AT_CIPSERVERMAXCONN();
// void ESP8266_AT_CIPMODE();
// void ESP8266_AT_SAVETRANSLINK();
// void ESP8266_AT_CIPSTO();
// void ESP8266_AT_PING();
// void ESP8266_AT_CIUPDATE();
// void ESP8266_AT_CIPDINFO();
// void ESP8266_IPD();
// void ESP8266_AT_CIPRECVMODE();
// void ESP8266_AT_CIPRECVDATA();
// void ESP8266_AT_CIPRECVLEN();
// void ESP8266_AT_CIPSNTPCFG();
// void ESP8266_AT_CIPSNTPTIME();
// void ESP8266_AT_CIPDNS_CUR();
// void ESP8266_AT_CIPDNS_DEF();

#endif