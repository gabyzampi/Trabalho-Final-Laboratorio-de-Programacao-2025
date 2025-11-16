#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libestruturas.h"
#include "libtest.h"

#define MAX_LINE 200

int main(int argc, char* argv[]) {

    if (argc != 3) {
        printf("Uso: %s <testes.txt> <resultados.txt>\n", argv[0]);
        return 1;
    }

    FILE* in = fopen(argv[1], "r");
    FILE* out = fopen(argv[2], "w");

    if (!in || !out) {
        printf("Erro abrindo arquivos.\n");
        return 1;
    }

    Pilha p;
    Fila f;
    initPilha(&p);
    initFila(&f);

    char linha[MAX_LINE];
    int n = 1;

    while (fgets(linha, MAX_LINE, in)) {
        if (strlen(linha) < 2) continue;

        Teste t;
        t.valor = 0;

        char op[20], sep[3];
        char esperado[100];

        if (strstr(linha, "|")) {
            sscanf(linha, "%s %2s %99[^\n]", t.operacao, sep, t.esperado);
        }
        else {
            sscanf(linha, "%s %d %99[^\n]", t.operacao, &t.valor, t.esperado);
        }

        char obtido[200];
        int ok = executarTeste(&t, &p, &f, obtido);

        registrarResultado(out, n++, &t, obtido, ok);
    }

    fclose(in);
    fclose(out);

    printf("Testes concluídos. Resultados gravados em %s\n", argv[2]);
    return 0;
}
