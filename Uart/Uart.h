#ifndef UART_H
#define UART_H

/* # open_serial
 * ## Fonction
 * Open the serial port file to be able to send or receive data.
 * ## Returns
 * {serial_port} : int => id of the file (use for read and write function)
 */
int open_serial();

/* # send_msg_uart
 * ## Fonction
 * Send message over Uart
 * ## Params
 * {msg}   : char *=> the string message to send
 * {size}  : int   => the size of the string
 * ## Return
 * 0 if all went right
 */
int send_msg_uart(char *msg, int size);

/* # recv_msg_uart
 * ## Fonction
 * receive message over uart
 * ## Params
 * {buffer_size}   : int   => size of the buffer for reading
 * ## Returns
 * 0 if all went right
 */
int recv_msg_uart(int buffer_size);

#endif /* UART_H */