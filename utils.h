#include <stdlib.h>
#include <stdio.h>

typedef struct {
    int tipo;
    int cor;
} peca;

typedef struct no{
    int x, y, dist;
    struct no* pai;
    struct no* prox;
} no;

typedef struct fila_prioridade{
    no* inicio;
    int tam;
} fila_prioridade;

peca** aloca_matriz(int lar, int alt);

void ini_mesa(peca** board);

void print_board(peca** board, int lar, int alt);