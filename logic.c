#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#define MAX 100 

#define MAX 100 

char tabuleiro[MAX][MAX]; 
int linhas, colunas;

void ler_mapa(const char *filename) {
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        printf("Erro ao abrir  %s\n", filename);
        exit(1);
    }

    fscanf(f, "%d %d", &linhas, &colunas);

    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            fscanf(f, " %c", &tabuleiro[i][j]); 
        }
    }

    fclose(f);

    }
void imprimir_mapa() {
    printf("\nMapa (%d x %d):\n", linhas, colunas);
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            printf("%c ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}