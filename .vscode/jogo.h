#ifndef JOGO_H
#define JOGO_H

#define MAX 20

typedef struct {
    int linhas;
    int colunas;
    char tabuleiro[MAX][MAX];
} Jogo;

int carregar_jogo(Jogo *jogo, const char *ficheiro);
void mostrar_jogo(Jogo *jogo);
int pintar_branco(Jogo *jogo, int linha, int coluna);
int riscar(Jogo *jogo, int linha, int coluna);

#endif