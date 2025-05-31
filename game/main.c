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

                printf("Erro ao carregar tabuleiro.\n");

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

            verificar_regras(&jogo);
            verificar_conectividade1(&jogo);

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
        
            sprintf(ficheiro, "%s.txt", nome);
        
            if (gravar_jogo(&jogo, ficheiro)) {
                printf("Tabuleiro guardado\n");
            } else {
                printf("Erro ao guardar tabuleiro\n");
            }
        } else if (cmd[0] == 'a') {
            // Dica: aplica um passo automático
            guardar_estado(&hist, &jogo);
            if (dica(&jogo)) {
                mostrar_tabuleiro(&jogo);
            } else {
                printf("Nenhuma dica possível.\n");
            }
        } else if (cmd[0] == 'R' || cmd[0] == 'A') {
            // Resolve tudo automaticamente
            guardar_estado(&hist, &jogo);
            resolver(&jogo);
            mostrar_tabuleiro(&jogo);
        } else {

            printf("Comando desconhecido.\n");

        }
        
    }

    printf("Adeus!\n");
    return 0;
}