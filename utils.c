#include <stdlib.h>
#include <stdio.h>
#include "utils.h"

/*
PRETO 1
BRANCO 2

PEAO 1
TORRE 2
UMA MUSUME/CAVALO 3
BISPO 4
RAINHA 5
REI 6
*/

peca** aloca_matriz(int lar, int alt){

    peca** matriz = calloc( alt, sizeof(peca*));
    for (int i = 0; i<alt; i++){
        matriz[i] = calloc( lar, sizeof(peca));
    }
    return matriz;
}

void ini_mesa(peca** board){

    //PRETAS
    for (int i=0; i<8; i++){
        board[0][i].cor  = 1;
    }
    //TORRES
    board[0][0].tipo = 2;
    board[0][7].tipo = 2;
    //CAVALOS
    board[0][1].tipo = 3;
    board[0][6].tipo = 3;
    //BISPOS
    board[0][2].tipo = 4;
    board[0][5].tipo = 4;
    //RAINHA
    board[0][3].tipo = 5;
    //REI
    board[0][4].tipo = 6;
    //PEOES
    for (int i=0; i<8; i++){
        board[1][i].cor  = 1;
        board[1][i].tipo = 1;
    }

    //BRANCAS
    for (int i=0; i<8; i++){
        board[7][i].cor  = 2;
    }
    //TORRES
    board[7][0].tipo = 2;
    board[7][7].tipo = 2;
    //CAVALOS
    board[7][1].tipo = 3;
    board[7][6].tipo = 3;
    //BISPOS
    board[7][2].tipo = 4;
    board[7][5].tipo = 4;
    //RAINHA
    board[7][3].tipo = 5;
    //REI
    board[7][4].tipo = 6;
    //PEOES
    for (int i=0; i<8; i++){
        board[6][i].cor  = 2;
        board[6][i].tipo = 1;
    }
}

void print_board(peca** board, int lar, int alt){

    for (int i=0; i<alt; i++){
        for (int j=0; j<lar;j++){
            printf("%d ", board[i][j].tipo);
        }
        printf("    ");
        for (int j=0; j<lar;j++){
            printf("%d ", board[i][j].cor);
        }
        printf("\n");
    }
}