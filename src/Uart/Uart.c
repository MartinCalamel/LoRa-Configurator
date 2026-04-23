/**
 * @file  Uart.c
 * @brief Implementation of uart_utils — simple uart send en recv.
 * @author Martin Calamel
 * @date 22/04/2026
 */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#include "src/Uart/Uart.h"

static char *UART_PATH = "/dev/ttyS0";

/**
 * @brief Open the serial port file to be able to send or receive data.
 * 
 * @return serial_port : int => id of the file (use for read and write function)
 * @note open the /dev/ttyS0 file (usually the serial 0 file)
 */
static int open_serial(){
    int serial_port = open(UART_PATH, O_RDWR);
    // change the path if you want to change the Serial port
    return serial_port;
}

/**
 * @brief Send message over Uart
 * @param msg   : char *=> the string message to send
 * @param size  : int   => the size of the string
 * @return 0 if all went right
 * @note open the serial file,
 * @note write the message,
 * @note and then close the file.
 */
int send_msg_uart(unsigned char *msg, int size){
    // for(int i=0;i<size;i++){printf("%x",msg[i]);}  //debug only
    int serial_port = open_serial();
    write(serial_port, msg, size);
    close(serial_port);

    return 0;
}

/**
 * @brief receive message over uart
 * @param buffer        : char *=> data buffer for UART reading
 * @param buffer_size   : int   => size of the buffer for reading
 * @note open the serial file,
 * @note put data on buffer with the right size,
 * @note close the serial file,
 */
int recv_msg_uart(char *buffer, int buffer_size){
    int serial_port = open_serial();

    read(serial_port, &buffer, buffer_size);
    close(serial_port);

    return 0;
}



// int main(){
//     printf("|-------------------|\n");
//     printf("|     UART test     |\n");
//     printf("|-------------------|\n\n");

//     pid_t p;

//     p = fork();
//     if (p<0){
//         printf("[ERROR] fork fail\n");// process error
//     } else if (p == 0){
//         // parent process for reading UART
//         printf("Waiting for data\n");
//         sleep(5);
//         printf("hey");
//         recv_msg_uart(64);
//     }else{
//         //chile process for writing UART
//         printf("Sending \"hello\" in 5s\n");
//         char *msg = "hello";
        
//         send_msg_uart(msg, 5);
//     }
//     return 0;
// }