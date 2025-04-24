#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// Função para imprimir o menu
void menuprintf() {
    printf("\n=== MENU ===\n");
    printf("1. Start\n");
    printf("2. DEBUG\n");
    printf("3. Exit\n");
    printf("Select an option (1-3): ");
}

// Funções associadas a cada opção
void start() {
    printf("Start selecionado. (Aqui chamarias a lógica de jogo)\n");
    // Aqui poderias invocar o REPL ou carregar o tabuleiro
}

void debug() {
    printf("DEBUG selecionado. (Modo de teste ou extra)\n");
}

void Cexit() {
    printf("A sair...\n");
    exit(0);
}

// Função chamada pelo main.c
void mostrar_menu() {
    int opcao;
    menuprintf();

    if (scanf("%d", &opcao) != 1) {
        printf("Entrada inválida.\n");
        return;
    }

    switch (opcao) {
        case 1: start(); break;
        case 2: debug(); break;
        case 3: Cexit(); break;
        default: printf("Opção inválida.\n");
    }
}
