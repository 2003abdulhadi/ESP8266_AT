/**
 * ESP8266_AT.h by Abdul Hadi 2023
 * Driver for ESP8266 wifi module using AT commands
 * All functions are implemented per v3.0.5 of AT commands found at
 * https://www.espressif.com/sites/default/files/documentation/4a-esp8266_at_instruction_set_en.pdf
 * All functions have 2 params minimum: uart, and timeout. uart is the
 * pointer to the uart used to communicate with the ESP8266. Timeout
 * configures the timeout duration of the transmitted request.
 * Returns documentation defines the response the ESP8266 will give
 * based on the command sent
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
/*
 * @brief Configures a GPIO to Wake ESP8266 up from Light-sleep Mode
 * Since the system needs some time to wake up from light sleep, it is
 * suggested that wait at least 5ms before sending next AT command. The
 * value of <trigger_GPIO> and <awake_GPIO> in the command should not
 * be the same. After being woken up by <trigger_GPIO> from Light-sleep,
 * when the ESP8266 attempts tosleep again, it will check the status of
 * the <trigger_GPIO>. if it is still in the wakeup status, the EP8266
 * will enter Modem-sleep mode instead. if it is NOT in the wakeup
 * status, the ESP8266 will enter Light-sleep mode
 * @param <enable>. true:  ESP8266 can be woken up from light-sleep by
 * GPIO. false: ESP8266 can NOT be woken up from light-sleep by GPIO
 * @param <trigger_gpio>. trigger_gpio :=[0,15]. enable sets the GPIO to
 * wake the ESP8266
 * @param <trigger_level>. true: ESP8266 will wake on high. false: ESP8266
 * will wake on low
 * @param <awake_GPIO>. OPTIONAL PARAM. awake_gpio := [0,15]. used to set
 * a GPIO as a flag of ESP8266’s being awoken form Light-sleep
 * @param <awake_level> OPTIONAL PARAM. true: GPIO is set to high after
 * wake. false: GPIO is set to low after wake
 * @returns OK
 * @note Optional params are nullable
 */
void ESP8266_AT_WAKEUPGPIO(UART_HandleTypeDef *uart, bool enable,
                           uint8_t trigger_gpio, bool trigger_level,
                           uint8_t awake_GPIO, bool awake_level,
                           uint8_t timeout);
/*
 * @brief Sets the Maximum Value of RF TX Power. This command sets the
 * maximum value of ESP8266 RF TX power; it is not precise. The actual
 * value could be smaller than the set value.
 * @param <TX Power>. Tx power :=[0,82]. Tx power is the maximum value
 * of RF TX power.
 * @returns OK
 */
void ESP8266_AT_RFPOWER(UART_HandleTypeDef *uart, uint8_t Tx_power, uint8_t timeout);

/*
 * @brief Query RF TX Power According to VDD33. Checks the value of ESP8266
 * VDD33. The command should only be used when TOUT pin has to be
 * suspended, or else the returned value would be invalid.
 * @returns +RFVDD:<VDD33>, OK
 */
void ESP8266_AT_RFVDD_QUERY(UART_HandleTypeDef *uart, uint8_t timeout);

/*
 * @brief Set RF TX Power According to VDD33. Sets the RF TX Power
 * according to <VDD33>.
 * @param <VD33>: VD33 := [1900,3300]. power voltage of ESP8266 VDD33
 * @returns OK
 */
void ESP8266_AT_RFVDD_SET(UART_HandleTypeDef *uart, uint8_t VD33, uint8_t timeout);

/*
 * @brief Execute RF TX Power According to VDD33. Automatically sets
 * the RF TX Power. TOUT pin has to be suspended in order to measure
 * VDD33.
 * @returns OK
 */
void ESP8266_AT_RFVDD_EXECUTRE(UART_HandleTypeDef *uart, uint8_t timeout);

/*
 * @brief Checks the Remaining Space of RAM
 * @returns +SYSRAM:<remaining RAM size>, OK
 */
void ESP8266_AT_SYSRAM(UART_HandleTypeDef *uart, uint8_t timeout);

