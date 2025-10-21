#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
/*
    COR:
        0 OUTRO
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
        7 OBSTACULO
*/

void print_matriz(tile_t** board, int lin, int col){
    for(int i=0; i<lin; i++){
        for(int j=0;j<col;j++){
            printf("%d ", board[i][j].peca);
        }
        printf("\n");
    }
    printf("\n");
}

int calc_dist(no_t* no){
    int dist = abs(no->goalX - no->posX) + abs(no->goalY - no->posY);
    return dist;
}

no_t* init_prob1(){
    no_t* no = calloc(1, sizeof(no_t));
    int linhas = 3;
    int colunas = 6;

    tile_t** board = calloc(linhas, sizeof(tile_t*));
    for (int i = 0; i<linhas; i++){
        board[i] = calloc(colunas, sizeof(tile_t));
    }

    board[0][0].cor = 2;
    board[0][0].peca = 3;
    board[0][1].cor = 1;
    board[0][1].peca = 4;
    board[0][2].cor = 1;
    board[0][2].peca = 4;
    board[0][3].cor = 1;
    board[0][3].peca = 4;
    board[0][4].cor = 1;
    board[0][4].peca = 4;
    board[0][5].cor = 1;
    board[0][5].peca = 2;

    board[1][0].cor = 1;
    board[1][0].peca = 3;
    board[1][1].cor = 1;
    board[1][1].peca = 3;
    board[1][2].cor = 1;
    board[1][2].peca = 3;
    board[1][3].cor = 1;
    board[1][3].peca = 3;
    board[1][4].cor = 1;
    board[1][4].peca = 2;
    board[1][5].cor = 1;
    board[1][5].peca = 2;

    board[2][0].cor = 0;
    board[2][0].peca = 7;
    board[2][1].cor = 0;
    board[2][1].peca = 7;
    board[2][2].cor = 0;
    board[2][2].peca = 7;
    board[2][3].cor = 0;
    board[2][3].peca = 7;
    board[2][4].cor = 1;
    board[2][4].peca = 2;
    board[2][5].cor = 0;
    board[2][5].peca = 0;

    no->board = board;
    no->posX = 0;
    no->posY = 0;
    no->goalX = 2;
    no->goalY = 5;
    no->distancia = calc_dist(no);
    no->custo = 0;
    no->pai = NULL;

    return no;
}

tile_t** copia_board(tile_t** board, int lin, int col){
    tile_t** nova_board = calloc(lin, sizeof(tile_t*));
    for(int i=0; i<lin; i++){
        nova_board[i] = calloc(col, sizeof(tile_t));
        for(int j=0; j<col; j++){
            nova_board[i][j] = board[i][j];
        }
    }
    return nova_board;
}

no_t* cria_no(tile_t** board, no_t* pai){
    no_t* novo_no = calloc(1, sizeof(no_t));
    novo_no->board = board;
    novo_no->pai = pai;
    novo_no->goalX = pai->goalX;
    novo_no->goalY = pai->goalY;
    novo_no->posX = pai->posX;
    novo_no->posY = pai->posY;
    novo_no->custo = pai->custo + 1;
    return novo_no;
}

elemento_t* cria_elemento(no_t* no){
    elemento_t* novo_elemento = calloc(1, sizeof(elemento_t));
    novo_elemento->no = no;
    novo_elemento->f = no->custo + no->distancia;

    return novo_elemento;
}

fila_t* cria_fila(){
    fila_t* fila = malloc(sizeof(fila_t));
    fila->tam = 0;
    fila->comeco = NULL;
    fila->fim = NULL;
    return fila;
}

void inserir_fila(fila_t* fila, no_t* no){
    elemento_t* novo = cria_elemento(no);

    if (fila->comeco == NULL){
        fila->comeco = novo;
        fila->fim = novo;
        fila->tam = 1;
        novo->anterior = NULL;
        novo->prox = NULL;
        return;
    }

    elemento_t* atual = fila->comeco;
    while((atual != NULL)&&(atual->f < novo->f)){
        atual = atual->prox;
    }

    if(atual == fila->comeco){
        novo->prox = atual;
        atual->anterior = novo;
        novo->anterior = NULL;
        fila->comeco = novo;
        fila->tam++;
        return;
    }
    
    if (atual != NULL){
        novo->anterior = atual->anterior;
        novo->prox = atual;
        atual->anterior->prox = novo;
        atual->anterior = novo;
        fila->tam++;
        return;
    }

    novo->anterior = fila->fim;
    novo->prox = NULL;
    fila->fim->prox = novo;
    fila->fim = novo;
    fila->tam++;    
}

