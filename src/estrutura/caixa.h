#ifndef CAIXA_C
#define CAIXA_C

#include "filaPrioridade.h"

#define NUM_CAIXAS 5
#define FECHADO 0
#define ABERTO 1

/**
 * Cada caixa possui a sua fila
 */
struct Caixa {
    struct FilaPrioridade *fila;

    int identificacao;
    int estado;
};

struct Caixa *initCaixa(int identificacao);

void abrirCaixa(struct Caixa *caixa);
void fecharCaixa(struct Caixa *caixa);

#endif