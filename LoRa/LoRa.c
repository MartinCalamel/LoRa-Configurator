#include <stdio.h>

int send_char_from_int(void *msg, size_t size){
    unsigned char *p = (unsigned char *)msg;
    for (size_t i = size; i > 0; i--) {
        printf("i=%li\n0x%02X\n", i-1, p[i-1]);
    }
    return 0;
}

long int config_address(unsigned short address) {
    /* # config_address
    * ## Fonction
    *   Configure address of the device to {address}
    * ## Param
    *   {address} : unsigned short => the address you want for the device
    * ## Return
    *   {msg} : long int => the msg to send to the device to setup the address
    * ## inside
    * 0xC0 : commande to set register
    * 0x00 : starting address of the register
    * 0x02 : length of the parameter
    */ 
    long int msg = 0xC000020000;
    msg |= address;    
    return msg;
}
int config_DataRate(int uart, int air){
    /* # config_DataRate
    * ## Fonction
    *   Configure Uart DataRate to defaut (9600)
    * ## Param
    *   None
    * ## Return
    *   {msg} : int => the msg to send to the device to setup DataRate
    * ## inside  
    * 0xC0 : commande to set register
    * 0x02 : starting address of the register
    * 0x01 : length of the parameter
    * 0x67 : data as follow :
    *       // Uart rate [7,6,5] => 011 : 9600 (default)
    *       // Serial parity bit [4,3] => 00 : 8N1 (default)
    *       // Air DataRate [2,1,0] => 111 : 62.5k (Max)
    *       // bits => 0110 0111 => 0x67
    *       // for more details look doc p14-15
    */
    int data = 0;
    data += (uart<<5) + air;
    int msg = 0xC0020100;
    msg += data;
    return msg;
}

int setup_frequency(int freq){
    /* # setup_frequency
    * ## Fonction
    *   Configure module frequency
    * ## Param
    *   {freq} : int => frequency you want to setup (850 MHz - 930 MHz)
    * ## Return
    *   {msg} : int => the msg to send to the device to setup frequency
    * ## inside  
    * 0xC0 : commande to set register
    * 0x04 : starting address of the register
    * 0x01 : length of the parameter
    * data as follow (0-80): freq - 850
    */
    int msg = 0xC0040100;
    msg |= freq;
    return msg;
}

int setup_power(int power){
     /* # setup_power
    * ## Fonction
    *   Configure power to 13 dBm
    * ## Param
    *   None
    * ## Return
    *   {msg} : int => the msg to send to the device to setup power
    * ## inside  
    * 0xC0 : commande to set register
    * 0x03 : starting address of the register
    * 0x01 : length of the parameter
    * 0x02 : For 13 dBm power
    */
    int msg = 0xC0030100; 
    msg |= power;
    return msg;
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