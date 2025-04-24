#include <stdio.h>
#include <stdlib.h>

void mostrar_menu() {
    system("clear");
    printf("\n=== MENU ===\n");
    printf("1. Start\n");
    printf("2. DEBUG\n");
    printf("3. Exit\n");
    printf("\nSelect the number\n");

    int Mselector;
    scanf("%d", &Mselector);

    if (Mselector == 1) {
        printf("Starting the game...\n");
    } else if (Mselector == 2) {
        printf("DEBUG mode\n");
    } else if (Mselector == 3) {
        printf("Clossing..\n");
        exit(0); // Exits the program
    }
}
