#ifndef LIBESTRUTURAS_H
#define LIBESTRUTURAS_H

typedef struct NodeP {
    int valor;
    struct NodeP* prox;
} NodeP;

typedef struct {
    NodeP* topo;
} Pilha;

void initPilha(Pilha* p);
void push(Pilha* p, int v);
int pop(Pilha* p);
int top(Pilha* p);
void printPilha(Pilha* p, char* buffer);

typedef struct NodeF {
    int valor;
    struct NodeF* prox;
} NodeF;

typedef struct {
    NodeF* frente;
    NodeF* tras;
} Fila;

void initFila(Fila* f);
void enqueue(Fila* f, int v);
int dequeue(Fila* f);
void visualizarFila(Fila* f, char* buffer);

#endif
