#include <stdio.h>
#include <ctype.h>

#define TAMANHO 5  // Tamanho do tabuleiro

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

int vizinho_riscado(char tabuleiro[TAMANHO][TAMANHO], int linha, char letra){
    //miniscula
}
int casa_isolada(){
    //caso uma casa ficar isolada nao dse pode pintar em volta dela pintar ela
    //risca ela e o resto mete se pintado
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
