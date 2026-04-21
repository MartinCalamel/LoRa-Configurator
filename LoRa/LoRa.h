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

/* # config_address
 * ## Fonction
 * Configure address of the device to {address}
 * ## Param
 * {address} : unsigned short => the address you want for the device
 * ## Return
 * {msg} : long int => the msg to send to the device to setup the address
 */
long int config_address(unsigned short address);

/* # config_DataRate
 * ## Fonction
 * Configure Uart DataRate to defaut (9600)
 * ## Return
 * {msg} : int => the msg to send to the device to setup DataRate
 */
int config_DataRate();

/* # setup_frequency
 * ## Fonction
 * Configure module frequency (850 MHz - 930 MHz)
 * ## Param
 * {freq} : int => frequency you want to setup
 * ## Return
 * {msg} : int => the msg to send to the device to setup frequency
 */
int setup_frequency(int freq);

/* # setup_power
 * ## Fonction
 * Configure power to 13 dBm
 * ## Return
 * {msg} : int => the msg to send to the device to setup power
 */
int setup_power();

#endif /* LORA_H */