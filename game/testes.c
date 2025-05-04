#include <stdio.h>
#include <ctype.h>

#define TAMANHO 5  // Tamanho do tabuleiro

typedef struct {
    int linhas;
    int colunas;
    char tabuleiro[100][100]; // ou algum tamanho máximo apropriado
} Jogo;


// Função para imprimir o tabuleiro
void imprimirTabuleiro(char tabuleiro[TAMANHO][TAMANHO]) {
    for (int i = 0; i < TAMANHO; i++) {
        for (int j = 0; j < TAMANHO; j++) {
            printf("%c ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

// Função para riscar a casa
void riscar(char tabuleiro[TAMANHO][TAMANHO], int i, int j) {
    tabuleiro[i][j] = '#';
}

// Função para pintar a letra em maiúsculo
void pintarBranco(char tabuleiro[TAMANHO][TAMANHO], int i, int j) {
    tabuleiro[i][j] = toupper(tabuleiro[i][j]);
}

int temDuplicataNaLinha(char tabuleiro[TAMANHO][TAMANHO], int linha, char letra) {
    int contador = 0;
    for (int j = 0; j < TAMANHO; j++) {
        if (tabuleiro[linha][j] == letra) {
            contador++;
            if (contador > 1) {
                return 1;  // Se a letra aparecer mais de uma vez, retorna 1 (duplicata encontrada)
            }
        }
    }
    return 0;  // Se não encontrar duplicata, retorna 0
}

int temDuplicataNaColuna(char tabuleiro[TAMANHO][TAMANHO], int coluna, char letra) {
    int contador = 0;
    for (int i = 0; i < TAMANHO; i++) {
        if (tabuleiro[i][coluna] == letra) {
            contador++;
            if (contador > 1) {
                return 1;  // Se a letra aparecer mais de uma vez, retorna 1 (duplicata encontrada)
            }
        }
    }
    return 0;  // Se não encontrar duplicata, retorna 0
}


int ehMaiuscula(char letra) {
    return (letra >= 'A' && letra <= 'Z') ? 1 : 0;
}

// Função para aplicar as regras
void aplicarRegras(char tabuleiro[TAMANHO][TAMANHO]) {
    // Matriz para controlar as casas já riscadas
    int casasRiscadas[TAMANHO][TAMANHO] = {0};  // 0 significa que a casa não foi riscada, 1 significa que já foi riscada

    // Primeiro, pintamos todas as casas de branco
    for (int i = 0; i < TAMANHO; i++) {
        for (int j = 0; j < TAMANHO; j++) {
            pintarBranco(tabuleiro, i, j);  // Pintar a casa de branco inicialmente
        }
    }

    // Agora, percorremos o tabuleiro para aplicar as regras
    for (int i = 0; i < TAMANHO; i++) {
        for (int j = 0; j < TAMANHO; j++) {
            char letra = tabuleiro[i][j];

            // Se a letra aparece mais de uma vez na linha ou coluna
            if (temDuplicataNaLinha(tabuleiro, i, letra)==1 || temDuplicataNaColuna(tabuleiro, j, letra)==1) {
                if()
                    if (!casasRiscadas[i][j]) {
                        riscar(tabuleiro, i, j);  // Risca a casa se for minúscula
                        casasRiscadas[i][j] = 1;  // Marca a casa como riscada
                    }
                }
            }
        }
        for (int i = 0; i < TAMANHO; i++) {
            for (int j = 0; j < TAMANHO; j++) {
                if
        }
    }
    }

    int vizinho_riscado(Jogo *j, int i, int j_col) {
        // Verifica se há um '#' nos vizinhos imediatos (cima, baixo, esquerda, direita)
        int di[] = {-1, 1, 0, 0};
        int dj[] = {0, 0, -1, 1};
    
        for (int k = 0; k < 4; k++) {
            int ni = i + di[k];
            int nj = j_col + dj[k];
    
            if (ni >= 0 && ni < j->linhas && nj >= 0 && nj < j->colunas) {
                if (j->tabuleiro[ni][nj] == '#') {
                    return 1;
                }
            }
        }
        return 0;
    }
    
    int casa_isolada(Jogo *j, int i, int j_col) {
        int di[] = {-1, 1, 0, 0};
        int dj[] = {0, 0, -1, 1};
    
        for (int k = 0; k < 4; k++) {
            int ni = i + di[k];
            int nj = j_col + dj[k];
    
            if (ni >= 0 && ni < j->linhas && nj >= 0 && nj < j->colunas) {
                if (j->tabuleiro[ni][nj] == '#') {
                    return 0; // Tem vizinho riscado → não está isolada
                }
            }
        }
    
        return 1; // Nenhum vizinho riscado → está isolada
    }
    
int main() {
    char tabuleiro[TAMANHO][TAMANHO] = {
        {'e', 'c', 'a', 'd', 'c'},
        {'d', 'c', 'd', 'e', 'c'},
        {'b', 'd', 'd', 'c', 'e'},
        {'c', 'd', 'e', 'e', 'b'},
        {'a', 'c', 'c', 'b', 'b'}
    };

    printf("Tabuleiro inicial:\n");
    imprimirTabuleiro(tabuleiro);

    aplicarRegras(tabuleiro);

    printf("\nTabuleiro após aplicar as regras:\n");
    imprimirTabuleiro(tabuleiro);

    return 0;
}
