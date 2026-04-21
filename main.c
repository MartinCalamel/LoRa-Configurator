#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

#include "Uart/Uart.h"
#include "LoRa/LoRa.h"

char opts_freq[81][20]; // Global

void init_frequences() {
    for (int i = 0; i < 80; i++) {
        sprintf(opts_freq[i], "%.3f MHz", 850.125 + i);
    }
}

const char *opts_baud[]  = {"1200 ", "2400 ", "4800 ", "9600  ", "19200 ", "38400 ", "57600 ", "115200"};
const char *opts_data[]  = {"2,4Kbps", "2,4Kbps", "2,4Kbps", "4,8Kbps", "9,6Kbps", "19,2Kbps", "38,4Kbps", "62,5Kbps"};
const char *opts_power[] = {"22dBm", "17dBm", "13dBm", "10dBm"};

int tailles[] = {8, 80, 8, 4};

short b = 3;
short f = 0;
short d = 7;
short p = 2;

int getch_linux() {
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}


void afficher_interface(int param_selectionne, int idx_baud, int idx_freq, int idx_data, int idx_pwr, int color) {
    // 1. Préparation des valeurs avec inversion de couleur si sélectionnées
    char v_baud[60], v_freq[60], v_data[60], v_pwr[60];

    // On utilise sprintf pour formater chaque valeur avec les codes ANSI
    sprintf(v_baud, "%s %s \033[0m", (param_selectionne == 1 && color) ? "\033[7m" : "", opts_baud[idx_baud]);
    sprintf(v_freq, "%s %s \033[0m", (param_selectionne == 2 && color) ? "\033[7m" : "", opts_freq[idx_freq]);
    sprintf(v_data, "%s %s \033[0m", (param_selectionne == 3 && color) ? "\033[7m" : "", opts_data[idx_data]);
    sprintf(v_pwr,  "%s %s \033[0m", (param_selectionne == 4 && color) ? "\033[7m" : "", opts_power[idx_pwr]);

    // 2. Le logo (modifié en tableau de char 2D pour pouvoir placer le 'X')
    char image[17][120] = {
        "      @@@@@@@@@@@@@@@@@@@@@@@@@@      ____       _     ____                 ",
        "   @@@@@@@@@@@@@@@@@@@@@@@@@@@@@     / ___|_ __ (_)   / ___| _ __   __ _  ___ ___ ",
        "  @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@    | |   | '_ \\| |____\\___ \\| '_ \\ / _` |/ __/ _ \\",
        " @@@      @@@@      @@@@            | |___| |_) | |_____|__) | |_) | (_| | (_|  __/",
        "@@@       @@@      @@@@@             \\____| .__/|_|    |____/| .__/ \\__,_|\\___\\___|",
        "         @@@@      @@@@@                  |_|                |_|                   ",
        "         @@@@      @@@@@        ",
        "         @@@@      @@@@@                           Module : E220-900T22D",
        "         @@@@      @@@@@                          Autor  : Martin CALAMEL",
        "        @@@@@     @@@@@@        ",
        "       @@@@@      @@@@@@        ",
        "      @@@@@@      @@@@@@             Default Specs: ",
        "     @@@@@@@      @@@@@@      @@       [ ] |   BaudRate    | ", // Ligne 12
        "    @@@@@@@       @@@@@@@    @@@       [ ] |   Frequency   | ", // Ligne 13
        "   @@@@@@@@       @@@@@@@@@@@@@        [ ] |   DataRate    | ", // Ligne 14
        "   @@@@@@@         @@@@@@@@@@@         [ ] |     Power     | ", // Ligne 15
        "    @@@@@            @@@@@@@    \n\n"
    };

    // 3. Placement de la croix 'X' au bon endroit (Ligne 12 + param_selectionne)
    // L'indice 40 correspond à l'espace entre les crochets [ ]
    if (param_selectionne){
    image[11 + param_selectionne][40] = 'X';
    }

    // 4. Rendu final
    printf("\033[H\033[J"); // Clear screen
    for (int i = 0; i < 17; i++) {
        printf("%s", image[i]);
        
        // Ajout des valeurs dynamiques à droite du tableau ASCII
        if (i == 12) printf("%s %*s|", v_baud, 13 - (int)strlen(opts_baud[idx_baud]), " ");
        if (i == 13) printf("%s %*s|", v_freq, 13 - (int)strlen(opts_freq[idx_freq]), " ");
        if (i == 14) printf("%s %*s|", v_data, 13 - (int)strlen(opts_data[idx_data]), " ");
        if (i == 15) printf("%s %*s|", v_pwr, 13 - (int)strlen(opts_power[idx_pwr]), " ");
        
        printf("\n");
    }
}

int est_positif(char *entree, const char *choix_oui) {
    return strcmp(entree, choix_oui) == 0;
}

