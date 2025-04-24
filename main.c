#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#include "menu.c"

struct testar
{
    int linhas;
    int colonas;


} UserInput;
//struck

// stack de undo 

// 
//int linhas = 5;
//int colonas = 5;

void input() {

    assert(scanf("%d %d", &UserInput.linhas, &UserInput.colonas) == 2);

}


int main() {



    input();

    int TamanhoLinhas = UserInput.linhas;
    int TamanhoColonas = UserInput.colonas;
    char linha1 [TamanhoLinhas];
    char matrix [TamanhoColonas] [TamanhoLinhas + 1];

    srand(time(NULL));

for(int j = 0; j < TamanhoColonas; j++ ){ 
    for (int i = 0; i < TamanhoLinhas; i++){

        matrix[j][i] = (rand() % 10) + 'a';
        //linha1[i] = (rand() % 26) + 'a';

    }

    matrix[j][TamanhoLinhas] = '\0';

}
    linha1[TamanhoLinhas] = '\0';
for (int j = 0; j < TamanhoColonas; j++){
    for (int i = 0; i < TamanhoLinhas; i++){

        printf("%c", matrix[j][i]);

        if (i < TamanhoLinhas - 1){

            printf(" ");

        }

    }
    printf("\n");
}
    return 0;
}

//teste
