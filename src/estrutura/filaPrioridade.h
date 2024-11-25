#ifndef FILA_PRIORIDADE_C
#define FILA_PRIORIDADE_C

#include "cliente.h"

struct NoFila {
    struct Cliente *cliente;
    struct NoFila *prox;
    struct NoFila *ant;
};

/**
 * A fila de prioridade possui uma lista encadeada de clientes
 */
struct FilaPrioridade {
    struct NoFila *inicio;
    struct NoFila *fim;

    int tamanho;
};

struct FilaPrioridade *criarFilaPrioridade();

void adicionarClienteFim(struct FilaPrioridade *fila, struct Cliente *cliente);
void adicionarClienteInicio(struct FilaPrioridade *fila, struct Cliente *cliente);
void adicionarCliente(struct FilaPrioridade *fila, struct Cliente *cliente);

void removerCliente(struct FilaPrioridade *fila);
struct Cliente *obterCliente(struct FilaPrioridade *fila);

void imprimirFila(struct FilaPrioridade *fila);

#endif