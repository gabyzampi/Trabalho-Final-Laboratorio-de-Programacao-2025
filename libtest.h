#ifndef LIBTEST_H
#define LIBTEST_H

#include "libestruturas.h"
#include <stdio.h>

// Estrutura de Teste
typedef struct {
    char operacao[20];
    int valor1;    // Valor a ser inserido (PUSH/ENQUEUE)
    char esperado[50]; // String do resultado esperado
    // Campos auxiliares para o resultado real
    int resultado_int;
    char resultado_str[50];
} Teste;

// Funções
// Interpreta o teste e chama a operação apropriada.
// Retorna 1 (OK), 0 (ERRO) ou -1 (OPERAÇÃO INVÁLIDA).
int executarTeste(Teste* t, Pilha* p, Fila* f);

// Registra o resultado no arquivo de saída
void registrarResultado(FILE* out, int num_teste, Teste* t, int sucesso);

#endif // LIBTEST_H