#include <stdio.h>

#include "estrutura/caixa.h"

int lerOpcao();
int caixaValido();
int lerOpcaoCaixa(struct Caixa *caixas [], char *msg);
struct Cliente *cadastrarCliente();
void inverteEstadoCaixa(struct Caixa *caixa);
void ajusteCaixa(struct Caixa *caixas [], int opCaixa);

int main() {
    struct Caixa *caixas[NUM_CAIXAS];

    for (int i = 0; i < NUM_CAIXAS; i++) {
        caixas[i] = initCaixa(i);
    }

    int op = -1;
    int opCaixa = -1;

    while (op != 0) {
        printf("\nMENU DE OPCOES\n\n");
        printf("1 - Cadastrar cliente\n");
        printf("2 - Atender cliente\n");
        printf("3 - Abrir/Fechar caixa\n");
        printf("4 - Listar clientes em espera\n");
        printf("5 - Imprimir Status dos Caixas\n");
        printf("0 - Sair\n\n");
        printf("Opção: ");

        op = lerOpcao();
        if (op == -1) continue;

        opCaixa = -1;

        switch (op) {
        case 1:
            // Cadastrar cliente
            struct Cliente *cliente = cadastrarCliente();

            if (cliente == NULL) {
                printf("Erro ao cadastrar cliente.\n");
                continue;
            }

            opCaixa = lerOpcaoCaixa(caixas, "adicionar o cliente");
            adicionarCliente(caixas[opCaixa - 1]->fila, cliente);
            printf("Cliente cadastrado com sucesso!\n");
            break;
        case 2:
            // Atender cliente
            opCaixa = lerOpcaoCaixa(caixas, "atender o cliente");
            removerCliente(caixas[opCaixa - 1]->fila);
            break;
        case 3:
            // Abrir/Fechar caixa
            while (opCaixa == -1) {
                printf("\nEscolha o caixa para Abrir/Fechar (1 a %d): ", NUM_CAIXAS);

                opCaixa = caixaValido();
                if (opCaixa == -1) continue;
            }
            inverteEstadoCaixa(caixas[opCaixa - 1]);
            ajusteCaixa(caixas, opCaixa - 1);
            break;
        case 4:
            // Listar clientes
            for (int i = 0; i < NUM_CAIXAS; i++) {
                printf("\n[Caixa %d]\n", i + 1);
                imprimirFila(caixas[i]->fila);
            }
            break;
        case 5:
            // Imprimir status dos caixas
            printf("\n");
            for (int i = 0; i < NUM_CAIXAS; i++) {
                printf("Caixa %d: %s | %d clientes\n", i + 1,
                    caixas[i]->estado == ABERTO ? "Aberto" : "Fechado",
                    caixas[i]->fila->tamanho);
            }
            break;
        case 0:
            printf("Saindo...\n");
            break;
        default:
            printf("Opcao invalida. Tente novamente.\n");
            break;
        }
    }

    return 0;
}

int lerOpcao() {
    int op = 0;
    if (scanf("%d", &op) != 1) {
        // Limpar o buffer de entrada
        while (getchar() != '\n');
        printf("Entrada invalida. Insira um numero inteiro.\n");
        return -1;
    }
    return op;
}

int caixaValido() {
    int opCaixa = lerOpcao();
    if (opCaixa == -1) return -1;

    if (opCaixa < 1 || opCaixa > NUM_CAIXAS) {
        printf("Caixa invalido. Tente novamente.\n");
        return -1;
    }
    return opCaixa;
}

int lerOpcaoCaixa(struct Caixa *caixas [], char *msg) {
    int opCaixa = -1;
    while (opCaixa == -1) {
        printf("\nEscolha o caixa para %s (1 a %d): ", msg, NUM_CAIXAS);

        opCaixa = caixaValido();
        if (opCaixa == -1) continue;

        if (caixas[opCaixa - 1]->estado == FECHADO) {
            printf("Caixa fechado. Tente outro caixa.\n");
            opCaixa = -1;
            continue;
        }
    }
    return opCaixa;
}

struct Cliente *cadastrarCliente() {
    char nome[100];
    long int cpf;
    int prioridade;
    int itens;

    printf("Nome: ");
    scanf(" %[^\n]", nome);

    printf("CPF: ");

    if (scanf("%ld", &cpf) != 1) {
        while (getchar() != '\n');
        printf("\nEntrada invalida. Insira um numero inteiro.\n");
        return NULL;
    }

    printf("Prioridade (1 - Baixa, 2 - Media, 3 - Alta): ");
    prioridade = lerOpcao();
    if (prioridade == -1) return NULL;

    printf("Quantidade de itens: ");
    itens = lerOpcao();
    if (itens == -1) return NULL;

    return criarCliente(nome, cpf, prioridade, itens);
}

void inverteEstadoCaixa(struct Caixa *caixa) {
    if (caixa->estado == ABERTO) {
        fecharCaixa(caixa);
    } else {
        abrirCaixa(caixa);
    }
}

void ajusteCaixa(struct Caixa *caixas [], int opCaixa) {
    if (caixas[opCaixa]->estado == FECHADO) {
        if (caixas[opCaixa]->fila->tamanho > 0) {
            int idCaixa = -1;
            printf("Procurando caixa vazio\n");

            for (int i = 0; i < NUM_CAIXAS; i++) {
                if (caixas[i]->estado == ABERTO) {
                    idCaixa = i;
                    break;
                }
            }

            printf("\n");
            while (caixas[opCaixa]->fila->tamanho > 0) {
                printf("Realocando cliente...\n");
                adicionarCliente(caixas[idCaixa]->fila, obterCliente(caixas[opCaixa]->fila));
                removerCliente(caixas[opCaixa]->fila);
            }
        }
    }
}