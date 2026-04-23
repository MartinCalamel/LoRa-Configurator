# LoRa E220-900T22D configurator
Module to setup and configure E220-900T22D LoRa module

## installation
```
git clone https://github.com/MartinCalamel/LoRa-Configurator.git
cd LoRa-Configurator
make
./build/main
```
**⚠️make sure the device is connected on the UART0 (`/dev/ttyS0`)⚠️**

## Usage
To run the module : 
```
./build/main
```
You arrived in a cli menu where you can navigate by answering question, using arrow (up and down) and ENTER to validate.
```
      @@@@@@@@@@@@@@@@@@@@@@@@@@      ____       _     ____
   @@@@@@@@@@@@@@@@@@@@@@@@@@@@@     / ___|_ __ (_)   / ___| _ __   __ _  ___ ___
  @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@    | |   | '_ \| |____\___ \| '_ \ / _` |/ __/ _ \
 @@@      @@@@      @@@@            | |___| |_) | |_____|__) | |_) | (_| | (_|  __/
@@@       @@@      @@@@@             \____| .__/|_|    |____/| .__/ \__,_|\___\___|
         @@@@      @@@@@                  |_|                |_|
         @@@@      @@@@@
         @@@@      @@@@@                           Module : E220-900T22D
         @@@@      @@@@@                          Autor  : Martin CALAMEL
        @@@@@     @@@@@@
       @@@@@      @@@@@@
      @@@@@@      @@@@@@             Default Specs:
     @@@@@@@      @@@@@@      @@       [ ] |   BaudRate    |  9600           |
    @@@@@@@       @@@@@@@    @@@       [ ] |   Frequency   |  850.125 MHz    |
   @@@@@@@@       @@@@@@@@@@@@@        [ ] |   DataRate    |  62,5Kbps       |
   @@@@@@@         @@@@@@@@@@@         [ ] |     Power     |  13dBm          |
    @@@@@            @@@@@@@


Keep those Value ? [yes/no]:
```
You can choose the specs you want.  
Once you select all the spec you want, you can validate by entering anything but `no`.  
After that the programme send all the config to the LoRa module via the UART. 

**⚠️Make sure that if you change the BaudRate, you also change the BaudRate of your device⚠️**.  

You need now to setup the device's address.  
It must be a 4 digit hexadecimal address such as `1234` who will be understand as `0x1234`. 

## Doc
Here you can access to the module documentation [ebyte doc](https://www.cdebyte.com/pdf-down.aspx?id=1136)  
Here you can access to the library documentation [LoRa-Configurator](https://martincalamel.github.io/LoRa-Configurator/index.html)