/*
 * @brief Checks the Value of ADC.
 * @returns +SYSADC:<ADC>, OK
 */
void ESP8266_AT_SYSADC(UART_HandleTypeDef *uart, uint8_t timeout);

/*
 * @brief Configures IO Working Mode. Please refer to ESP8266 Pin List
 * for uses of AT+SYSIO-related commands at
 * https://www.espressif.com/en/support/documents/technical-documents?keys=ESP8266+Pin+List
 * @param <pin>. number of an IO pin
 * @param <mode>. the working mode of the IO pin
 * @param <pull-up>. true: enable the pull-up of the IO pin.
 * false: disable the pull up
 * @returns OK
 */
void ESP8266_AT_SYSIOSETCFG(UART_HandleTypeDef *uart, uint8_t pin,
                            uint8_t mode, bool pull_up, uint8_t timeout);

/*
 * @brief Checks the Working Modes of IO Pins. Please refer to ESP8266
 * Pin List for uses of AT+SYSIO-related commands at
 * https://www.espressif.com/en/support/documents/technical-documents?keys=ESP8266+Pin+List
 * @param <pin>. pin number
 * @returns +SYSIOGETCFG:<pin>,<mode>,<pull-up>, OK
 */
void ESP8266_AT_SYSIOGETCFG(UART_HandleTypeDef *uart, uint8_t pin, uint8_t timeout);

/*
 * @brief Configures the Direction of a GPIO. Please refer to ESP8266
 * Pin List for uses of AT+SYSIO-related commands at
 * https://www.espressif.com/en/support/documents/technical-documents?keys=ESP8266+Pin+List
 * @param <pin>: GPIO pin number
 * @param <dir>: true: set GPIO to output. false: set GPIO to input
 * @returns on success: OK. on failure: NOT	GPIO MODE! ERROR
 */
void ESP8266_AT_SYSGPIODIR(UART_HandleTypeDef *uart, uint8_t pin,
                           bool dir, uint8_t timeout);
/*
 * @brief Configures the Direction of a GPIO. Please refer to ESP8266
 * Pin List for uses of AT+SYSIO-related commands at
 * https://www.espressif.com/en/support/documents/technical-documents?keys=ESP8266+Pin+List
 * @param <pin>: GPIO pin number
 * @param <level>: true: set high. false: set low
 * @returns on success: OK. on failure: NOT	GPIO MODE! ERROR
 */
void ESP8266_AT_SYSGPIOWRITE(UART_HandleTypeDef *uart, uint8_t pin,
                             bool level, uint8_t timeout);

/*
 * @brief Reads the GPIO Input Level. Please refer to ESP8266 Pin List
 * for uses of AT+SYSIO-related commands at
 * https://www.espressif.com/en/support/documents/technical-documents?keys=ESP8266+Pin+List
 * @param <pin>: GPIO pin number
 * @returns on success: +SYSGPIOREAD:<pin>,<dir>,<level>, OK.
 * on failure: NOT GPIO MODE! ERROR
 */
void ESP8266_AT_SYSGPIOREAD(UART_HandleTypeDef *uart, uint8_t pin, uint8_t timeout);

/*
 * @brief Set Current System Messages. The configuration changes will
 * NOT be saved in the flash.
 * @param set_quit_message. true: when quitting WiFi-UART passthrough
 * transmission, it will prompt themessage +QUITT. false: there is no
 * message when quitting WiFi-UART passthrough transmission
 * @param set_establish_message. true: when establishing a network
 * connection, it will prompt the message +LINK_CONN:<status_type>,
 * <link_id>,"UDP/TCP/SSL",<c/s>,<remote_ip>,<remote_port>,<local_port>.
 * <status_type> : 0 - the connection is established successfully;
 * 1 -fail to establish the connection
 * <c/s> : 0 - the ESP works as a client; 1 - the ESP works as a server
 * false: when a network connection is established, it will prompt the
 * message <Link_ID>,CONNECT.
 * @returns OK
 */
void ESP8266_AT_SYSMSG_CUR(UART_HandleTypeDef *uart,
                           bool set_quit_message,
                           bool set_establish_message, uint8_t timeout);

