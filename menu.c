#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#ifndef MENU_H
#define MENU_H

void menuprintf() {

    printf("\n=== MENU ===\n");
    printf("1. Start\n");
    printf("2. DEBUG\n");
    printf("3. Exit\n");
    printf("\nSelect the number\n");

}

void start(){

    //call main.c
    printf("Select the a number if Colums & Lines\n");

}

void debug(){

    printf("NO FUNCTION TO THIS YET\n");

}

void Cexit(){

    exit(0);

}



//void ShowMenu() {
int main() {

    menuprintf();

    int Mselector;
    //char MSselector [30] = {0};

    assert((scanf("%d", &Mselector))==1);
    
    if (Mselector == 1) start();
    if (Mselector == 2) debug();
    if (Mselector == 3) Cexit();
    
}


#endif