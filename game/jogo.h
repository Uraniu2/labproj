#ifndef JOGO_H
#define JOGO_H

#define MAX 50
#define HIST 100

typedef struct {
    int linhas, colunas;
    char tabuleiro[MAX][MAX];
} Jogo;

typedef struct {
    Jogo estados[HIST];
    int topo;
} Historico;

int carregar_jogo(Jogo *j, const char *ficheiro);
int verificar_conectividade(Jogo *j);
void pintar_branco(Jogo *j, int linha, int coluna);
void riscar(Jogo *j, int linha, int coluna);
void copiar_jogo(Jogo *dest, Jogo *orig);
void guardar_estado(Historico *h, Jogo *j);
int desfazer(Historico *h, Jogo *j);
void mostrar_tabuleiro(Jogo *j);
void verificar_regras(Jogo *j);

#endif
