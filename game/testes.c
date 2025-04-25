#include <stdio.h>
#include <string.h>
#include "jogo.h"

void teste_carregamento() {
    Jogo j;
    if (!carregar_jogo(&j, "tabuleiro.txt")) {
        printf("❌ Erro ao carregar tabuleiro\n");
        return;
    }

    if (j.linhas != 5 || j.colunas != 5)
        printf("❌ Dimensões incorretas\n");
    else if (j.tabuleiro[0][0] != 'e')
        printf("❌ Conteúdo incorreto\n");
    else
        printf("✅ Teste de carregamento passou\n");
}

void teste_pintar_riscar() {
    Jogo j;
    carregar_jogo(&j, "tabuleiro.txt");

    pintar_branco(&j, 0, 0);
    if (j.tabuleiro[0][0] != 'E') {
        printf("❌ Pintar branco falhou\n");
        return;
    }

    riscar(&j, 0, 1);
    if (j.tabuleiro[0][1] != '#') {
        printf("❌ Riscar falhou\n");
        return;
    }

    printf("✅ Teste de pintar e riscar passou\n");
}

int main() {
    teste_carregamento();
    teste_pintar_riscar();
    return 0;
}