/*
 * @brief Set Default System Messages. The configuration changes will
 * be saved in the flash user parameter area.
 * @param set_quit_message. true: when quitting WiFi-UART passthrough
 * transmission, it will prompt themessage +QUITT. false: there is no
 * message when quitting WiFi-UART passthrough transmission
 * @param set_establish_message. true: when establishing a network
 * connection, it will prompt the message +LINK_CONN:<status_type>,
 * <link_id>,"UDP/TCP/SSL",<c/s>,<remote_ip>,<remote_port>,<local_port>.
 * <status_type> : 0 - the connection is established successfully;
 * 1 -fail to establish the connection
 * <c/s> : 0 - the ESP works as a client; 1 - the ESP works as a server
 * false: when a network connection is established, it will prompt the
 * message <Link_ID>,CONNECT.
 * @returns OK
 */
void ESP8266_AT_SYSMSG_DEF(UART_HandleTypeDef *uart,
                           bool set_quit_message,
                           bool set_establish_message, uint8_t timeout);

// Wi-Fi AT Commands

// void ESP8266_AT_CWMODE_CUR(UART_HandleTypeDef *uart, uint8_t timeout);
// void ESP8266_AT_CWMODE_DEF(UART_HandleTypeDef *uart, uint8_t timeout);
// void ESP8266_AT_CWJAP_CUR(UART_HandleTypeDef *uart, uint8_t timeout);
// void ESP8266_AT_CWJAP_DEF(UART_HandleTypeDef *uart, uint8_t timeout);
// void ESP8266_AT_CWLAPOPT(UART_HandleTypeDef *uart, uint8_t timeout);
// void ESP8266_AT_CWLAP(UART_HandleTypeDef *uart, uint8_t timeout);
// void ESP8266_AT_CWQAP(UART_HandleTypeDef *uart, uint8_t timeout);
// void ESP8266_AT_CWSAP_CUR(UART_HandleTypeDef *uart, uint8_t timeout);
// void ESP8266_AT_CWSAP_DEF(UART_HandleTypeDef *uart, uint8_t timeout);
// void ESP8266_AT_CWLIF(UART_HandleTypeDef *uart, uint8_t timeout);
// void ESP8266_AT_CWDHCP_CUR(UART_HandleTypeDef *uart, uint8_t timeout);
// void ESP8266_AT_CWDHCP_DEF(UART_HandleTypeDef *uart, uint8_t timeout);
// void ESP8266_AT_CWDHCPS_CUR(UART_HandleTypeDef *uart, uint8_t timeout);
// void ESP8266_AT_CWDHCPS_DEF(UART_HandleTypeDef *uart, uint8_t timeout);
// void ESP8266_AT_CWAUTOCONN(UART_HandleTypeDef *uart, uint8_t timeout);
// void ESP8266_AT_CIPSTAMAC_CUR(UART_HandleTypeDef *uart, uint8_t timeout);
// void ESP8266_AT_CIPSTAMAC_DEF(UART_HandleTypeDef *uart, uint8_t timeout);
// void ESP8266_AT_CIPAPMAC_CUR(UART_HandleTypeDef *uart, uint8_t timeout);
// void ESP8266_AT_CIPAPMAC_DEF(UART_HandleTypeDef *uart, uint8_t timeout);
// void ESP8266_AT_CIPSTA_CUR(UART_HandleTypeDef *uart, uint8_t timeout);
// void ESP8266_AT_CIPSTA_DEF(UART_HandleTypeDef *uart, uint8_t timeout);
// void ESP8266_AT_CIPAP_CUR(UART_HandleTypeDef *uart, uint8_t timeout);
// void ESP8266_AT_CIPAP_DEF(UART_HandleTypeDef *uart, uint8_t timeout);
// void ESP8266_AT_CWSTARTSMART(UART_HandleTypeDef *uart, uint8_t timeout);
// void ESP8266_AT_CWSTOPSMART(UART_HandleTypeDef *uart, uint8_t timeout);
// void ESP8266_AT_CWSTARTDISCOVER(UART_HandleTypeDef *uart, uint8_t timeout);
// void ESP8266_AT_CWSTOPDISCOVER(UART_HandleTypeDef *uart, uint8_t timeout);
// void ESP8266_AT_WPS(UART_HandleTypeDef *uart, uint8_t timeout);
// void ESP8266_AT_MDNS(UART_HandleTypeDef *uart, uint8_t timeout);
// void ESP8266_AT_CWHOSTNAME(UART_HandleTypeDef *uart, uint8_t timeout);
// void ESP8266_AT_CWCOUNTRY_CUR(UART_HandleTypeDef *uart, uint8_t timeout);
// void ESP8266_AT_CWCOUNTRY_DEF(UART_HandleTypeDef *uart, uint8_t timeout);

