/**
 * @file  Uart.c
 * @brief Implementation of uart_utils — simple uart send en recv.
 * @author Martin Calamel
 * @date 22/04/2026
 */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

/**
 * @brief Open the serial port file to be able to send or receive data.
 * 
 * @return {serial_port} : int => id of the file (use for read and write function)
 * @note open the /dev/ttyS0 file (usually the serial 0 file)
 */
int open_serial(){
    int serial_port = open("/dev/ttyS0", O_RDWR);
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
 * @param buffer_size   : int   => size of the buffer for reading
 * @note open the serial file,
 * @note prepare the buffer,
 * @note read the buffer with the right size,
 * @note close the serial file,
 * @note display the data.
 */
int recv_msg_uart(int buffer_size){
    int serial_port = open_serial();

    char read_buffer[buffer_size];
    int bytes_read = 0;

    bytes_read = read(serial_port, &read_buffer, buffer_size);

    close(serial_port);

    printf("UART msg recv...\n");
    printf("Bytes read : %i\n", bytes_read);
    printf("\nContent : \n");

    for(int i=0; i<bytes_read;i++){printf("%c",read_buffer[i]);}

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