#include "libestruturas.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Inicializações
void initPilha(Pilha* p) {
    p->topo = NULL;
}

void initFila(Fila* f) {
    f->frente = NULL;
    f->tras = NULL;
}

int pilhaVazia(Pilha* p) {
    return p->topo == NULL;
}

int filaVazia(Fila* f) {
    return f->frente == NULL;
}

// Pilha
void push(Pilha* p, int v) {
    NodeP* novo = malloc(sizeof(NodeP));
    novo->valor = v;
    novo->prox = p->topo;
    p->topo = novo;
}

int pop(Pilha* p) {
    if (pilhaVazia(p)) return 0;
    NodeP* temp = p->topo;
    int val = temp->valor;
    p->topo = temp->prox;
    free(temp);
    return val;
}

int top(Pilha* p) {
    if (pilhaVazia(p)) return 0;
    return p->topo->valor;
}

// Imprime pilha no formato [20, 10]
void printPilha(Pilha* p, char* buffer) {
    buffer[0] = '\0';
    strcat(buffer, "[");

    NodeP* atual = p->topo;
    while (atual) {
        char aux[20];
        sprintf(aux, "%d", atual->valor);
        strcat(buffer, aux);

        if (atual->prox) strcat(buffer, ", ");
        atual = atual->prox;
    }
    strcat(buffer, "]");
}

// Fila
void enqueue(Fila* f, int v) {
    NodeF* novo = malloc(sizeof(NodeF));
    novo->valor = v;
    novo->prox = NULL;

    if (filaVazia(f)) {
        f->frente = novo;
    } else {
        f->tras->prox = novo;
    }
    f->tras = novo;
}

int dequeue(Fila* f) {
    if (filaVazia(f)) return 0;
    NodeF* temp = f->frente;
    int val = temp->valor;
    f->frente = temp->prox;
    if (!f->frente) f->tras = NULL;
    free(temp);
    return val;
}

void visualizarFila(Fila* f, char* buffer) {
    buffer[0] = '\0';
    strcat(buffer, "[");

    NodeF* atual = f->frente;
    while (atual) {
        char aux[20];
        sprintf(aux, "%d", atual->valor);
        strcat(buffer, aux);

        if (atual->prox) strcat(buffer, ", ");
        atual = atual->prox;
    }
    strcat(buffer, "]");
}
