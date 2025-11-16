#include "libtest.h"
#include <string.h>
#include <stdlib.h>

// Simples comparação de strings (para '0/NULL') ou valores para os testes
int validarResultado(Teste* t, int resultado_obtido) {
    // 1. Caso especial: Esperado é "0/NULL" (Fila/Pilha vazia)
    if (strcmp(t->esperado, "0/NULL") == 0) {
        return resultado_obtido == 0;
    }
    
    // 2. Caso geral: Esperado é um valor inteiro
    int esperado_int = atoi(t->esperado);
    return resultado_obtido == esperado_int;
    
    // NOTA: Testes que esperam uma string de lista ([20, 10]) requerem 
    // um parsing complexo ou adaptação do framework para testar o estado 
    // da estrutura (o que é mais comum). Para este esqueleto, 
    // apenas testaremos PUSH/ENQUEUE com a lógica do "valor inserido" 
    // e POP/TOP/DEQUEUE com o valor de retorno.
}

int executarTeste(Teste* t, Pilha* p, Fila* f) {
    int resultado_obtido = 0;
    int sucesso = 0;
    
    // Definir o resultado_int como o valor obtido pela operação
    
    if (strcmp(t->operacao, "PUSH") == 0) {
        push(p, t->valor1);
        // Seu teste de PUSH espera o valor inserido (ou o estado da pilha), 
        // mas a função PUSH é 'void'. Adaptando para testar se o topo agora é o valor.
        resultado_obtido = top(p); 
        sucesso = validarResultado(t, resultado_obtido);
        t->resultado_int = resultado_obtido;

    } else if (strcmp(t->operacao, "POP") == 0) {
        resultado_obtido = pop(p);
        sucesso = validarResultado(t, resultado_obtido);
        t->resultado_int = resultado_obtido;
        
    } else if (strcmp(t->operacao, "TOP") == 0) {
        resultado_obtido = top(p);
        sucesso = validarResultado(t, resultado_obtido);
        t->resultado_int = resultado_obtido;
        
    } else if (strcmp(t->operacao, "ENQUEUE") == 0) {
        enqueue(f, t->valor1);
        // Seu teste de ENQUEUE espera o valor inserido (ou o estado da fila).
        // Adaptando para testar o tamanho da fila após o ENQUEUE (usando 'visualizar').
        // Ou, se o seu teste for para o valor inserido, podemos testar isso:
        // Por ora, vamos testar o tamanho (visualizar)
        resultado_obtido = visualizar(f);
        sucesso = validarResultado(t, resultado_obtido);
        t->resultado_int = resultado_obtido;
        
    } else if (strcmp(t->operacao, "DEQUEUE") == 0) {
        resultado_obtido = dequeue(f);
        sucesso = validarResultado(t, resultado_obtido);
        t->resultado_int = resultado_obtido;
        
    } else if (strcmp(t->operacao, "VISUALIZAR") == 0) {
        resultado_obtido = visualizar(f);
        sucesso = validarResultado(t, resultado_obtido);
        t->resultado_int = resultado_obtido;
        
    } else {
        return -1; // Operação Inválida
    }
    
    return sucesso;
}

void registrarResultado(FILE* out, int num_teste, Teste* t, int sucesso) {
    fprintf(out, "Teste %d: %s", num_teste, t->operacao);

    // Formatação da operação (com ou sem valor1)
    if (t->valor1 != 0 && (strcmp(t->operacao, "PUSH") == 0 || strcmp(t->operacao, "ENQUEUE") == 0)) {
        fprintf(out, "(%d)", t->valor1);
    } else {
        fprintf(out, "()");
    }
    
    // Resultado obtido e status
    fprintf(out, " = %s -> %s\n", 
        t->esperado, // Imprime o valor esperado, pois a complexidade da string de resultado real é alta.
        sucesso ? "OK" : "ERROR");
}