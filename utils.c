#include <stdio.h>
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

typedef struct {
    int cor;
    int peca; 
} tile_t;

typedef struct no_t {
    tile_t** board;
    struct no_t* pai;
    int linhas, colunas;
    int custo;         
    int distancia;    
    int f;             
    int posX, posY;    
    int goalX, goalY;
} no_t;

typedef struct fila_t {
    no_t** elementos;  
    int tam;
    int capacidade;
} fila_t;

no_t* init_prob1(){
    no_t* no = calloc(1, sizeof(no_t));
    no->linhas = 3;
    no->colunas = 6;

    tile_t** board = calloc(no->linhas, sizeof(tile_t*));
    for (int i = 0; i<no->linhas; i++){
        board[i] = calloc(no->colunas, sizeof(tile_t));
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
    board[2][0].peca = 0;
    board[2][1].cor = 0;
    board[2][1].peca = 0;
    board[2][2].cor = 0;
    board[2][2].peca = 0;
    board[2][3].cor = 0;
    board[2][3].peca = 0;
    board[2][4].cor = 1;
    board[2][4].peca = 2;
    board[2][5].cor = 0;
    board[2][5].peca = 0;

    no->board = board;
    no->posX = 0;
    no->posY = 0;
    no->goalX = 2;
    no->goalY = 5;
    no->pai = NULL;

    return no;
}

int calc_dist(no_t* no){
    int dist = abs(no->goalX - no->posX) + abs(no->goalY - no->posY);
    return dist;
}

fila_t* criar_fila(int capacidade) {
    fila_t* fila = malloc(sizeof(fila_t));
    fila->elementos = malloc(sizeof(no_t*) * capacidade);
    fila->tam = 0;
    fila->capacidade = capacidade;
    return fila;
}

int pai(int i) { return (i - 1) / 2; }
int esquerda(int i) { return 2 * i + 1; }
int direita(int i) { return 2 * i + 2; }

void trocar(no_t** a, no_t** b) {
    no_t* temp = *a;
    *a = *b;
    *b = temp;
}

void inserir_fila(fila_t* fila, no_t* no) {
    // Se não tem mais espaço, dobra a capacidade
    if (fila->tam >= fila->capacidade) {
        fila->capacidade *= 2;
        fila->elementos = realloc(fila->elementos, sizeof(no_t*) * fila->capacidade);
        if (!fila->elementos) {
            perror("Erro realloc");
            exit(EXIT_FAILURE);
        }
    }

    // Insere o nó no final do array
    int i = fila->tam++;
    fila->elementos[i] = no;

    // Sobe o nó para manter propriedade do min-heap (baseada em f)
    while (i != 0 && fila->elementos[pai(i)]->f > fila->elementos[i]->f) {
        trocar(&fila->elementos[i], &fila->elementos[pai(i)]);
        i = pai(i);
    }
}

no_t* remover_menor(fila_t* fila) {
    if (fila->tam == 0) return NULL;

    no_t* menor = fila->elementos[0];
    fila->elementos[0] = fila->elementos[--fila->tam];

    int i = 0;
    while (1) {
        int e = esquerda(i);
        int d = direita(i);
        int menorIndice = i;

        if (e < fila->tam && fila->elementos[e]->f < fila->elementos[menorIndice]->f)
            menorIndice = e;
        if (d < fila->tam && fila->elementos[d]->f < fila->elementos[menorIndice]->f)
            menorIndice = d;

        if (menorIndice == i) break;

        trocar(&fila->elementos[i], &fila->elementos[menorIndice]);
        i = menorIndice;
    }

    return menor;
}

tile_t** copiar_tabuleiro(tile_t** board, int linhas, int colunas){
    
    tile_t** novo = calloc(linhas, sizeof(tile_t*));
    for(int i=0; i<linhas; i++){
        novo[i] = calloc(colunas, sizeof(tile_t));
        for(int j=0; j<colunas; j++){
            novo[i][j].cor = board[i][j].cor;
            novo[i][j].peca = board[i][j].peca;
        }
    }

    return novo;
}

no_t* criar_no(tile_t** board, int posX, int posY, int goalX, int goalY, int custo, int linhas, int colunas, no_t* pai){
    
    no_t* no = calloc(1, sizeof(no_t));
    no->posX = posX;
    no->posY = posY;
    no->goalX = goalX;
    no->goalY = goalY;
    no->linhas = linhas;
    no->colunas = colunas;
    no->pai = pai;
    no->custo = custo;
    no->distancia = calc_dist(no);
    no->f = no->custo + no->distancia;
    no->board = copiar_tabuleiro(board, linhas, colunas);

    return no;
}

int caminho_livre(tile_t** board, int fromX, int fromY, int toX, int toY) {
    int dx = (toX - fromX) == 0 ? 0 : (toX - fromX) / abs(toX - fromX);
    int dy = (toY - fromY) == 0 ? 0 : (toY - fromY) / abs(toY - fromY);

    int x = fromX + dx;
    int y = fromY + dy;

    while (x != toX || y != toY) {
        if (board[x][y].peca != 0)
            return 0; // obstáculo no caminho
        x += dx;
        y += dy;
    }

    return 1; // caminho livre
}


int pode_peca_mover(tile_t** board, int fromX, int fromY, int toX, int toY, tile_t peca) {
    int dx = toX - fromX;
    int dy = toY - fromY;

    switch (peca.peca) {
        case 1: // peão
            if (peca.cor == 1) { // branco
                return (dx == -1 && dy == 0); // anda uma casa para cima
            } else if (peca.cor == 2) { // preto
                return (dx == 1 && dy == 0); // anda uma casa para baixo
            }
            break;

        case 2: // torre
            return (dx == 0 || dy == 0) && caminho_livre(board, fromX, fromY, toX, toY);

        case 3: // cavalo
            return (abs(dx) == 2 && abs(dy) == 1) || (abs(dx) == 1 && abs(dy) == 2);

        case 4: // bispo
            return (abs(dx) == abs(dy)) && caminho_livre(board, fromX, fromY, toX, toY);

        case 5: // rainha
            return ((abs(dx) == abs(dy)) || (dx == 0 || dy == 0)) && caminho_livre(board, fromX, fromY, toX, toY);

        case 6: // rei
            return (abs(dx) <= 1 && abs(dy) <= 1);

        default:
            return 0;
    }

    return 0;
}


void gerar_sucessor(no_t* atual, fila_t* fila){

    for(int x=0;x<atual->linhas; x++){
        for(int y=0; y<atual->colunas; y++){
            if(atual->board[x][y].cor == 0){

                // Verificar as 8 casas ao redor
                for (int dx = -1; dx <= 1; dx++) {
                    for (int dy = -1; dy <= 1; dy++) {
                        if (dx == 0 && dy == 0) continue; // Ignora a própria casa

                        int nx = x + dx;
                        int ny = y + dy;

                        if (nx >= 0 && nx < atual->linhas && ny >= 0 && ny < atual->colunas) {
                            tile_t peca_vizinha = atual->board[nx][ny];
                            if (peca_vizinha.peca != 0) {
                                if (pode_peca_mover(atual->board, nx, ny, x, y, peca_vizinha)){

                                    tile_t** novo_tabuleiro = copiar_tabuleiro(atual->board, atual->linhas, atual->colunas);

                                    if ((nx == atual->posX) && (ny == atual->posY)){
                                        novo_tabuleiro[x][y] = novo_tabuleiro[nx][ny];
                                        novo_tabuleiro[nx][ny].peca = 0;
                                        novo_tabuleiro[nx][ny].cor = 0;
                                        no_t* novo = criar_no(novo_tabuleiro, nx, ny, atual->goalX, atual->goalY, atual->custo + 1, atual->linhas, atual->colunas, atual);
                                        inserir_fila(fila, novo);
                                    }else{
                                        novo_tabuleiro[x][y] = novo_tabuleiro[nx][ny];
                                        novo_tabuleiro[nx][ny].peca = 0;
                                        novo_tabuleiro[nx][ny].cor = 0;
                                        no_t* novo = criar_no(novo_tabuleiro, x, y, atual->goalX, atual->goalY, atual->custo + 1, atual->linhas, atual->colunas, atual);
                                        inserir_fila(fila, novo);}
                                }
                                
                            }
                        }
                    }
                }
            }
        }
    }
}

int verifica_obj(no_t* no){
    if((no->goalX == no->posX) && no->posY == no->goalY) return 1;
    return 0;
}

no_t* A_estrela1(tile_t** board) {
    fila_t* fila = criar_fila(100);
    no_t* no_inicial = criar_no(board, 0, 0, 2, 5, 0, 3, 6, NULL);
    inserir_fila(fila, no_inicial);

    while (fila->tam > 0) {
        no_t* no_atual = remover_menor(fila); // pega o nó com menor f

        if (verifica_obj(no_atual)) {
            return no_atual;        }

        gerar_sucessor(no_atual, fila); 
    }

    return NULL;
}