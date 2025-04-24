#include "jogo.h"
#include <stdio.h>
#include <ctype.h>

int carregar_jogo(Jogo *jogo, const char *ficheiro) {
    FILE *f = fopen(ficheiro, "r");
    if (!f) return 0;

    fscanf(f, "%d %d\n", &jogo->linhas, &jogo->colunas);

    for (int i = 0; i < jogo->linhas; i++) {
        for (int j = 0; j < jogo->colunas; j++) {
            jogo->tabuleiro[i][j] = fgetc(f);
        }
        fgetc(f); // ler o \n
    }

    fclose(f);
    return 1;
}

void mostrar_jogo(Jogo *jogo) {
    printf("  ");
    for (int j = 0; j < jogo->colunas; j++)
        printf(" %c", 'a' + j);
    printf("\n");

    for (int i = 0; i < jogo->linhas; i++) {
        printf("%d ", i + 1);
        for (int j = 0; j < jogo->colunas; j++) {
            printf(" %c", jogo->tabuleiro[i][j]);
        }
        printf("\n");
    }
}

int pintar_branco(Jogo *jogo, int linha, int coluna) {
    char *casa = &jogo->tabuleiro[linha][coluna];
    if (*casa == '#' || isupper(*casa)) return 0;
    *casa = toupper(*casa);
    return 1;
}

int riscar(Jogo *jogo, int linha, int coluna) {
    char *casa = &jogo->tabuleiro[linha][coluna];
    if (*casa == '#' || isupper(*casa)) return 0;
    *casa = '#';
    return 1;
}
