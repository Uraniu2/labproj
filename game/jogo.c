#include <stdio.h>
#include <stdlib.h>
#include "jogo.h"

//RODAR o projeto
//gcc -Wall -Wextra -pedantic -O1 -fno-omit-frame-pointer -g main.c jogo.c -o jogo
//rodar o testes.c
//gcc -Wall -Wextra -pedantic -O1 -fno-omit-frame-pointer -g testes.c jogo.c -o testar
// Funções principais do puzzle

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

int gravar_jogo(Jogo *j, const char *ficheiro) {
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

// Mostra o tabuleiro atual
void mostrar_tabuleiro(Jogo *j) {
    char coluna = 'a';
    printf("   ");
    for (int r = 0; r < j->colunas; r++) printf(" %c", coluna++);
    printf("\n   ");
    for (int p = 0; p < j->colunas; p++) printf(" |");
    printf("\n");

    for (int i = 0; i < j->linhas; i++) {
        printf("%d - ", i + 1);
        for (int k = 0; k < j->colunas; k++)
            printf("%c ", j->tabuleiro[i][k]);
        printf("\n");
    }
}

// Pinta a casa de branco (maiúscula)
void pintar_branco(Jogo *j, int linha, int coluna) {
    if (j->tabuleiro[linha][coluna] >= 'a' && j->tabuleiro[linha][coluna] <= 'z') {
        j->tabuleiro[linha][coluna] -= 32;
        printf("Pintado a branco: %c\n", j->tabuleiro[linha][coluna]);
    }
}

// Risca a casa (coloca #)
void riscar(Jogo *j, int linha, int coluna) {
    j->tabuleiro[linha][coluna] = '#';
    printf("Casa riscada!\n");
}

// Copia o estado do jogo
void copiar_jogo(Jogo *dest, Jogo *orig) {
    dest->linhas = orig->linhas;
    dest->colunas = orig->colunas;
    for (int i = 0; i < orig->linhas; i++)
        for (int k = 0; k < orig->colunas; k++)
            dest->tabuleiro[i][k] = orig->tabuleiro[i][k];
}

// Guarda estado no histórico
void guardar_estado(Historico *h, Jogo *j) {
    if (h->topo < HIST) copiar_jogo(&h->estados[h->topo++], j);
}

// Desfaz uma jogada
int desfazer(Historico *h, Jogo *j) {
    if (h->topo == 0) return 0;
    copiar_jogo(j, &h->estados[--h->topo]);
    return 1;
}

// Regras: duplicação e riscadas
void verificar_regras(Jogo *j) {
    int erro = 0;

    // Regras de duplicação em branco (linha)
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

    // (coluna)
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

    // Casas riscadas sem vizinho branco
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

// Conectividade das casas brancas
int verificar_conectividade1(Jogo *j) {
    int visitado[MAX][MAX] = {{0}};
    int dx[] = {0, 1, 0, -1};
    int dy[] = {1, 0, -1, 0};

    int start_i = -1, start_k = -1;
    for (int i = 0; i < j->linhas && start_i == -1; i++)
        for (int k = 0; k < j->colunas; k++)
            if (j->tabuleiro[i][k] >= 'A' && j->tabuleiro[i][k] <= 'Z') {
                start_i = i;
                start_k = k;
                break;
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

    for (int i = 0; i < j->linhas; i++)
        for (int k = 0; k < j->colunas; k++)
            if (j->tabuleiro[i][k] >= 'A' && j->tabuleiro[i][k] <= 'Z' && !visitado[i][k]) {
                printf("Casa branca isolada em %c%d\n", 'a' + k, i + 1);
                return 0;
            }

    printf("Todas as casas brancas estao conectadas.\n");
    return 1;
}

// --- FUNÇÕES DE DICA E RESOLUÇÃO AUTOMÁTICA ---

// RISCA se já existe um branco igual na linha/coluna
static int riscar_se_ja_tem_branco(Jogo *j) {
    for (int i = 0; i < j->linhas; i++) {
        for (int k = 0; k < j->colunas; k++) {
            char c = j->tabuleiro[i][k];
            if (c >= 'a' && c <= 'z') {
                int tem_branco = 0;
                for (int x = 0; x < j->colunas; x++)
                    if (j->tabuleiro[i][x] == toupper(c)) tem_branco = 1;
                for (int x = 0; x < j->linhas; x++)
                    if (j->tabuleiro[x][k] == toupper(c)) tem_branco = 1;
                if (tem_branco) {
                    j->tabuleiro[i][k] = '#';
                    printf("Dica: Risquei '%c' porque já existe branco na linha/coluna em %c%d\n", c, 'a'+k, i+1);
                    return 1;
                }
            }
        }
    }
    return 0;
}

// RISCA todas as réplicas de símbolos nas linhas e colunas se já existir a versão maiúscula
static int riscar_replicas(Jogo *j) {
    for (int i = 0; i < j->linhas; i++) {
        for (int k = 0; k < j->colunas; k++) {
            char c = j->tabuleiro[i][k];
            if (c >= 'a' && c <= 'z') {
                for (int cc = 0; cc < j->colunas; cc++)
                    if (j->tabuleiro[i][cc] == toupper(c)) {
                        j->tabuleiro[i][k] = '#';
                        printf("Dica: Risquei '%c' em %c%d\n", c, 'a'+k, i+1);
                        return 1;
                    }
                for (int ll = 0; ll < j->linhas; ll++)
                    if (j->tabuleiro[ll][k] == toupper(c)) {
                        j->tabuleiro[i][k] = '#';
                        printf("Dica: Risquei '%c' em %c%d\n", c, 'a'+k, i+1);
                        return 1;
                    }
            }
        }
    }
    return 0;
}

// PINTA de branco se só pode existir naquela linha/coluna
static int pintar_unico_na_linha_coluna(Jogo *j) {
    for (int i = 0; i < j->linhas; i++) {
        for (int k = 0; k < j->colunas; k++) {
            char c = j->tabuleiro[i][k];
            if (c >= 'a' && c <= 'z') {
                int count_linha = 0, count_coluna = 0;
                for (int x = 0; x < j->colunas; x++)
                    if (j->tabuleiro[i][x] == c) count_linha++;
                for (int x = 0; x < j->linhas; x++)
                    if (j->tabuleiro[x][k] == c) count_coluna++;
                if (count_linha == 1 || count_coluna == 1) {
                    j->tabuleiro[i][k] = toupper(c);
                    printf("Dica: Pintei '%c' de branco por ser único na linha/coluna em %c%d\n", c, 'a'+k, i+1);
                    return 1;
                }
            }
        }
    }
    return 0;
}

// PINTA de branco todos os vizinhos ortogonais de uma casa riscada, se possível
static int pintar_vizinho_riscada(Jogo *j) {
    for (int i = 0; i < j->linhas; i++) {
        for (int k = 0; k < j->colunas; k++) {
            if (j->tabuleiro[i][k] == '#') {
                int dl[4] = {-1, 1, 0, 0}, dc[4] = {0, 0, -1, 1};
                for (int d = 0; d < 4; d++) {
                    int ni = i + dl[d], nj = k + dc[d];
                    if (ni >= 0 && ni < j->linhas && nj >= 0 && nj < j->colunas) {
                        char c = j->tabuleiro[ni][nj];
                        if (c >= 'a' && c <= 'z') {
                            // Só pode pintar se não há já maiúscula igual na linha/coluna
                            int pode = 1;
                            for (int x = 0; x < j->colunas; x++)
                                if (j->tabuleiro[ni][x] == toupper(c)) pode = 0;
                            for (int x = 0; x < j->linhas; x++)
                                if (j->tabuleiro[x][nj] == toupper(c)) pode = 0;
                            if (pode) {
                                j->tabuleiro[ni][nj] = toupper(c);
                                printf("Dica: Pintei vizinho '%c' de branco em %c%d\n", c, 'a'+nj, ni+1);
                                return 1;
                            }
                        }
                    }
                }
            }
        }
    }
    return 0;
}

// PINTA de branco se riscar isola as casas brancas
static int pintar_para_nao_isolar(Jogo *j) {
    for (int i = 0; i < j->linhas; i++) {
        for (int k = 0; k < j->colunas; k++) {
            char c = j->tabuleiro[i][k];
            if (c >= 'a' && c <= 'z') {
                char temp = j->tabuleiro[i][k];
                j->tabuleiro[i][k] = '#';
                int ligado = verificar_conectividade1(j);
                j->tabuleiro[i][k] = temp;
                if (!ligado) {
                    j->tabuleiro[i][k] = toupper(c);
                    printf("Dica: Pintei '%c' de branco (para não isolar) em %c%d\n", c, 'a'+k, i+1);
                    return 1;
                }
            }
        }
    }
    return 0;
}

int dica(Jogo *j) {
    if (riscar_se_ja_tem_branco(j)) return 1;
    if (riscar_replicas(j)) return 1;
    if (pintar_unico_na_linha_coluna(j)) return 1;
    if (pintar_vizinho_riscada(j)) return 1;
    if (pintar_para_nao_isolar(j)) return 1;
    return 0;
}

void resolver(Jogo *j) {
    int passos = 0;
    while (dica(j)) {
        mostrar_tabuleiro(j);
        passos++;
        if (passos > 200) break; // segurança contra loop infinito
    }
    printf("Resolução finalizada em %d passos!\n", passos);
}