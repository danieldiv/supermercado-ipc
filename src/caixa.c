#include "estrutura/caixa.h"

int caixasAbertos = 0;


struct Caixa *initCaixa(int identificacao) {
    struct Caixa *caixa = (struct Caixa *)malloc(sizeof(struct Caixa));

    caixa->identificacao = identificacao;
    caixa->estado = ABERTO;
    caixasAbertos = NUM_CAIXAS;

    caixa->fila = criarFilaPrioridade();

    return caixa;
}

void abrirCaixa(struct Caixa *caixa) {
    if (caixa->estado == FECHADO) {
        caixa->estado = ABERTO;
        caixasAbertos++;
        printf("Caixa aberto com sucesso!\n");
    }
}

void fecharCaixa(struct Caixa *caixa) {
    if (caixa->estado == ABERTO) {
        if (caixasAbertos == 1) {
            printf("Nao eh possivel fechar o caixa, pois eh o unico aberto\n");
            return;
        }
        caixa->estado = FECHADO;
        caixasAbertos--;
        printf("Caixa fechado com sucesso!\n");
    }
}