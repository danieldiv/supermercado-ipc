#include "estrutura/filaPrioridade.h"

struct FilaPrioridade *criarFilaPrioridade() {
    struct FilaPrioridade *fila = (struct FilaPrioridade *)malloc(sizeof(struct FilaPrioridade));

    fila->inicio = NULL;
    fila->fim = NULL;
    fila->tamanho = 0;

    return fila;
}

void adicionarCliente(struct FilaPrioridade *fila, struct Cliente *cliente) {
    if (cliente->prioridade == PRIORIDADE_BAIXA || fila->tamanho == 0) {
        adicionarClienteFim(fila, cliente);
    } else {
        struct NoFila *noAtual = fila->inicio;

        while (noAtual != NULL && noAtual->cliente->prioridade >= cliente->prioridade) {
            noAtual = noAtual->prox;
        }

        if (noAtual == NULL) {
            adicionarClienteFim(fila, cliente);
        } else if (noAtual->ant == NULL) {
            adicionarClienteInicio(fila, cliente);
        } else {
            struct NoFila *novoNo = (struct NoFila *)malloc(sizeof(struct NoFila));

            novoNo->cliente = cliente;
            novoNo->prox = noAtual;
            novoNo->ant = noAtual->ant;

            noAtual->ant->prox = novoNo;
            noAtual->ant = novoNo;
        }
    }
    fila->tamanho++;
}

void adicionarClienteFim(struct FilaPrioridade *fila, struct Cliente *cliente) {
    struct NoFila *novoNo = (struct NoFila *)malloc(sizeof(struct NoFila));

    novoNo->cliente = cliente;
    novoNo->prox = NULL;
    novoNo->ant = fila->fim;

    if (fila->fim != NULL) {
        fila->fim->prox = novoNo;
    } else {
        fila->inicio = novoNo;
    }
    fila->fim = novoNo;
}

void adicionarClienteInicio(struct FilaPrioridade *fila, struct Cliente *cliente) {
    struct NoFila *novoNo = (struct NoFila *)malloc(sizeof(struct NoFila));

    novoNo->cliente = cliente;
    novoNo->prox = fila->inicio;
    novoNo->ant = NULL;

    if (fila->inicio != NULL) {
        fila->inicio->ant = novoNo;
    } else {
        fila->fim = novoNo;
    }
    fila->inicio = novoNo;
}

void removerCliente(struct FilaPrioridade *fila) {
    if (fila->tamanho == 0) {
        printf("\nFila vazia!\n");
        return;
    }

    struct NoFila *noRemovido = fila->inicio;

    if (fila->tamanho == 1) {
        fila->inicio = NULL;
        fila->fim = NULL;
    } else {
        fila->inicio = noRemovido->prox;
        fila->inicio->ant = NULL;
    }

    free(noRemovido);
    fila->tamanho--;
}

struct Cliente *obterCliente(struct FilaPrioridade *fila) {
    if (fila->tamanho == 0) {
        printf("\nFila vazia!\n");
        return NULL;
    }

    return fila->inicio->cliente;
}

void imprimirFila(struct FilaPrioridade *fila) {
    struct NoFila *noAtual = fila->inicio;

    if (fila->tamanho == 0) {
        printf("\nFila vazia!\n");
        return;
    }

    printf("\nCPF | Prioridade | Itens - Nome\n\n");

    while (noAtual != NULL) {
        printCliente(noAtual->cliente);
        noAtual = noAtual->prox;
    }
}