#include <stdlib.h>
#include <stdio.h>
#include "utils.h"


void montar_prob1(peca** board);

void montar_prob2(peca** board);

int distancia(int posX, int posY, int goalX, int goalY);

fila_prioridade* cria_fila();

void inserir_fila(fila_prioridade* fila, no* node);

void remover_fila(fila_prioridade* fila, no* node);

void a_estrela();