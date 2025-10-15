#include <stdlib.h>

int linhas = 0;
int colunas = 0;
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

typedef struct tile_t{
    int tipo;
    int cor;
}tile_t;

typedef struct no_t{
    tile_t** board;
    int posX, posY;
    int goalX, goalY;
    struct no_t* pai;
}no_t;  

typedef struct elemento_t{
    int dist;
    no_t* board;
    struct elemento_t* prox;
}elemento_t;

typedef struct fila_t{
    elemento_t* primeiro;
    int tam;
}fila_t;

no_t* init_prob1(){
    linhas = 3;
    colunas = 6;
    no_t* no = calloc(1, sizeof(no_t));
    tile_t** board = calloc(linhas, sizeof(tile_t*));
    for (int i = 0; i<linhas; i++){
        board[i] = calloc(colunas, sizeof(tile_t));
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

    no->board = board;
    no->posX = 0;
    no->posY = 0;
    no->goalX = 2;
    no->goalY = 5;
    no->pai = NULL;

    return no;
}

int calc_dist(no_t* no){
    int dist = 0;
    dist += abs(no->goalX-no->posX);
    dist += abs(no->goalY-no->posY);
    return dist;
}

tile_t** atualiza_board(tile_t** board, int old_X, int old_Y, int X, int Y){

    tile_t** new_board = calloc(linhas, sizeof(tile_t*));
    for (int i = 0; i<linhas; i++){
        board[i] = calloc(colunas, sizeof(tile_t));
    }
    *new_board = *board;
    new_board[X][Y].tipo = board[old_X][old_Y].tipo;
    new_board[X][Y].cor = board[old_X][old_Y].cor;
    new_board[old_X][old_Y].tipo = 0;
    new_board[old_X][old_Y].cor = 0;
    return new_board;
}

no_t* cria_no(tile_t** ini, no_t* pai){
    no_t* no = calloc(1, sizeof(no_t));
    no->board = ini;
    no->pai = pai;
    return no;
}

elemento_t* cria_elemento(no_t* no){
    elemento_t* elemento = calloc(1, sizeof(elemento_t));
    elemento->board = no;
    elemento->dist = calc_dist(no);
    return elemento;
}

fila_t* cria_fila() {  
    fila_t* fila = calloc(1, sizeof(fila_t));
    fila->primeiro = NULL;
    fila->tam = 0;
    return fila;
}

void inserir_fila(fila_t* fila, elemento_t* elemento){

    if (fila->primeiro == NULL) {
        fila->primeiro = elemento;
        fila->tam = 1;
        return;
    }
    elemento_t* pos = fila->primeiro;
    elemento_t* anterior = NULL;

    while (pos != NULL && pos->dist < elemento->dist) {
        anterior = pos;
        pos = pos->prox;
    }
    if (anterior == NULL) {
        elemento->prox = fila->primeiro;
        fila->primeiro = elemento;
    }

    else {
        anterior->prox = elemento;
        elemento->prox = pos;
    }    
    fila->tam++;
    
}

void remove_fila(fila_t* fila, elemento_t* elemento){

    if (fila == NULL || fila->primeiro == NULL) {
        return;
    }
    
    elemento_t* removido = fila->primeiro;
    fila->primeiro = removido->prox;  // Novo primeiro é o próximo
    fila->tam--;
    
    free(removido);
}

int fila_vazia(fila_t* fila) {
    return (fila->primeiro == NULL);
}

int eh_objetivo(no_t* no) {
    return (no->posX == no->goalX && no->posY == no->goalY);
}

int movimento_valido(no_t* no, int old_X, int old_Y, int X, int Y){
    if ((X<0) || (X>=colunas)) return 0;
    if ((Y<0) || (Y>=linhas)) return 0;
    if (no->board[X][Y].cor == no->board[old_X][old_Y].cor) return 0;
    return 1;
}

fila_t* gera_movimentos_peao(no_t* no, int X, int Y, int is_obj){
    
}

fila_t* gera_movimentos_torre(no_t* no, int X, int Y, int is_obj){
    
}

fila_t* gera_movimentos_cavalo(no_t* no, int X, int Y, int is_obj){
    fila_t* sucessores = cria_fila();
    int movimentos[8][2] = {{-2,-1}, {-2,1}, {-1,-2}, {-1, 2},
                            {1,-2} , {1,2} , {2,-1} , {2, 1}};

    for (int i = 0; i < 8; i++) {
        int novo_x = X + movimentos[i][0];
        int novo_y = Y + movimentos[i][1];
        if (movimento_valido(no, X, Y, novo_x, novo_y)) {
            tile_t** new_board = atualiza_board(no->board , X, Y, novo_x, novo_y);
            no_t* novo_estado = cria_no(new_board, no);
            if (is_obj){
                novo_estado->posX = novo_x;
                novo_estado->posY = novo_y;
            }
            elemento_t* novo_elemento = cria_elemento(novo_estado);
            inserir_fila(sucessores, novo_elemento);
        }
    }
    return sucessores;
}

fila_t* gera_movimentos_bispo(no_t* no, int X, int Y, int is_obj){
    
}

fila_t* gera_movimentos_rainha(no_t* no, int X, int Y, int is_obj){
    
}

fila_t* gera_movimentos_rei(no_t* no, int X, int Y, int is_obj){
    
}

fila_t* gerar_sucessor(no_t* no, int X, int Y){
    fila_t* sucessores = NULL;
    int is_obj = 0;
    if (no->posX == X && no->posY == Y )is_obj = 1;

    int tipo_peca = no->board[X][Y].tipo;
    
    // SWITCH para diferentes tipos de peça
    switch(tipo_peca) {
        case 3:  // CAVALO (tipo 3)
            sucessores = gera_movimentos_cavalo(no, X, Y, is_obj);
            break;
            
        case 2:  // TORRE (tipo 2)  
            sucessores = gera_movimentos_torre(no, X, Y, is_obj);
            break;
            
        case 1:  // PEAO (tipo 1)
            sucessores = gera_movimentos_peao(no, X, Y, is_obj);
            break;
            
        case 4:  // BISPO (tipo 4)
            sucessores = gera_movimentos_bispo(no, X, Y, is_obj);
            break;
            
        case 5:  // RAINHA (tipo 5)
            sucessores = gera_movimentos_rainha(no, X, Y, is_obj);
            break;
            
        case 6:  // REI (tipo 6)
            sucessores = gera_movimentos_rei(no, X, Y, is_obj);
            break;
            
        default:  // Para tipos desconhecidos ou VAZIO (0)
            sucessores = NULL;
            break;
    }
    
    return sucessores;


}