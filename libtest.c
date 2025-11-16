#include "libtest.h"
#include <string.h>

int executarTeste(Teste* t, Pilha* p, Fila* f, char* buffer) {
    buffer[0] = '\0';

    if (strcmp(t->operacao, "PUSH") == 0) {
        push(p, t->valor);
        printPilha(p, buffer);
    }
    else if (strcmp(t->operacao, "POP") == 0) {
        int r = pop(p);
        sprintf(buffer, "%d", r);
    }
    else if (strcmp(t->operacao, "TOP") == 0) {
        int r = top(p);
        sprintf(buffer, "%d", r);
    }
    else if (strcmp(t->operacao, "ENQUEUE") == 0) {
        enqueue(f, t->valor);
        visualizarFila(f, buffer);
    }
    else if (strcmp(t->operacao, "DEQUEUE") == 0) {
        int r = dequeue(f);
        sprintf(buffer, "%d", r);
    }
    else if (strcmp(t->operacao, "VISUALIZAR") == 0) {
        visualizarFila(f, buffer);
    }

    return strcmp(buffer, t->esperado) == 0;
}

void registrarResultado(FILE* out, int n, Teste* t, char* obtido, int ok) {
    fprintf(out,
        "Teste %d: %s(%d) = %s -> %s\n",
        n, t->operacao, t->valor,
        obtido,
        ok ? "OK" : "ERROR"
    );
}
