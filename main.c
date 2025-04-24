#include <stdio.h>
#include <stdlib.h>
#include "comandos.h"

void mostrar_menu();
void ler_mapa(const char *filename);
void imprimir_mapa();

int main() {
    mostrar_menu();  

    ler_mapa("mapa.txt");  
    imprimir_mapa();        

   

    return 0;
} 