int config_menu(int indice_depart, int min, int max) {
    int indice = indice_depart;
    int c;

    while (1) {
        // 1. Nettoyage et Affichage (ANSI escape pour Linux)
        afficher_interface(indice, b, f, d, p, 0); 

        // 2. Lecture de la touche
        c = getch_linux();

        // 3. Logique des touches
        if (c == 10) { // 10 = Touche Entrée sous Linux
            return indice;
        }

        if (c == 27) { // Début d'une séquence d'échappement (Flèches)
            getch_linux(); // On ignore le '['
            switch(getch_linux()) {
                case 'A': // Flèche Haut
                    if (indice > min) indice--;
                    break;
                case 'B': // Flèche Bas
                    if (indice < max) indice++;
                    break;
            }
        }
    }
}

int gerer_valeur(short *index_actuel, int max_options) {
    int c = getch_linux();
    if (c == 27) { // Séquence d'échappement
        getch_linux(); // ignore [
        switch(getch_linux()) {
            case 'A': // Haut
                (*index_actuel) = (*index_actuel - 1 + max_options) % max_options;
                break;
            case 'B': // Bas
                (*index_actuel) = (*index_actuel + 1) % max_options;
                break;
        }
    }
    return c; // On retourne la touche pour savoir si c'est 'Entrée' (10)
}

void select_param(int param){
    int sel = param-1;
    while (1) {
        afficher_interface(sel+1, b, f, d, p, 1);
        
        short *indices[] = {&b, &f, &d, &p};
        int touche = gerer_valeur(indices[sel], tailles[sel]);

        if (touche == 10) { // Entrée : on passe au paramètre suivant (ou on valide tout)
            break;
            // Optionnel : si sel revient à 0, vous pouvez décider de quitter
        }
    }
}

void configure_LoRa_module(){
    printf("\n\n-----------------------------\n");
    printf("Message sent via UART...\n");

    int rate_config = config_DataRate(b, d);
    printf("    1.  0x%x\n", rate_config);
    send_msg_uart((char *)&rate_config, sizeof(rate_config));

    int freq_config = setup_frequency(f);
    printf("    2.  0x%x\n", freq_config);
    send_msg_uart((char *)&freq_config, sizeof(freq_config));

    int power_config = setup_power(p);
    printf("    3.  0x%x\n", power_config);
    send_msg_uart((char *)&power_config, sizeof(power_config));

    printf("-----------------------------\n");
}
void setup_address(){
    char address[6];
    printf("Setup module's address [XXXX]: ");
    if (fgets(address, sizeof(address), stdin)) {
            // Supprimer le caractère de nouvelle ligne '\n' capturé par fgets
            address[strcspn(address, "\n")] = 0;
        }
    int address_int = 0;
    for (int i=0; i<4; i++){
        if (47 < (int)(address[i]) && (int)(address[i]) < 58){
            address_int += ((int)(address[i]-48)<<(4*(3-i)));
        } else if (96 < (int)(address[i]) && (int)(address[i]) < 103){
            address_int += ((int)(address[i]-87)<<(4*(3-i)));
        } else if (64 < (int)(address[i]) && (int)(address[i]) < 71){
            address_int += ((int)(address[i]-55)<<(4*(3-i)));
        }
    }
    printf("\n\n-----------------------------\n");
    printf("Message sent via UART...\n");
    long int addr_config = config_address((unsigned short)address_int);
    printf("    1.  0x%lx\n", addr_config);
    send_msg_uart((char *)&addr_config, sizeof(addr_config));
    printf("-----------------------------\n");
}

void starting_menu(){
    while (1){
        afficher_interface(0, b, f, d, p, 0);
        char reponse[10]; // Buffer pour stocker la réponse

        // 1. Affichage de la question
        printf("Keep those Value ? [yes/no]: ");
        fflush(stdout); // Force l'affichage sur certains terminaux

        // 2. Récupération de la saisie
        if (fgets(reponse, sizeof(reponse), stdin)) {
            // Supprimer le caractère de nouvelle ligne '\n' capturé par fgets
            reponse[strcspn(reponse, "\n")] = 0;
        }

        if (est_positif(reponse, "no")) {
            int set = config_menu(1, 1, 4);
            select_param(set);
        } else {
            break;

        }
    }
    configure_LoRa_module();
    setup_address();
}

int main() {
    init_frequences();
    starting_menu();
    // printf("Starting LoRa + UART System...\n\n");

    // // 1. Generate LoRa Configuration Messages
    // // Using functions from LoRa.h
    // unsigned short my_addr = 0x1234;
    // long int addr_config = config_address(my_addr);
    // int freq_config = setup_frequency(868); // 868 MHz

    // // 2. Send Configuration over UART
    // // Using functions from Uart.h
    // printf("Sending Address Config to LoRa module...\n");
    // send_msg_uart((char *)&addr_config, sizeof(addr_config));

    // printf("Sending Frequency Config to LoRa module...\n");
    // send_msg_uart((char *)&freq_config, sizeof(freq_config));

    // // 3. Receive data from UART
    // printf("Waiting for response from module...\n");
    // recv_msg_uart(64);

    // return 0;
}