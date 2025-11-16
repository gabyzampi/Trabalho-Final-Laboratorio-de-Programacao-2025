/*_projeto_tlibestruturas.hester_

 main.c
 libestruturas.c
 libestruturas.h
 libtest.c
 libtest.h
 testes.txt
 resultados.txt (gerado automaticamente)

 README.md */
 
/*#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libestruturas.h"
#include "libtest.h"

// -------------------- FUNÇÕES DE ARQUIVO (reaproveitadas) --------------------
void write_text_overwrite(const char *filename, const char *text) {
    FILE *f = fopen(filename, "w");
    if (!f) {
        perror("Erro ao abrir arquivo para escrita");
        return;
    }
    fprintf(f, "%s\n", text);
    fclose(f);
}

void append_text(const char *filename, const char *text) {
    FILE *f = fopen(filename, "a");
    if (!f) {
        perror("Erro ao abrir arquivo para append");
        return;
    }
    fprintf(f, "%s\n", text);
    fclose(f);
}

// -------------------- PROGRAMA PRINCIPAL --------------------
int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Uso: %s <arquivo_testes> <arquivo_resultados>\n", argv[0]);
        return 1;
    }

    const char *arquivo_entrada = argv[1];
    const char *arquivo_saida = argv[2];

    FILE *in = fopen(arquivo_entrada, "r");
    if (!in) {
        perror("Erro ao abrir arquivo de testes");
        return 1;
    }

    // Limpa o arquivo de saída no início
    write_text_overwrite(arquivo_saida, "=== RESULTADOS DOS TESTES ===");

    Pilha p;
    Fila f;
    inicializarPilha(&p);
    inicializarFila(&f);

    Teste t;
    int indice = 1;
    char linha[256];

    while (fgets(linha, sizeof(linha), in)) {
        // ignora linhas vazias
        if (strlen(linha) < 2) continue;

        // exemplo de linha: "PUSH 10 10"
        if (scanf(linha, "%s %d %d", t.operacao, &t.valor, &t.esperado) == 3) {
            int resultado = executarTeste(&t, &p, &f);

            // cria string do resultado
            char saida[128];
            snprintf(saida, sizeof(saida),
                     "Teste %d: %s(%d) = %d -> %s",
                     indice++,
                     t.operacao,
                     t.valor,
                     resultado,
                     (resultado == t.esperado) ? "OK" : "ERROR");

            append_text(arquivo_saida, saida);
        }
    }

    fclose(in);
    liberarPilha(&p);
    liberarFila(&f);

    printf("Execução concluída. Resultados gravados em %s\n", arquivo_saida);
    return 0;
}

*/
#include "libestruturas.h"
#include "libtest.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 100

int main(int argc, char *argv[]) {
    // 1. Ler argv[1] e argv[2]
    if (argc != 3) {
        fprintf(stderr, "Uso: %s <arquivo_entrada> <arquivo_saida>\n", argv[0]);
        return 1;
    }

    // 2. Abrir os arquivos
    FILE *in = fopen(argv[1], "r");
    if (in == NULL) {
        perror("Erro ao abrir arquivo de entrada");
        return 1;
    }

    FILE *out = fopen(argv[2], "w");
    if (out == NULL) {
        perror("Erro ao abrir arquivo de saída");
        fclose(in);
        return 1;
    }
    
    // 3. Inicializar estruturas vazias
    Pilha p;
    Fila f;
    inicializarPilha(&p);
    inicializarFila(&f);

    // 4. Ler linha a linha, preencher Teste e chamar executarTeste
    char line[MAX_LINE_LENGTH];
    int num_teste = 0;
    
    while (fgets(line, MAX_LINE_LENGTH, in) != NULL) {
        num_teste++;
        Teste t;
        t.valor1 = 0; // Inicializar
        
        // Parsing da linha: [OPERAÇÃO] [VALOR1 (opcional)] [|] [ESPERADO]
        
        // Usamos sscanf para ler a string da operação, o valor (se houver), 
        // o separador '|' (que pode ou não estar lá dependendo do formato) e o resultado esperado.
        // O formato do arquivo de entrada é um pouco inconsistente (com e sem '|'),
        // então sscanf com cuidado é o melhor caminho.
        
        char separador[2]; // Para ler o '|' ou um espaço
        int count = sscanf(line, "%19s %d %1s %49[^\n]", 
                           t.operacao, &t.valor1, separador, t.esperado);
        
        // Ajuste no parsing: se a operação for de consulta (TOP, POP, DEQUEUE, VISUALIZAR)
        // o valor1 não está presente, e o esperado pode estar após o '|'.
        if (count < 4) {
             // Tenta ler sem o valor1
             count = sscanf(line, "%19s %1s %49[^\n]", t.operacao, separador, t.esperado);
             if (count < 3) {
                 // Tenta ler sem o separador '|'
                 count = sscanf(line, "%19s %d %49[^\n]", t.operacao, &t.valor1, t.esperado);
             }
        }
        
        // Remover espaços em branco no início e fim do 'esperado' se necessário (simplificado)
        if (t.esperado[0] == ' ') memmove(t.esperado, t.esperado + 1, strlen(t.esperado));

        // Executar e registrar
        int sucesso = executarTeste(&t, &p, &f);
        registrarResultado(out, num_teste, &t, sucesso);
    }

    // 6. Liberar a memória e fechar arquivos
    liberarPilha(&p);
    liberarFila(&f);
    fclose(in);
    fclose(out);
    
    printf("Testes concluídos. Resultados gravados em %s\n", argv[2]);

    return 0;
}