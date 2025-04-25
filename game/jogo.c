#include <stdio.h>
#include "jogo.h"

int carregar_jogo(Jogo *j, const char *ficheiro) {
    FILE *f = fopen(ficheiro, "r");
    if (!f) return 0;

    fscanf(f, "%d %d\n", &j->linhas, &j->colunas);
    for (int i = 0; i < j->linhas; i++) {
        for (int k = 0; k < j->colunas; k++) {
            fscanf(f, "%c", &j->tabuleiro[i][k]);
        }
        fscanf(f, "\n");
    }

    fclose(f);
    return 1;
}

void mostrar_tabuleiro(Jogo *j) { //POR BONITO AAKA POR AS CORDENADAS EMCIMA PRO PAVLO PRONTOS 
    for (int i = 0; i < j->linhas; i++) {
        for (int k = 0; k < j->colunas; k++) {
            printf("%c ", j->tabuleiro[i][k]);
        }
        printf("\n");
    }
}

void pintar_branco(Jogo *j, int linha, int coluna) {
    if (j->tabuleiro[linha][coluna] >= 'a' && j->tabuleiro[linha][coluna] <= 'z') {
        j->tabuleiro[linha][coluna] -= 32; // minúscula -> maiúscula
        printf("Pintado a branco: %c\n", j->tabuleiro[linha][coluna]);
    }
}

void riscar(Jogo *j, int linha, int coluna) {
    j->tabuleiro[linha][coluna] = '#';
    printf("Casa riscada!\n");
}

void copiar_jogo(Jogo *dest, Jogo *orig) {
    dest->linhas = orig->linhas;
    dest->colunas = orig->colunas;
    for (int i = 0; i < orig->linhas; i++)
        for (int j = 0; j < orig->colunas; j++)
            dest->tabuleiro[i][j] = orig->tabuleiro[i][j];
}

void guardar_estado(Historico *h, Jogo *j) {
    if (h->topo < HIST) {
        copiar_jogo(&h->estados[h->topo++], j);
    }
}

int desfazer(Historico *h, Jogo *j) {
    if (h->topo == 0) return 0;
    copiar_jogo(j, &h->estados[--h->topo]);
    return 1;
}

void verificar_regras(Jogo *j) {
    int erro = 0;

    // Regras de duplicação em branco (maiusculas)
    for (int i = 0; i < j->linhas; i++) {
        int usados[256] = {0};
        for (int k = 0; k < j->colunas; k++) {
            char c = j->tabuleiro[i][k];
            if (c >= 'A' && c <= 'Z') {
                if (usados[(int)c]++) {
                    printf("X Repetição '%c' na linha %d\n", c, i+1);
                    erro = 1;
                }
            }
        }
    }

    for (int k = 0; k < j->colunas; k++) {
        int usados[256] = {0};
        for (int i = 0; i < j->linhas; i++) {
            char c = j->tabuleiro[i][k];
            if (c >= 'A' && c <= 'Z') {
                if (usados[(int)c]++) {
                    printf("❌ Repetição '%c' na coluna %c\n", c, 'a' + k);
                    erro = 1;
                }
            }
        }
    }

    // Regras das casas riscadas
    for (int i = 0; i < j->linhas; i++) {
        for (int k = 0; k < j->colunas; k++) {
            if (j->tabuleiro[i][k] == '#') {
                int tem_branco = 0;
                if (i > 0 && j->tabuleiro[i-1][k] >= 'A' && j->tabuleiro[i-1][k] <= 'Z') tem_branco = 1;
                if (i < j->linhas-1 && j->tabuleiro[i+1][k] >= 'A' && j->tabuleiro[i+1][k] <= 'Z') tem_branco = 1;
                if (k > 0 && j->tabuleiro[i][k-1] >= 'A' && j->tabuleiro[i][k-1] <= 'Z') tem_branco = 1;
                if (k < j->colunas-1 && j->tabuleiro[i][k+1] >= 'A' && j->tabuleiro[i][k+1] <= 'Z') tem_branco = 1;

                if (!tem_branco) {
                    printf("❌ Casa #(%d,%c) sem vizinho branco\n", i+1, 'a'+k);
                    erro = 1;
                }
            }
        }
    }

    if (!erro)
        printf("✅ Nenhuma regra foi violada\n");
}
