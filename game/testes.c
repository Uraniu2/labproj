#include <stdio.h>
#include <ctype.h>

#define TAMANHO 5

typedef struct {
    int linhas;
    int colunas;
    char tabuleiro[100][100];
} Jogo;

typedef struct {
    int i, j;
} Posicao;


void imprimirTabuleiro(char tabuleiro[TAMANHO][TAMANHO]) {
    for (int i = 0; i < TAMANHO; i++) {
        for (int j = 0; j < TAMANHO; j++) {
            printf("%c ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

void riscar1(char tabuleiro[TAMANHO][TAMANHO], int i, int j) {
    tabuleiro[i][j] = '#';
}

void pintarBranco(char tabuleiro[TAMANHO][TAMANHO], int i, int j) {
    tabuleiro[i][j] = toupper(tabuleiro[i][j]);
}

int temDuplicataNaLinha(char tabuleiro[TAMANHO][TAMANHO], int linha, char letra) {
    int contador = 0;
    for (int j = 0; j < TAMANHO; j++) {
        if (tabuleiro[linha][j] == letra) {
            contador++;
            if (contador > 1) return 1;
        }
    }
    return 0;
}

int temDuplicataNaColuna(char tabuleiro[TAMANHO][TAMANHO], int coluna, char letra) {
    int contador = 0;
    for (int i = 0; i < TAMANHO; i++) {
        if (tabuleiro[i][coluna] == letra) {
            contador++;
            if (contador > 1) return 1;
        }
    }
    return 0;
}

int diagonais_riscadas(char tabuleiro[TAMANHO][TAMANHO]) {

    for (int k = 0; k < 2 * TAMANHO - 1; k++) {
        int freq[26] = {0};  

        for (int i = 0; i < TAMANHO; i++) {
            int j = k - i;
            if (j >= 0 && j < TAMANHO) {
                char c = tabuleiro[i][j];
                if (c >= 'A' && c <= 'Z') {
                    int idx = c - 'A';
                    if (freq[idx] > 0)
                        return 0;  
                    freq[idx]++;
                }
            }
        }
    }


    for (int k = 0; k < 2 * TAMANHO - 1; k++) {
        int freq[26] = {0};

        for (int i = 0; i < TAMANHO; i++) {
            int j = k - (TAMANHO - 1 - i);
            if (j >= 0 && j < TAMANHO) {
                char c = tabuleiro[i][j];
                if (c >= 'A' && c <= 'Z') {
                    int idx = c - 'A';
                    if (freq[idx] > 0)
                        return 0;  
                    freq[idx]++;
                }
            }
        }
    }

    return 1; 
}


int vizinho_riscado(char tabuleiro[TAMANHO][TAMANHO], int linhas, int colunas, int i, int j) {
    int di[] = {-1, 1, 0, 0};
    int dj[] = {0, 0, -1, 1};

    for (int k = 0; k < 4; k++) {
        int ni = i + di[k];
        int nj = j + dj[k];
        if (ni >= 0 && ni < linhas && nj >= 0 && nj < colunas) {
            if (tabuleiro[ni][nj] == '#') return 1;
        }
    }
    return 0;
}

int casa_isolada(char tabuleiro[TAMANHO][TAMANHO], int linhas, int colunas, int i, int j_col) {

    int eh_canto = 
        (i == 0 && j_col == 0) ||  
        (i == 0 && j_col == colunas - 1) ||  
        (i == linhas - 1 && j_col == 0) ||  
        (i == linhas - 1 && j_col == colunas - 1);  

    if (!eh_canto)
        return 0;

    
    int di[] = {-1, 1, 0, 0};
    int dj[] = {0, 0, -1, 1};

    for (int k = 0; k < 4; k++) {
        int ni = i + di[k];
        int nj = j_col + dj[k];

        
        if (ni >= 0 && ni < linhas && nj >= 0 && nj < colunas) {
            if (tabuleiro[ni][nj] != '#') {
                return 0;
            }
        }
    }

    return 1; 
}

int dentroDoTabuleiro(int i, int j) {
    return i >= 0 && i < TAMANHO && j >= 0 && j < TAMANHO;
}

void dfs(char tabuleiro[TAMANHO][TAMANHO], int visitado[TAMANHO][TAMANHO], int i, int j) {
    int di[] = {-1, 1, 0, 0};
    int dj[] = {0, 0, -1, 1};

    visitado[i][j] = 1;

    for (int k = 0; k < 4; k++) {
        int ni = i + di[k];
        int nj = j + dj[k];

        if (dentroDoTabuleiro(ni, nj)
            && !visitado[ni][nj]
            && tabuleiro[ni][nj] != '#'
            && (tabuleiro[ni][nj] >= 'A' && tabuleiro[ni][nj] <= 'Z')) {
            dfs(tabuleiro, visitado, ni, nj);
        }
    }
}

int todasConectadas(char tabuleiro[TAMANHO][TAMANHO]) {
    int visitado[TAMANHO][TAMANHO] = {0};
    int encontrou = 0;
    int start_i = -1, start_j = -1;

    
    for (int i = 0; i < TAMANHO && !encontrou; i++) {
        for (int j = 0; j < TAMANHO && !encontrou; j++) {
            if (tabuleiro[i][j] >= 'A' && tabuleiro[i][j] <= 'Z') {
                start_i = i;
                start_j = j;
                encontrou = 1;
            }
        }
    }

    if (!encontrou)
        return 1; 

    
    dfs(tabuleiro, visitado, start_i, start_j);

    
    for (int i = 0; i < TAMANHO; i++) {
        for (int j = 0; j < TAMANHO; j++) {
            if ((tabuleiro[i][j] >= 'A' && tabuleiro[i][j] <= 'Z') && !visitado[i][j])
                return 0; 
        }
    }

    return 1; 
}
void minimizarNaoVizinhoDeRiscados(char tabuleiro[TAMANHO][TAMANHO]) {
    int di[] = {-1, 1, 0, 0};
    int dj[] = {0, 0, -1, 1};

    for (int i = 0; i < TAMANHO; i++) {
        for (int j = 0; j < TAMANHO; j++) {
            
            if (tabuleiro[i][j] >= 'A' && tabuleiro[i][j] <= 'Z') {
                int podeMinimizar = 1;

                
                for (int k = 0; k < 4; k++) {
                    int ni = i + di[k];
                    int nj = j + dj[k];

                    
                    if (dentroDoTabuleiro(ni, nj) && tabuleiro[ni][nj] == '#') {
                        podeMinimizar = 0;  
                        break;
                    }
                }


                if (podeMinimizar) {
                    tabuleiro[i][j] = tolower(tabuleiro[i][j]);
                }
            }
        }
    }
}


void aplicarRegras(char tabuleiro[TAMANHO][TAMANHO]) {
    int casasRiscadas[TAMANHO][TAMANHO] = {0};
    Posicao candidatos[100];
    int total = 0;


    for (int i = 0; i < TAMANHO; i++)
        for (int j = 0; j < TAMANHO; j++)
            pintarBranco(tabuleiro, i, j);


    for (int i = 0; i < TAMANHO; i++) {
        for (int j = 0; j < TAMANHO; j++) {
            char letra = tabuleiro[i][j];

            if ((letra >= 'A' && letra <= 'Z') &&
                (temDuplicataNaLinha(tabuleiro, i, letra) || temDuplicataNaColuna(tabuleiro, j, letra)) &&
                !casasRiscadas[i][j]) {

                candidatos[total].i = i;
                candidatos[total].j = j;
                total++;
            }
        }
    }


    for (int k = 0; k < total; k++) {
        int i = candidatos[k].i;
        int j = candidatos[k].j;


        char copia[TAMANHO][TAMANHO];
        for (int x = 0; x < TAMANHO; x++)
            for (int y = 0; y < TAMANHO; y++)
                copia[x][y] = tabuleiro[x][y];


        copia[i][j] = '#';

        int pode_riscar = 0;


        if (vizinho_riscado(tabuleiro, TAMANHO, TAMANHO, i, j)) {
            if (diagonais_riscadas(copia)) {
                pode_riscar = 1;
            }
        } else {

            if (todasConectadas(copia)) {
                
                pode_riscar = 1;
                
            }
        }


        if (pode_riscar) {
            riscar1(tabuleiro, i, j);
            casasRiscadas[i][j] = 1;
        }
    }
    

}




int main() {
    char tabuleiro[TAMANHO][TAMANHO] = {
        {'e', 'c', 'a', 'd', 'c'},
        {'d', 'c', 'd', 'e', '#'},
        {'b', 'd', 'd', 'c', 'e'},
        {'c', 'd', 'e', 'e', 'b'},
        {'a', '#', 'c', 'b', '#'}
    };

    printf("Tabuleiro inicial:\n");
    imprimirTabuleiro(tabuleiro);

    aplicarRegras(tabuleiro);
    printf("\nTabuleiro após aplicar as regras:\n");
    imprimirTabuleiro(tabuleiro);

    return 0;
}