elemento_t* remover_primeiro(fila_t* fila){
    if (!fila || !fila->comeco) return NULL;
    
    elemento_t* removido = fila->comeco;
    fila->comeco = removido->prox;
    
    if (fila->comeco != NULL) {
        fila->comeco->anterior = NULL;
    } else {
        fila->fim = NULL;
    }
    
    fila->tam--;
    return removido;
}

int caminho_livre(tile_t** board, int fromX, int fromY, int toX, int toY) {
    int dx = fromX - toX;
    int dy = fromY - toY;

    if(dx == 0){
        for(int i=MIN(fromY, toY)+1; i<MAX(fromY, toY); i++){
            //printf("fromY:%d fromX:%d toY:%d toX:%d board:%d\n", fromY,fromX,toY,toX,board[i][fromX].peca);
            if(board[i][fromX].peca != 0) return 0;
        }
    }else if(dy == 0){
        for(int j=MIN(fromX, toX)+1; j<MAX(fromX, toX); j++){
            //printf("fromY:%d fromX:%d toY:%d toX:%d board:%d\n", fromY,fromX,toY,toX,board[fromY][j].peca);
            if(board[fromY][j].peca != 0) return 0;
        }
    }else{
        if((dx<0) && (dy<0)){
            for(int k=1; k<abs(dx); k++){
                if(board[fromY+k][fromX+k].peca != 0) return 0;
            }
        }else if((dx<0) && (dy>0)){
            for(int k=1; k<abs(dx); k++){
                if(board[fromY+k][fromX-k].peca != 0) return 0;
            }
        }else if((dx>0) && (dy<0)){
            for(int k=1; k<abs(dx); k++){
                if(board[fromY-k][fromX+k].peca != 0) return 0;
            }
        }else{
            for(int k=1; k<abs(dx); k++){
                if(board[fromY-k][fromX-k].peca != 0) return 0;
            }
        }
    }
    return 1;
}

//VERIFICAR ESSES MOVIMENTOS
int pode_mover_peca(tile_t** board, int fromX, int fromY, int toX, int toY) {
    int dx = fromX - toX;
    int dy = fromY - toY;

    // printf("cheguei?\n");

    switch (board[fromY][fromX].peca) {
        //Peao
        case 1:
            //Peça branca
            if(board[fromY][fromX].cor == 1){

            }
            //Peça preta
            else{

            }
            break;
        //Torre
        case 2:
            //printf("Torre\n");
            if((dx==0) || (dy==0)) {
                //printf("yay? dx:%d dy:%d fromX:%d toX:%d fromY:%d toY:%d\n", dx, dy, fromX, toX, fromY, toY);
                return caminho_livre(board, fromX, fromY, toX, toY);
            }
            break;
        //Cavalo
        case 3:
            if((abs(dx)==2 && abs(dy)==1) || (abs(dx)==1 && abs(dy)==2)) return 1;
            break;
        //Bispo
        case 4:
            if(abs(dx) == abs(dy)) return caminho_livre(board, fromX, fromY, toX, toY);
            break;
        //Rainha
        case 5:
            if((dx==0) || (dy==0)) return caminho_livre(board, fromX, fromY, toX, toY);
            if(abs(dx) == abs(dy)) return caminho_livre(board, fromX, fromY, toX, toY);
            break;
        //Rei
        case 6:
            //Não preciso implementar, não tem rei nas boards
            break;
        case 7:
            return 0;
        default:
            return 0;
    }

    return 0;
}


int verifica_obj(no_t* no){
    if((no->goalX == no->posX) && no->posY == no->goalY) return 1;
    return 0;
}

//ki e kj são a nova posição
void gerar_sucessor(fila_t* fila, elemento_t* elemento, int i, int j, int ki, int kj){
    no_t* novo_no = cria_no(copia_board(elemento->no->board, fila->lin, fila->col), elemento->no);
    novo_no->board[ki][kj].peca = novo_no->board[i][j].peca;
    novo_no->board[ki][kj].cor = novo_no->board[i][j].cor;
    novo_no->board[i][j].peca = 0;
    novo_no->board[i][j].cor = 0;
    if ((i == novo_no->posY) && (j == novo_no->posX)){
        novo_no->posY = ki;
        novo_no->posX = kj;
    }
    novo_no->distancia = calc_dist(novo_no);
    if(verifica_obj(novo_no)){
        //FAZ ALGO
        printf("achei\n");
        return;
    }
    inserir_fila(fila, novo_no);
}


