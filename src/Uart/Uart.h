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
 *     // Read data over UART
 *     recv_msg_uart(64);
 * @endcode
 */

#ifndef UART_H
#define UART_H

/**
 * @brief Open the serial port file to be able to send or receive data.
 * 
 * @return {serial_port} : int => id of the file (use for read and write function)
 * @note open the /dev/ttyS0 file (usually the serial 0 file)
 */
int open_serial();

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
 * @param buffer_size   : int   => size of the buffer for reading
 * @note open the serial file,
 * @note prepare the buffer,
 * @note read the buffer with the right size,
 * @note close the serial file,
 * @note display the data.
 */
int recv_msg_uart(int buffer_size);

#endif /* UART_H */