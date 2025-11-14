#include <stdio.h>

#define TAM 10            // Tamanho do tabuleiro
#define NAVIO 3           // Representa navio
#define HABILIDADE 5      // Representa área de efeito da habilidade
#define SIZE 5            // Tamanho das matrizes de habilidade (5x5)
#define MID 2             // Centro da matriz (5/2 = 2)

int main() {

    int tabuleiro[TAM][TAM];

    //---------------------------------------------
    // 1. Inicializar tabuleiro com água (0)
    //---------------------------------------------
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            tabuleiro[i][j] = 0;
        }
    }

    //---------------------------------------------
    // 2. Posicionar navios (mesmo do nível anterior)
    //---------------------------------------------

    // Navio horizontal
    int linH = 2, colH = 4;
    for (int i = 0; i < 3; i++) {
        tabuleiro[linH][colH + i] = NAVIO;
    }

    // Navio vertical
    int linV = 5, colV = 1;
    for (int i = 0; i < 3; i++) {
        tabuleiro[linV + i][colV] = NAVIO;
    }

    //---------------------------------------------
    // 3. Criar matrizes de habilidade (dinâmico)
    //---------------------------------------------

    int cone[SIZE][SIZE];
    int cruz[SIZE][SIZE];
    int octaedro[SIZE][SIZE];

    // ----- A) Preencher matriz CONE -----
    // Cone apontando para baixo: 
    // nível 0 → apenas centro
    // nível 1 → 3 posições
    // nível 2 → 5 posições
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {

            if (i == 0 && j == MID) {
                cone[i][j] = 1;   // topo do cone
            }
            else if (i == 1 && (j >= MID - 1 && j <= MID + 1)) {
                cone[i][j] = 1;
            }
            else if (i == 2 && (j >= 0 && j < SIZE)) {
                cone[i][j] = 1;
            }
            else {
                cone[i][j] = 0;
            }
        }
    }

    // ----- B) Preencher matriz CRUZ -----
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {

            if (i == MID || j == MID) {
                cruz[i][j] = 1;
            } else {
                cruz[i][j] = 0;
            }
        }
    }

    // ----- C) Preencher matriz OCTAEDRO -----
    // Distância de Manhattan até o centro
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {

            int dist = (i > MID ? i - MID : MID - i)
                      + (j > MID ? j - MID : MID - j);

            if (dist <= 2) {  
                octaedro[i][j] = 1;
            } else {
                octaedro[i][j] = 0;
            }
        }
    }

    //---------------------------------------------
    // 4. Definir origem das habilidades
    //---------------------------------------------
    int origemConeLinha = 1, origemConeColuna = 1;
    int origemCruzLinha = 7, origemCruzColuna = 7;
    int origemOctLinha = 4, origemOctColuna = 6;

    //---------------------------------------------
    // 5. Sobrepor habilidades no tabuleiro
    //---------------------------------------------

    // Função manual: sobrepõe apenas se for 1 e dentro dos limites

    // --- Cone ---
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            int lin = origemConeLinha + (i - MID);
            int col = origemConeColuna + (j - MID);

            if (lin >= 0 && lin < TAM && col >= 0 && col < TAM) {
                if (cone[i][j] == 1) {
                    tabuleiro[lin][col] = HABILIDADE;
                }
            }
        }
    }

    // --- Cruz ---
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            int lin = origemCruzLinha + (i - MID);
            int col = origemCruzColuna + (j - MID);

            if (lin >= 0 && lin < TAM && col >= 0 && col < TAM) {
                if (cruz[i][j] == 1) {
                    tabuleiro[lin][col] = HABILIDADE;
                }
            }
        }
    }

    // --- Octaedro ---
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            int lin = origemOctLinha + (i - MID);
            int col = origemOctColuna + (j - MID);

            if (lin >= 0 && lin < TAM && col >= 0 && col < TAM) {
                if (octaedro[i][j] == 1) {
                    tabuleiro[lin][col] = HABILIDADE;
                }
            }
        }
    }

    //---------------------------------------------
    // 6. Exibir tabuleiro final
    //---------------------------------------------
    printf("\n===== TABULEIRO FINAL COM HABILIDADES =====\n\n");

    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {

            if (tabuleiro[i][j] == 0)
                printf(" . ");   // água
            else if (tabuleiro[i][j] == NAVIO)
                printf(" 3 ");   // navio
            else if (tabuleiro[i][j] == HABILIDADE)
                printf(" 5 ");   // área de habilidade
            
        }
        printf("\n");
    }

    return 0;
}