void percorrer_mesa(fila_t* fila, elemento_t* elemento){
    for(int i=0; i<fila->lin; i++){
        for(int j=0; j<fila->col; j++){
            //Percorre board testando espaços vazios
            if (elemento->no->board[i][j].peca == 0){
                // for(int ki=0; ki<fila->lin; ki++){
                //     for(int kj=0; kj<fila->col; kj++){
                //         //ki e kj é onde a peça está originalmente
                //         if(pode_mover_peca(elemento->no->board, kj, ki, j, i)){                       
                //             no_t* novo_no = cria_no(copia_board(elemento->no->board, fila->lin, fila->col), elemento->no);
                //             novo_no->board[i][j].peca = novo_no->board[ki][kj].peca;
                //             novo_no->board[i][j].cor = novo_no->board[ki][kj].cor;
                //             novo_no->board[ki][kj].peca = 0;
                //             novo_no->board[ki][kj].cor = 0;
                //             if ((ki == novo_no->posY) && (kj == novo_no->posX)){
                //                 novo_no->posY = i;
                //                 novo_no->posX = j;
                //             }
                //             novo_no->distancia = calc_dist(novo_no);
                //             if(verifica_obj(novo_no)){
                //                 //FAZ ALGO
                //                 printf("achei\n");
                //                 return;
                //             }
                //             inserir_fila(fila, novo_no);
                //         }
                //     }
                // }
                for(int k=1; k<(1+MAX(fila->col, fila->lin)); k++){
                    //printf("i:%d j:%d k:%d\n", i, j, k);
                    for(int kj=j-k; kj<=j+k; kj++){
                        //Coisa cima
                        if((i-k>=0)&&(kj>=0)&&(kj<fila->col)){
                                //printf("%d %d %d %d\n", kj, i-k, j, i);

                            if(pode_mover_peca(elemento->no->board, kj, i-k, j, i)){
                                //printf("Achei %d %d %d %d\n", kj, i-k, j, i);
                                gerar_sucessor(fila, elemento, i-k, kj, i, j);
                            }
                        }//Coisa baixo
                        if((i+k<fila->lin)&&(kj>=0)&&(kj<fila->col)){
                            if(pode_mover_peca(elemento->no->board, kj, i+k, j, i)){
                                //printf("Achei %d %d %d %d\n", kj, i+k, j, i);
                                gerar_sucessor(fila, elemento, i+k, kj, i, j);
                            }
                        }
                    }
                    for(int ki=i-k+1; ki<i+k; ki++){
                        //Coisa esq
                        if((j-k>=0)&&(ki>=0)&&(ki<fila->lin)){
                            if(pode_mover_peca(elemento->no->board, j-k, ki, j, i)){
                                //printf("Achei %d %d %d %d\n", j-k, ki, j, i);
                                gerar_sucessor(fila, elemento, ki, j-k, i, j);
                            }
                        }//Coisa dir
                        if((j+k<fila->col)&&(ki>=0)&&(ki<fila->lin)){
                                //printf("%d %d %d %d\n", j+k, ki, j, i);

                            if(pode_mover_peca(elemento->no->board, j+k, ki, j, i)){
                                //printf("Achei %d %d %d %d\n", j+k, ki, j, i);
                                gerar_sucessor(fila, elemento, ki, j+k, i, j);
                            }
                        }
                    }
                }
            }
        }
    }
}

void a_estrela1(){
    fila_t* fila = cria_fila();
    fila->lin = 3;
    fila->col = 6;
    inserir_fila(fila, init_prob1());
    elemento_t* elemento_atual;


    while(fila->tam > 0){
        elemento_atual = remover_primeiro(fila);
        print_matriz(elemento_atual->no->board, fila->lin, fila->col);
        if(verifica_obj(elemento_atual->no)){
            //TODO
            return;
        }
        percorrer_mesa(fila, elemento_atual);
        
    }

    printf("Não foi encontrado solução\n");
}