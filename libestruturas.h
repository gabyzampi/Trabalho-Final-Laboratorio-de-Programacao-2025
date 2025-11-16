#ifndef LIBESTRUTURAS_H
#define LIBESTRUTURAS_H

// Definição da Pilha
typedef struct NodeP {
    int valor;
    struct NodeP* prox;
} NodeP;

typedef struct {
    NodeP* topo;
} Pilha;

// Definição da Fila
typedef struct NodeF {
    int valor;
    struct NodeF* prox;
} NodeF;

typedef struct {
    NodeF* frente;
    NodeF* tras;
} Fila;

// Funções de Inicialização
void inicializarPilha(Pilha* p);
void inicializarFila(Fila* f);

// Operações da Pilha
void push(Pilha* p, int v);
int pop(Pilha* p); // Retorna o valor removido ou um código de erro (e.g., -1 ou um valor que não pode ser 0/NULL no contexto da sua aplicação)
int top(Pilha* p); // Retorna o valor do topo ou um código de erro

// Operações da Fila
void enqueue(Fila* f, int v);
int dequeue(Fila* f); // Retorna o valor removido ou um código de erro
// A função 'visualizar' no seu exemplo parece retornar um estado da fila (o último a ser enfileirado no topo da visualização), 
// mas para um teste unitário que retorna apenas um 'int', vamos implementar algo que possa ser testado numericamente, 
// como o tamanho da fila ou um valor específico (ou adaptar o teste para ser validado em 'libtest.c').
// Para este esqueleto, vou usar o tamanho da fila como retorno para 'visualizar'.
int visualizar(Fila* f); 

// Funções auxiliares (para fins de teste/limpeza)
int pilhaVazia(Pilha* p);
int filaVazia(Fila* f);
void liberarPilha(Pilha* p);
void liberarFila(Fila* f);

#endif // LIBESTRUTURAS_H