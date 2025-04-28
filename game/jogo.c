#include <stdio.h>
#include <stdlib.h>

#define MAX 10
#define HIST 100

typedef struct {
    int linhas, colunas;
    char tabuleiro[MAX][MAX];
} Jogo;

typedef struct {
    Jogo estados[HIST];
    int topo;
} Historico;

// Funções

int carregar_jogo(Jogo *j, const char *ficheiro) {

    FILE *f = fopen(ficheiro, "r");
    if (!f) return 0;  

    if (fscanf(f, "%d %d\n", &j->linhas, &j->colunas) != 2) {

        fclose(f);
        return 0;  

    }

    
    for (int i = 0; i < j->linhas; i++) {
        for (int k = 0; k < j->colunas; k++) {
            
            if (fscanf(f, " %c", &j->tabuleiro[i][k]) != 1) {

                fclose(f);
                return 0;  

            }
        }
    }

    fclose(f); 
    return 1;  
}
int gravar_jogo(const Jogo *j, const char *ficheiro) {
    FILE *f = fopen(ficheiro, "w");
    if (!f) return 0; 

    if (fprintf(f, "%d %d\n", j->linhas, j->colunas) < 0) {
        fclose(f);
        return 0;
    }

    
    for (int i = 0; i < j->linhas; i++) {
        for (int k = 0; k < j->colunas; k++) {
            if (fprintf(f, "%c", j->tabuleiro[i][k]) < 0) {
                fclose(f);
                return 0;
            }
        }
        fprintf(f, "\n");  
    }

    fclose(f);
    return 1;  
}


void mostrar_tabuleiro(Jogo *j) {

    for (int i = 0; i < j->linhas; i++) {
        for (int k = 0; k < j->colunas; k++) {

            printf("%c ", j->tabuleiro[i][k]);

        }

        printf("\n");

    }
}

void pintar_branco(Jogo *j, int linha, int coluna) {

    if (j->tabuleiro[linha][coluna] >= 'a' && j->tabuleiro[linha][coluna] <= 'z') {

        j->tabuleiro[linha][coluna] -= 32; // minúscula -> maiuscula
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
        for (int k = 0; k < orig->colunas; k++)

            dest->tabuleiro[i][k] = orig->tabuleiro[i][k];

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

    // Regras de duplicação em branco
    for (int i = 0; i < j->linhas; i++) {

        int usados[256] = {0};

        for (int k = 0; k < j->colunas; k++) {

            char c = j->tabuleiro[i][k];

            if (c >= 'A' && c <= 'Z') {
                if (usados[(int)c]++) {

                    printf("X Repeticao '%c' na linha %d\n", c, i+1);
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

                    printf("Repeticao '%c' na coluna %c\n", c, 'a' + k);
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

                    printf("Casa #(%d,%c) sem vizinho branco\n", i+1, 'a'+k);
                    erro = 1;

                }
            }
        }
    }

    if (!erro)

        printf("Nenhuma regra foi violada\n");

}

int verificar_conectividade(Jogo *j) {

    int visitado[MAX][MAX] = {{0}};
    int dx[] = {0, 1, 0, -1};
    int dy[] = {1, 0, -1, 0};

    int start_i = -1, start_k = -1;

    for (int i = 0; i < j->linhas && start_i == -1; i++) {
        for (int k = 0; k < j->colunas; k++) {
            if (j->tabuleiro[i][k] >= 'A' && j->tabuleiro[i][k] <= 'Z') {

                start_i = i;
                start_k = k;
                break;

            }
        }
    }

    if (start_i == -1) {

        printf("Nao ha casas brancas.\n");
        return 0;

    }

    int pilha[MAX*MAX][2];
    int topo = 0;
    pilha[topo][0] = start_i;
    pilha[topo++][1] = start_k;
    visitado[start_i][start_k] = 1;

    while (topo > 0) {

        int i = pilha[--topo][0];
        int k = pilha[topo][1];

        for (int d = 0; d < 4; d++) {

            int ni = i + dx[d], nk = k + dy[d];

            if (ni >= 0 && ni < j->linhas && nk >= 0 && nk < j->colunas) {
                if (!visitado[ni][nk] && j->tabuleiro[ni][nk] >= 'A' && j->tabuleiro[ni][nk] <= 'Z') {

                    visitado[ni][nk] = 1;
                    pilha[topo][0] = ni;
                    pilha[topo++][1] = nk;

                }
            }
        }
    }

    for (int i = 0; i < j->linhas; i++) {
        for (int k = 0; k < j->colunas; k++) {
            if (j->tabuleiro[i][k] >= 'A' && j->tabuleiro[i][k] <= 'Z' && !visitado[i][k]) {

                printf("Casa branca isolada em %c%d\n", 'a' + k, i + 1);
                return 0;
                
            }
        }
    }

    printf("Todas as casas brancas estao conectadas.\n");
    return 1;
}