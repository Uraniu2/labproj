#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "jogo.h"

int main() {
    Jogo jogo;
    Historico hist = {.topo = 0};
    char cmd[100];

    while (1) {
        printf("> ");
        if (!fgets(cmd, sizeof(cmd), stdin)) break;

        if (cmd[0] == 's') break;
        else if (cmd[0] == 'l') {
            char nome[50];
            sscanf(cmd, "l %s", nome);
            if (carregar_jogo(&jogo, nome)) {
                hist.topo = 0;
                guardar_estado(&hist, &jogo);
                printf("Tabuleiro carregado!\n");
                mostrar_tabuleiro(&jogo);
            } else {
                printf("ERRO a carregar tabuleiro.\n");
            }
        } else if (cmd[0] == 'b') {
            int l; char c;
            sscanf(cmd, "b %c%d", &c, &l);
            guardar_estado(&hist, &jogo);
            pintar_branco(&jogo, l - 1, c - 'a');
            mostrar_tabuleiro(&jogo);
        } else if (cmd[0] == 'r') {
            int l; char c;
            sscanf(cmd, "r %c%d", &c, &l);
            guardar_estado(&hist, &jogo);
            riscar(&jogo, l - 1, c - 'a');
            mostrar_tabuleiro(&jogo);
        } else if (cmd[0] == 'v') {
            int erro = 0;
            if (!verificar_regras(&jogo)) erro = 1;
            if (!verificar_conectividade1(&jogo)) erro = 1;
            if (erro)
                printf("Tabuleiro inválido!\n");
            else
                printf("Tabuleiro válido!\n");
        } else if (cmd[0] == 'd') {
            if (desfazer(&hist, &jogo)) {
                printf("Ultima jogada desfeita.\n");
                mostrar_tabuleiro(&jogo);
            } else {
                printf("Nada para desfazer.\n");
            }
        } else if (cmd[0] == 'g') {
            char nome[50];
            sscanf(cmd, "g %s", nome);
            char ficheiro[100];
            sprintf(ficheiro, "%s", nome);
            if (gravar_jogo(&jogo, ficheiro)) {
                printf("Tabuleiro guardado\n");
            } else {
                printf("Erro ao guardar tabuleiro\n");
            }
        } else if (cmd[0] == 'a') {
            guardar_estado(&hist, &jogo);
            if (dica(&jogo)) {
                mostrar_tabuleiro(&jogo);
            } else {
                printf("Nenhuma dica possível.\n");
            }
        } else if (cmd[0] == 'R') {
            guardar_estado(&hist, &jogo);
            resolver(&jogo);
            mostrar_tabuleiro(&jogo);
        } else if (cmd[0] == 'A') {
            guardar_estado(&hist, &jogo);
            if (dica(&jogo)) {
                mostrar_tabuleiro(&jogo);
            } else {
                printf("Nenhuma dica possível.\n");
            }
        } else if (cmd[0] == 'h') {
            printf("Comandos disponíveis:\n");
            printf("g <jogo>       - gravar o estado atual do jogo num ficheiro\n");
            printf("l <jogo>       - ler o estado do jogo de um ficheiro\n");
            printf("<coordenada>   - jogar numa coordenada (<letra><número>)\n");
            printf("b <coordenada> - colocar a letra da casa correspondente à coordenada em maiúsculas\n");
            printf("r <coordenada> - colocar um # no local da letra\n");
            printf("v              - verificar o estado do jogo e apontar todas as restrições violadas\n");
            printf("a              - ajudar mudando o estado de todas as casas que se conseguem inferir\n");
            printf("A              - aplicar uma dica automática\n");
            printf("R              - resolver o jogo\n");
            printf("d              - desfazer o último comando executado\n");
            printf("s              - sair do programa\n");
            printf("h ou h(Etc..)  - mostrar esta mensagem de ajuda\n"); 
        } else {
            printf("Comando desconhecido.\n");
        }
    }

    printf("Adeus!\n");
    return 0;
}
