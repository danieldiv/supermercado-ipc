#ifndef CLIENTE_C
#define CLIENTE_C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PRIORIDADE_ALTA 3
#define PRIORIDADE_MEDIA 2
#define PRIORIDADE_BAIXA 1

struct Cliente {
    char nome[100];
    long int CPF; // 11 dígitos
    int prioridade;
    int itens;
};

struct Cliente *criarCliente(char *nome, long int CPF, int prioridade, int itens);
void printCliente(struct Cliente *cliente);

#endif