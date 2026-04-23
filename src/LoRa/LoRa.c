/**
 * @file  LoRa.c
 * @brief Simple LoRa Library for the E220-900T22D LoRa module
 * @author Martin Calamel
 * @date 22/04/2026
 */

#include <stdio.h>
#include <lgpio.h>
#include <stdint.h>
#include <string.h>

#include "src/gpio/gpio_utils.h"
#include "src/Uart/Uart.h"
#include "src/LoRa/LoRa.h"

static int M0 = 17;
static int M1 = 27;

/**
 * @brief Configure address of the device to {address}
 * @param address : unsigned short => the address you want for the device
 * @return msg : long int => the msg to send to the device to setup the address
 * @note 0xC0 : commande to set register
 * @note 0x00 : starting address of the register
 * @note 0x02 : length of the parameter
 */
static long int set_address(unsigned short address) {
    long int msg = 0xC000020000;
    msg |= address;    
    return msg;
}

/**
 * @brief Configure Uart DataRate to defaut (9600)
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
static int set_DataRate(LoRa_baudrate_t uart, LoRa_datarate_t air){
    int data = 0;
    data += (uart<<5) + air;
    int msg = 0xC0020100;
    msg += data;
    return msg;
}

/**
 * @brief Configure module frequency
 * @param freq  : int => frequency you want to setup (850 MHz - 930 MHz)
 * @return msg  : int => the msg to send to the device to setup frequency
 * @note 0xC0 : commande to set register
 * @note 0x04 : starting address of the register
 * @note 0x01 : length of the parameter
 * @note data as follow (0-80): freq - 850
 */
static int set_frequency(int freq){
    int msg = 0xC0040100;
    msg |= freq;
    return msg;
}

/**
 * @brief Configure power
 * @param power : int => code for the correct baudrate 00 -> 11
 * @return msg  : int => the msg to send to the device to setup power
 * @note 0xC0 : commande to set register
 * @note 0x03 : starting address of the register
 * @note 0x01 : length of the parameter
 * @note power data
 */
static int set_power(LoRa_power_t power){
    int msg = 0xC0030100; 
    msg |= power;
    return msg;
}

/**
 * @brief set the fonction mode of the module
 * @param handle    : int => process with the gpio
 * @param mode      : int => mode you want to set (0->config, 1->transmit)
 * @return 0 if ok
 */
static int set_mode(int handle, LoRa_mode_t mode){
    if (mode){
        up_gpio(handle, M0);
        up_gpio(handle, M1);
    } else {
        down_gpio(handle, M0);
        down_gpio(handle, M1);
    }
}


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
int config_LoRa(int handle, unsigned short address, LoRa_baudrate_t baudrate, LoRa_datarate_t datarate, int freq, LoRa_power_t){
    set_mode(handle, CONFIG);

    long int set_address_cmd = set_address(address);
    send_msg_uart((char *)&set_address_cmd, sizeof(set_address_cmd));

    int set_datarate_cmd = set_DataRate(baudrate, datarate);
    send_msg_uart((char *)&set_datarate_cmd, sizeof(set_datarate_cmd));

    int set_frequency_cmd = set_frequency(freq);
    send_msg_uart((char *)&set_frequency_cmd, sizeof(set_frequency_cmd));

    int set_power_cmd = set_power(power);
    send_msg_uart((char *)&set_power_cmd, sizeof(set_power_cmd));
}


/**
 * @brief Sends a message to a specific LoRa module using Fixed Transmission mode.
 * * According to Section 5.1 of the manual, in fixed transmission mode, the first 
 * three bytes of the UART data are used as the target address and channel.
 * @param address   Target module address (ADDH and ADDL), from 0 to 65535.
 * @param channel   Target frequency channel (0 to 80).
 * @param msg       Pointer to the data payload to be sent.
 * @param msg_size  Size of the payload (Max 200 bytes per packet by default).
 * @return int      0 on success.
 */
int send_msg_LoRa(uint16_t address, uint8_t channel, char *msg, uint8_t msg_size) {
    set_mode(LORA_MODE_TRANSMIT);
    
    uint8_t total_size = 3 + msg_size;
    uint8_t data_buffer[total_size];

    data_buffer[0] = (uint8_t)(address >> 8);   // ADDH
    data_buffer[1] = (uint8_t)(address & 0xFF);  // ADDL
    
    data_buffer[2] = channel;

    memcpy(&data_buffer[3], msg, msg_size);

    send_msg_uart(data_buffer, total_size);
    
    return 0;
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