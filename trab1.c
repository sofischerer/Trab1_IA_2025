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

void montar_prob1(peca** board){

    board[0][0].tipo = 3;
    board[0][0].cor = 1;

    board[0][1].tipo = 4;
    board[0][1].cor = 2;
    board[0][2].tipo = 4;
    board[0][2].cor = 2;
    board[0][3].tipo = 4;
    board[0][3].cor = 2;
    board[0][4].tipo = 4;
    board[0][4].cor = 2;

    board[0][5].tipo = 2;
    board[0][5].cor = 2;

    board[1][0].tipo = 3;
    board[1][0].cor = 2;
    board[1][1].tipo = 3;
    board[1][1].cor = 2;
    board[1][2].tipo = 3;
    board[1][2].cor = 2;
    board[1][3].tipo = 3;
    board[1][3].cor = 2;

    board[1][4].tipo = 2;
    board[1][4].cor = 2;
    board[1][5].tipo = 2;
    board[1][5].cor = 2;

    board[2][4].tipo = 2;
    board[2][4].cor = 2;
}

void montar_prob2(peca** board){

    for (int j=0; j<4; j++){
        board[0][j].cor  = 2;
        board[0][j].tipo = 3;
    }
    for (int j=0; j<4; j++){
        board[1][j].cor  = 2;
        board[1][j].tipo = 4;
    }
    for (int j=0; j<4; j++){
        board[2][j].cor  = 2;
        board[2][j].tipo = 2;
    }

    board[3][3].tipo = 1;
    board[3][3].cor = 1;
}

int distancia(int posX, int posY, int goalX, int goalY){

    int distancia = 0;
    distancia += abs(posX-goalX);
    distancia += abs(posY-goalY);

    return distancia;
}

fila_prioridade* cria_fila(){
    
    fila_prioridade* lista =  calloc(1, sizeof(fila_prioridade));
    lista->inicio = NULL;
    lista->tam = 0;

    return lista;
}

void inserir_fila(fila_prioridade* fila, no* node){

    no* pos = fila->inicio;
    if (pos == NULL){
        pos->prox = node;
        node->pai = pos;
        fila->tam++;
        return;
    }
    while(pos->prox->dist < node->dist){
        pos = pos->prox;
    }
    node->prox = pos->prox;
    node->pai = pos;
    pos->prox->pai = node;
    pos->prox = node;
    fila->tam++;
    return;
}

void remover_fila(fila_prioridade* fila, no* node){

    node->pai->prox = node->prox;
    node->prox->pai = node->pai;
    fila->tam--;
    free(node);
    return;
}

void a_estrela(){

    fila_prioridade* fila = cria_fila();
    fila_prioridade* ordem = cria_fila();

    return;
}