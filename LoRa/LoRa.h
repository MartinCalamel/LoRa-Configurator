/**
 * @file  LoRa.c
 * @brief Implementation of LoRa — simple LoRa configurator.
 * @author Martin Calamel
 * @date 22/04/2026
 */

#ifndef LORA_H
#define LORA_H

#include <stddef.h>

/* # send_char_from_int
 * ## Fonction
 * Iterates through the bytes of a generic message and prints them in hex.
 * ## Param
 * {msg}  : void * => pointer to the data to print
 * {size} : size_t => size of the data in bytes
 * ## Return
 * 0 if all went right
 */
int send_char_from_int(void *msg, size_t size);

/**
 * @brief Configure address of the device to {address}
 * @param address : unsigned short => the address you want for the device
 * @return msg : long int => the msg to send to the device to setup the address
 * @note 0xC0 : commande to set register
 * @note 0x00 : starting address of the register
 * @note 0x02 : length of the parameter
 */
long int config_address(unsigned short address);

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
int config_DataRate();

/**
 * @brief Configure module frequency
 * @param freq  : int => frequency you want to setup (850 MHz - 930 MHz)
 * @return msg  : int => the msg to send to the device to setup frequency
 * @note 0xC0 : commande to set register
 * @note 0x04 : starting address of the register
 * @note 0x01 : length of the parameter
 * @note data as follow (0-80): freq - 850
 */
int setup_frequency(int freq);

/**
 * @brief Configure power
 * @param power : int => code for the correct baudrate 00 -> 11
 * @return msg  : int => the msg to send to the device to setup power
 * @note 0xC0 : commande to set register
 * @note 0x03 : starting address of the register
 * @note 0x01 : length of the parameter
 * @note power data
 */
int setup_power();

/**
 * set the fonction mode of the module
 * @param handle    : int => process with the gpio
 * @param mode      : int => mode you want to set (0->config, 1->transmit)
 * @return 0 if ok
 */
int set_mode(int handle, int mode);

#endif /* LORA_H */