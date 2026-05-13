/**
 * @file Uart.h
 * @brief Simple UART library for Raspberry Pi 4 board
 * 
 * You can Write en Read over UART
 * 
 * Typical usage :
 * @code 
 *     #include <stdio.h>
 *     #include "Uart.h"
 * 
 *     // write data over UART
 *     char *msg = "hello";
 *     send_msg_uart(msg, sizeof(msg));
 *     
 *     // Read data over UART with a buffer of 64 Bytes
 *     char *buffer[64];
 *     recv_msg_uart(buffer, 64);
 * @endcode
 */

#ifndef UART_H
#define UART_H

/**
 * @brief List of status for the UART API.
 * Those value can be used to debug.
 */
typedef enum{
    UART_OK = 0,    /**< All went right */
    UART_FAILED     /**< something is wrong */
} uart_status;

/**
 * @brief Send message over Uart
 * @param msg   : char *=> the string message to send
 * @param size  : int   => the size of the string
 * @return 0 if all went right
 * @note open the serial file,
 * @note write the message,
 * @note and then close the file.
 */
int send_msg_uart(unsigned char *msg, int size);

/**
 * @brief receive message over uart
 * @param buffer        : char *=> data buffer for UART reading
 * @param buffer_size   : int   => size of the buffer for reading
 * @note open the serial file,
 * @note prepare the buffer,
 * @note read the buffer with the right size,
 * @note close the serial file,
 * @note display the data.
 */
int recv_msg_uart(char *buffer, int buffer_size);

#endif /* UART_H */