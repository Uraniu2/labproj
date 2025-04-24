#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jogo.h"

int main() {
    Jogo jogo;
    char comando[100], coord[10];
    int linha, coluna;

    if (!carregar_jogo(&jogo, "tabuleiro.txt")) {
        fprintf(stderr, "Erro ao carregar o jogo.\n");
        return 1;
    }

    while (1) {
        mostrar_jogo(&jogo);
        printf("> ");
        fgets(comando, sizeof(comando), stdin);

        if (comando[0] == 's') break;

        if (comando[0] == 'b' || comando[0] == 'r') {
            sscanf(comando + 1, "%s", coord);
            coluna = coord[0] - 'a';
            linha = atoi(coord + 1) - 1;

            if (comando[0] == 'b')
                pintar_branco(&jogo, linha, coluna);
            else
                riscar(&jogo, linha, coluna);
        }
    }

    return 0;
}
