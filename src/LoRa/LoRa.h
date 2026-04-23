/**
 * @file  LoRa.h
 * @brief Simple LoRa Library for the E220-900T22D LoRa module
 * @code
 *      #include <stdio.h>
 *      #include "src/LoRa/LoRa.h"
 * 
 * @endcode
 */

#ifndef LORA_H
#define LORA_H

#include <stddef.h>

/**
 * @brief List of mode for the LoRa module
 */
typedef enum LoRa_mode{
    LORA_MODE_CONFIG = 0,     /**< Configuration mode */
    LORA_MODE_TRANSMIT        /**< Transmit data mode */
} LoRa_mode_t;

/**
 * @brief List of the possibilities for baudrate
 * 
 */
typedef enum LoRa_baudrate{
    LORA_BAUDRATE_1200 = 0,     /**< value for 1200bps */
    LORA_BAUDRATE_B2400,        /**< value for 2400bps */
    LORA_BAUDRATE_B4800,        /**< value for 4800bps */
    LORA_BAUDRATE_B9600,        /**< value for 9600bps */
    LORA_BAUDRATE_B19200,       /**< value for 19200bps */
    LORA_BAUDRATE_B38400,       /**< value for 38400bps */
    LORA_BAUDRATE_B57600,       /**< value for 57600bps */
    LORA_BAUDRATE_B115200      /**< value for 115200bps */
} LoRa_baudrate_t;

/**
 * @brief List of the possibilities for datarate
 * 
 */
typedef enum LoRa_datarate{
    LORA_DATARATE_24 = 2,   /**< value for 2,4Kbps*/
    LORA_DATARATE_48,       /**< value for 4,8Kbps*/
    LORA_DATARATE_96,       /**< value for 9,6Kbps*/
    LORA_DATARATE_192,      /**< value for 19,2Kbps*/
    LORA_DATARATE_384,      /**< value for 38,4Kbps*/
    LORA_DATARATE_625      /**< value for 62,5Kbps*/
} LoRa_datarate_t;

/**
 * @brief list of possibilities for power
 * 
 */
typedef enum LoRa_power{
    LORA_POWER_22 = 0,  /**< value for 22dBm */
    LORA_POWER_17,      /**< value for 17dBm */
    LORA_POWER_13,      /**< value for 13dBm */
    LORA_POWER_10       /**< value for 10dBm */
}LoRa_power_t;

/**
 * @brief Configure the LoRa module
 * 
 * @param handle    : int               => process with the gpio
 * @param address   : unsigned short    => Address of the module 
 * @param baudrate  : LoRa_baudrate_t   => Desired BaudRate
 * @param datarate  : LoRa_datarate_t   => Desired DataRate
 * @param freq      : int               => frequency of the module [0-80]
 * @return int 0 if all right
 */
void config_LoRa(int handle, unsigned short address, LoRa_baudrate_t baudrate, LoRa_datarate_t datarate, int freq, LoRa_power_t power);

/**
 * @brief Sends a message to a specific LoRa module using Fixed Transmission mode.
 * * According to Section 5.1 of the manual, in fixed transmission mode, the first 
 * three bytes of the UART data are used as the target address and channel.
 * @param handle    process with the GPIO
 * @param address   Target module address (ADDH and ADDL), from 0 to 65535.
 * @param channel   Target frequency channel (0 to 83).
 * @param msg       Pointer to the data payload to be sent.
 * @param msg_size  Size of the payload (Max 200 bytes per packet by default).
 * @return int      0 on success.
 */
int send_msg_LoRa(int handle, uint16_t address, uint8_t channel, char *msg, uint8_t msg_size);

#endif /* LORA_H */