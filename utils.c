#include <stdlib.h>

/*
    COR:
        0 VAZIO
        1 BRANCO
        2 PRETO

    PEÇA:
        0 VAZIO
        1 PEAO
        2 TORRE
        3 CAVALO
        4 BISPO
        5 RAINHA
        6 REI
*/
typedef struct tile tile_t;
typedef struct no no_t;
typedef struct no_fila no_fila_t;
typedef struct fila fila_t;

// Definição da struct tile
struct tile {
    int cor;
    int tipo;
};

// Definição da struct no
struct no {
    tile_t** board;
    no_t* pai;
};

// Definição da struct no_fila
struct no_fila {

};

// Definição da struct fila
struct fila {
    no_fila_t* primeiro;
    no_fila_t* ultimo;   // Adicionei um ponteiro para o último para eficiência
    int tam;
};

tile_t** init_prob1(){

    tile_t** board = calloc(3, sizeof(tile_t*));
    for(int i = 0; i<4; i++){
        board[i] = calloc(6, sizeof(tile_t));
    }

    board[0][0].cor = 2;
    board[0][0].tipo = 3;
    board[0][1].cor = 1;
    board[0][1].tipo = 4;
    board[0][2].cor = 1;
    board[0][2].tipo = 4;
    board[0][3].cor = 1;
    board[0][3].tipo = 4;
    board[0][4].cor = 1;
    board[0][4].tipo = 4;
    board[0][5].cor = 1;
    board[0][5].tipo = 2;

    board[1][0].cor = 1;
    board[1][0].tipo = 3;
    board[1][1].cor = 1;
    board[1][1].tipo = 3;
    board[1][2].cor = 1;
    board[1][2].tipo = 3;
    board[1][3].cor = 1;
    board[1][3].tipo = 3;
    board[1][4].cor = 1;
    board[1][4].tipo = 2;
    board[1][5].cor = 1;
    board[1][5].tipo = 2;

    board[2][0].cor = 0;
    board[2][0].tipo = 0;
    board[2][1].cor = 0;
    board[2][1].tipo = 0;
    board[2][2].cor = 0;
    board[2][2].tipo = 0;
    board[2][3].cor = 0;
    board[2][3].tipo = 0;
    board[2][4].cor = 1;
    board[2][4].tipo = 2;
    board[2][5].cor = 0;
    board[2][5].tipo = 0;

    return board;
}

tile_t** init_prob2(){
    
    tile_t** board = calloc(4, sizeof(tile_t*));
    for(int i = 0; i<5; i++){
        board[i] = calloc(4, sizeof(tile_t));
    }

    board[0][0].cor = 1;
    board[0][0].tipo = 3;
    board[0][1].cor = 1;
    board[0][1].tipo = 3;
    board[0][2].cor = 1;
    board[0][2].tipo = 3;
    board[0][3].cor = 1;
    board[0][3].tipo = 3;
    board[0][4].cor = 1;
    board[0][4].tipo = 3;

    board[1][0].cor = 1;
    board[1][0].tipo = 4;
    board[1][1].cor = 1;
    board[1][1].tipo = 4;
    board[1][2].cor = 1;
    board[1][2].tipo = 4;
    board[1][3].cor = 1;
    board[1][3].tipo = 4;
    board[1][4].cor = 1;
    board[1][4].tipo = 4;

    board[2][0].cor = 1;
    board[2][0].tipo = 2;
    board[2][1].cor = 1;
    board[2][1].tipo = 2;
    board[2][2].cor = 1;
    board[2][2].tipo = 2;
    board[2][3].cor = 1;
    board[2][3].tipo = 2;
    board[2][4].cor = 1;
    board[2][4].tipo = 2;

    board[3][0].cor = 1;
    board[3][0].tipo = 2;
    board[3][1].cor = 1;
    board[3][1].tipo = 2;
    board[3][2].cor = 1;
    board[3][2].tipo = 2;
    board[3][3].cor = 1;
    board[3][3].tipo = 2;
    board[3][4].cor = 1;
    board[3][4].tipo = 2;

    return board;
}

fila_t* init_fila(){

    fila_t* A = calloc(1, sizeof(fila_t));
    A->primeiro = NULL;
    A->tam = 0;

    return A;
}

no_t* cria_no(tile_t** board, no_t* pai){

    no_t* node = calloc(1, sizeof(no_t));
    node->board = board;
    node->pai = pai;

    return node;
}

void insere_no(fila_t* ){
    
}