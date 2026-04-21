#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int open_serial(){
    /* # open_serial
    * ## Fonction
    *   Open the serial port file to be able to send or receive data.
    * ## Param
    *   none
    * ## Returns
    *   {serial_port} : int => id of the file (use for read and write function)
    * ## Inside
    *   open the /dev/ttyS0 file (usually the serial 0 file)
    */

    int serial_port = open("/dev/ttyS0", O_RDWR);
    // change the path if you want to change the Serial port
    return serial_port;
}


int send_msg_uart(unsigned char *msg, int size){
    /* # send_msg_uart
    * ## Fonction
    *   Send message over Uart
    * ## Params
    *   {msg}   : char *=> the string message to send
    *   {size}  : int   => the size of the string
    * ## Return
    *   0 if all went right
    * ## inside
    *   open the serial file,
    *   write the message,
    *   and then close the file.
    */
    // for(int i=0;i<size;i++){printf("%x",msg[i]);}  //debug only
    int serial_port = open_serial();
    write(serial_port, msg, size);
    close(serial_port);

    return 0;
}

int recv_msg_uart(int buffer_size){
    /* # recv_msg_uart
    * ## Fonction
    *   receive message over uart
    * ## Params
    *   {buffer_size}   : int   => size of the buffer for reading
    * ## Returns
    *   0 if all went right
    * ## inside
    *   open the serial file,
    *   prepare the buffer, 
    *   read the buffer with the right size,
    *   close the serial file,
    *   display the data.
    */
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