#include "trab1.h"


int main(){

    peca** board = aloca_matriz(6, 3);
    montar_prob1(board);
    print_board(board, 6, 3);
    free(board);
    printf("\n\n");

    board = aloca_matriz(4, 4);
    montar_prob2(board);
    print_board(board, 4, 4);

    a_estrela();
}