// TCP/IP-Related AT Commands

// void ESP8266_AT_CIPSTATUS(UART_HandleTypeDef *uart, uint8_t timeout);
// void ESP8266_AT_CIPDOMAIN(UART_HandleTypeDef *uart, uint8_t timeout);
// void ESP8266_AT_CIPSTART(UART_HandleTypeDef *uart, uint8_t timeout);
// void ESP8266_AT_CIPSSLSIZE(UART_HandleTypeDef *uart, uint8_t timeout);
// void ESP8266_AT_CIPSSLCONF(UART_HandleTypeDef *uart, uint8_t timeout);
// void ESP8266_AT_CIPSEND(UART_HandleTypeDef *uart, uint8_t timeout);
// void ESP8266_AT_CIPSENDEX(UART_HandleTypeDef *uart, uint8_t timeout);
// void ESP8266_AT_CIPSENDBUF(UART_HandleTypeDef *uart, uint8_t timeout);
// void ESP8266_AT_CIPBUFRESET(UART_HandleTypeDef *uart, uint8_t timeout);
// void ESP8266_AT_CIPBUFSTATUS(UART_HandleTypeDef *uart, uint8_t timeout);
// void ESP8266_AT_CIPCHECKSEQ(UART_HandleTypeDef *uart, uint8_t timeout);
// void ESP8266_AT_CIPCLOSE(UART_HandleTypeDef *uart, uint8_t timeout);
// void ESP8266_AT_CIFSR(UART_HandleTypeDef *uart, uint8_t timeout);
// void ESP8266_AT_CIPMUX(UART_HandleTypeDef *uart, uint8_t timeout);
// void ESP8266_AT_CIPSERVER(UART_HandleTypeDef *uart, uint8_t timeout);
// void ESP8266_AT_CIPSERVERMAXCONN(UART_HandleTypeDef *uart, uint8_t timeout);
// void ESP8266_AT_CIPMODE(UART_HandleTypeDef *uart, uint8_t timeout);
// void ESP8266_AT_SAVETRANSLINK(UART_HandleTypeDef *uart, uint8_t timeout);
// void ESP8266_AT_CIPSTO(UART_HandleTypeDef *uart, uint8_t timeout);
// void ESP8266_AT_PING(UART_HandleTypeDef *uart, uint8_t timeout);
// void ESP8266_AT_CIUPDATE(UART_HandleTypeDef *uart, uint8_t timeout);
// void ESP8266_AT_CIPDINFO(UART_HandleTypeDef *uart, uint8_t timeout);
// void ESP8266_IPD(UART_HandleTypeDef *uart, uint8_t timeout);
// void ESP8266_AT_CIPRECVMODE(UART_HandleTypeDef *uart, uint8_t timeout);
// void ESP8266_AT_CIPRECVDATA(UART_HandleTypeDef *uart, uint8_t timeout);
// void ESP8266_AT_CIPRECVLEN(UART_HandleTypeDef *uart, uint8_t timeout);
// void ESP8266_AT_CIPSNTPCFG(UART_HandleTypeDef *uart, uint8_t timeout);
// void ESP8266_AT_CIPSNTPTIME(UART_HandleTypeDef *uart, uint8_t timeout);
// void ESP8266_AT_CIPDNS_CUR(UART_HandleTypeDef *uart, uint8_t timeout);
// void ESP8266_AT_CIPDNS_DEF(UART_HandleTypeDef *uart, uint8_t timeout);

#endif