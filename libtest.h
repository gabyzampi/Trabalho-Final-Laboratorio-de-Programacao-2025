#ifndef LIBTEST_H
#define LIBTEST_H

#include "libestruturas.h"
#include <stdio.h>

typedef struct {
    char operacao[20];
    int valor;
    char esperado[100];
} Teste;

int executarTeste(Teste* t, Pilha* p, Fila* f, char* buffer);
void registrarResultado(FILE* out, int n, Teste* t, char* obtido, int ok);

#endif
