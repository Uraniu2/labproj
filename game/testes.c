#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define TAM 5

typedef struct {
    int linhas, colunas;
    char tab[TAM][TAM];
} Jogo;

// Imprime o tabuleiro
void imprimir(Jogo *j) {
    printf("   ");
    for (int c = 0; c < j->colunas; c++)
        printf("%c ", 'a' + c);
    printf("\n");
    for (int l = 0; l < j->linhas; l++) {
        printf("%2d ", l + 1);
        for (int c = 0; c < j->colunas; c++)
            printf("%c ", j->tab[l][c]);
        printf("\n");
    }
    printf("\n");
}

// Função auxiliar: verifica se dentro dos limites
int dentro(Jogo *j, int l, int c) {
    return l >= 0 && l < j->linhas && c >= 0 && c < j->colunas;
}

// DFS para conectividade das casas brancas
void dfs(Jogo *j, int l, int c, int vis[TAM][TAM]) {
    if (!dentro(j, l, c) || vis[l][c] || !isupper(j->tab[l][c])) return;
    vis[l][c] = 1;
    dfs(j, l + 1, c, vis);
    dfs(j, l - 1, c, vis);
    dfs(j, l, c + 1, vis);
    dfs(j, l, c - 1, vis);
}

// Retorna 1 se todas as casas brancas estão conectadas ortogonalmente
int todasConectadas(Jogo *j) {
    int vis[TAM][TAM] = {0};
    int l, c, achou = 0;
    for (l = 0; l < j->linhas && !achou; l++)
        for (c = 0; c < j->colunas && !achou; c++)
            if (isupper(j->tab[l][c])) {
                dfs(j, l, c, vis);
                achou = 1;
            }
    if (!achou) return 1; // nenhum branco = ok
    for (l = 0; l < j->linhas; l++)
        for (c = 0; c < j->colunas; c++)
            if (isupper(j->tab[l][c]) && !vis[l][c])
                return 0;
    return 1;
}

// RISCA todas as réplicas de símbolos nas linhas e colunas se já existir a versão maiúscula
int riscar_replicas(Jogo *j) {
    for (int i = 0; i < j->linhas; i++) {
        for (int k = 0; k < j->colunas; k++) {
            char c = j->tab[i][k];
            if (c >= 'a' && c <= 'z') {
                for (int cc = 0; cc < j->colunas; cc++)
                    if (j->tab[i][cc] == toupper(c)) {
                        j->tab[i][k] = '#';
                        printf("Dica: Risquei '%c' em %c%d\n", c, 'a'+k, i+1);
                        return 1;
                    }
                for (int ll = 0; ll < j->linhas; ll++)
                    if (j->tab[ll][k] == toupper(c)) {
                        j->tab[i][k] = '#';
                        printf("Dica: Risquei '%c' em %c%d\n", c, 'a'+k, i+1);
                        return 1;
                    }
            }
        }
    }
    return 0;
}

// PINTA de branco todos os vizinhos ortogonais de uma casa riscada, se possível
int pintar_vizinho_riscada(Jogo *j) {
    for (int i = 0; i < j->linhas; i++) {
        for (int k = 0; k < j->colunas; k++) {
            if (j->tab[i][k] == '#') {
                int dl[4] = {-1, 1, 0, 0}, dc[4] = {0, 0, -1, 1};
                for (int d = 0; d < 4; d++) {
                    int ni = i + dl[d], nj = k + dc[d];
                    if (dentro(j, ni, nj)) {
                        char c = j->tab[ni][nj];
                        if (c >= 'a' && c <= 'z') {
                            // Só pode pintar se não há já maiúscula igual na linha/coluna
                            int pode = 1;
                            for (int x = 0; x < j->colunas; x++)
                                if (j->tab[ni][x] == toupper(c)) pode = 0;
                            for (int x = 0; x < j->linhas; x++)
                                if (j->tab[x][nj] == toupper(c)) pode = 0;
                            if (pode) {
                                j->tab[ni][nj] = toupper(c);
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
int pintar_para_nao_isolar(Jogo *j) {
    for (int i = 0; i < j->linhas; i++) {
        for (int k = 0; k < j->colunas; k++) {
            char c = j->tab[i][k];
            if (c >= 'a' && c <= 'z') {
                char temp = j->tab[i][k];
                j->tab[i][k] = '#';
                int ligado = todasConectadas(j);
                j->tab[i][k] = temp;
                if (!ligado) {
                    j->tab[i][k] = toupper(c);
                    printf("Dica: Pintei '%c' de branco (para não isolar) em %c%d\n", c, 'a'+k, i+1);
                    return 1;
                }
            }
        }
    }
    return 0;
}

// RISCA se já existe um branco na linha/coluna
int riscar_se_ja_tem_branco(Jogo *j) {
    for (int i = 0; i < j->linhas; i++) {
        for (int k = 0; k < j->colunas; k++) {
            char c = j->tab[i][k];
            if (c >= 'a' && c <= 'z') {
                int tem_branco = 0;
                for (int x = 0; x < j->colunas; x++)
                    if (j->tab[i][x] == toupper(c)) tem_branco = 1;
                for (int x = 0; x < j->linhas; x++)
                    if (j->tab[x][k] == toupper(c)) tem_branco = 1;
                if (tem_branco) {
                    j->tab[i][k] = '#';
                    printf("Dica: Risquei '%c' porque já existe branco na linha/coluna em %c%d\n", c, 'a'+k, i+1);
                    return 1;
                }
            }
        }
    }
    return 0;
}

// PINTA de branco se só pode existir naquela linha/coluna
int pintar_unico_na_linha_coluna(Jogo *j) {
    for (int i = 0; i < j->linhas; i++) {
        for (int k = 0; k < j->colunas; k++) {
            char c = j->tab[i][k];
            if (c >= 'a' && c <= 'z') {
                int count_linha = 0, count_coluna = 0;
                for (int x = 0; x < j->colunas; x++)
                    if (j->tab[i][x] == c) count_linha++;
                for (int x = 0; x < j->linhas; x++)
                    if (j->tab[x][k] == c) count_coluna++;
                if (count_linha == 1 || count_coluna == 1) {
                    j->tab[i][k] = toupper(c);
                    printf("Dica: Pintei '%c' de branco por ser único na linha/coluna em %c%d\n", c, 'a'+k, i+1);
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
        imprimir(j);
        passos++;
        if (passos > 200) break; // segurança contra loop infinito
    }
    printf("Resolução finalizada em %d passos!\n", passos);
}

int main() {
    Jogo jogo = {
        .linhas = 5,
        .colunas = 5,
        .tab = {
            {'e','c','a','d','c'},
            {'d','c','d','e','c'},
            {'b','d','d','c','e'},
            {'c','d','e','e','b'},
            {'a','c','c','b','b'}
        }
    };
    printf("Tabuleiro inicial:\n");
    imprimir(&jogo);
    printf("Aplicando dicas passo a passo:\n");
    resolver(&jogo);
    printf("Tabuleiro final:\n");
    imprimir(&jogo);
    return 0;
}