#include "estrutura/cliente.h"

struct Cliente *criarCliente(char *nome, long int CPF, int prioridade, int itens) {
    struct Cliente *novoCliente = (struct Cliente *)malloc(sizeof(struct Cliente));

    strcpy(novoCliente->nome, nome);

    if (CPF < 0) {
        printf("\nCPF invalido\n");
        return NULL;
    }

    if (prioridade < 0 || prioridade > 3) {
        printf("\nPrioridade invalida\n");
        return NULL;
    }

    if (itens <= 0) {
        printf("\nQuantidade de itens invalida\n");
        return NULL;
    }

    novoCliente->CPF = CPF;
    novoCliente->prioridade = prioridade;
    novoCliente->itens = itens;

    return novoCliente;
}

void printCliente(struct Cliente *cliente) {
    printf("%ld | %d | %d - %s\n",
        cliente->CPF,
        cliente->prioridade,
        cliente->itens,
        cliente->nome);
}
