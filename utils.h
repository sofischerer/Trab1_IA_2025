#ifndef JOGO_H
#define JOGO_H

#include <stdio.h>
#include <stdlib.h>

// Macros úteis
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

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

// Structs
typedef struct {
    int cor;
    int peca; 
} tile_t;

typedef struct no_t {
    tile_t** board;
    struct no_t* pai;
    int custo;
    int distancia;
    int posX, posY;    
    int goalX, goalY;
} no_t;

typedef struct elemento_t {
    no_t* no;
    int f;
    struct elemento_t* prox;
    struct elemento_t* anterior;
} elemento_t;

typedef struct fila_t {
    elemento_t* comeco;  
    elemento_t* fim;
    int tam;
    int lin, col;
} fila_t;

// Protótipos das funções

int calc_dist(no_t* no);

no_t* init_prob1();

tile_t** copia_board(tile_t** board, int lin, int col);

no_t* cria_no(tile_t** board, no_t* pai);

elemento_t* cria_elemento(no_t* no);

fila_t* cria_fila();

void inserir_fila(fila_t* fila, no_t* no);

elemento_t* remover_primeiro(fila_t* fila);

int caminho_livre(tile_t** board, int fromX, int fromY, int toX, int toY);

int pode_mover_peca(tile_t** board, int fromX, int fromY, int toX, int toY);

int verifica_obj(no_t* no);

void gerar_sucessor(fila_t* fila, elemento_t* elemento, int i, int j, int ki, int kj);

void percorrer_mesa(fila_t* fila, elemento_t* elemento);

void a_estrela1();

#endif // JOGO_H
