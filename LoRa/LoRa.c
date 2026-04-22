#include <stdio.h>
#include "gpio_utils.h"
#include <lgpio.h>

#define M0 = 17
#define M1 = 27

int send_char_from_int(void *msg, size_t size){
    unsigned char *p = (unsigned char *)msg;
    for (size_t i = size; i > 0; i--) {
        printf("i=%li\n0x%02X\n", i-1, p[i-1]);
    }
    return 0;
}

/**
 * Configure address of the device to {address}
 * @param address : unsigned short => the address you want for the device
 * @return msg : long int => the msg to send to the device to setup the address
 * @note 0xC0 : commande to set register
 * @note 0x00 : starting address of the register
 * @note 0x02 : length of the parameter
 */
long int config_address(unsigned short address) {
    long int msg = 0xC000020000;
    msg |= address;    
    return msg;
}

/**
 * Configure Uart DataRate to defaut (9600)
 * @param uart  : int => code for the correct baudrate 000 -> 111
 * @param air   : int => code for the correct data rate 000 -> 111
 * @return msg  : int => the msg to send to the device to setup DataRate
 * @note 0xC0 : commande to set register
 * @note 0x02 : starting address of the register
 * @note 0x01 : length of the parameter
 * @note 0x?? : data as follow :
 * @note    |---Uart rate [7,6,5] => 011 = 9600 (default)
 * @note    |---Serial parity bit [4,3] => 00 = 8N1 (default)
 * @note    |---Air DataRate [2,1,0] => 111 : 62.5k (Max)
 * @note For more details look doc p14-15
 */
int config_DataRate(int uart, int air){
    int data = 0;
    data += (uart<<5) + air;
    int msg = 0xC0020100;
    msg += data;
    return msg;
}

/**
 * Configure module frequency
 * @param freq  : int => frequency you want to setup (850 MHz - 930 MHz)
 * @return msg  : int => the msg to send to the device to setup frequency
 * @note 0xC0 : commande to set register
 * @note 0x04 : starting address of the register
 * @note 0x01 : length of the parameter
 * @note data as follow (0-80): freq - 850
 */
int setup_frequency(int freq){
    int msg = 0xC0040100;
    msg |= freq;
    return msg;
}

/**
 * Configure power
 * @param power : int => code for the correct baudrate 00 -> 11
 * @return msg  : int => the msg to send to the device to setup power
 * @note 0xC0 : commande to set register
 * @note 0x03 : starting address of the register
 * @note 0x01 : length of the parameter
 * @note power data
 */
int setup_power(int power){
    int msg = 0xC0030100; 
    msg |= power;
    return msg;
}

/**
 * set the fonction mode of the module
 * @param handle    : int => process with the gpio
 * @param mode      : int => mode you want to set (0->config, 1->transmit)
 * @return 0 if ok
 */
int set_mode(int handle, int mode){
    if (mode){
        up_gpio(handle, M0);
        up_gpio(handle, M1);
    } else {
        down_gpio(handle, M0);
        down_gpio(handle, M1);
    }
}




// int main(){
//     long int valeur = config_address(0x1234);
//     send_char_from_int(&valeur, sizeof(valeur));
//     printf("#######\n");

//     int valeur2 = config_DataRate(0b011, 0b111);
//     send_char_from_int(&valeur2, sizeof(valeur2));
//     printf("#######\n");

//     int valeur3 = setup_frequency(25);
//     send_char_from_int(&valeur3, sizeof(valeur3));
//     printf("#######\n");

//     int valeur4 = setup_power(2);
//     send_char_from_int(&valeur4, sizeof(valeur4));
//     return 0;
// }