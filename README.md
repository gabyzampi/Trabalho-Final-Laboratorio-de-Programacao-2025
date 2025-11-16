# Trabalho-Final-Laboratorio-de-Programacao-2025

Instruções de Compilação e Execução:

Este projeto implementa um framework de testes unitários em C para as estruturas de dados Pilha (Stack) e Fila (Queue), utilizando modularização com bibliotecas pessoais.
Compilação
Para compilar o projeto, use o compilador GCC. O main.c deve ser linkado com as bibliotecas libestruturas.c e libtest.c.

Bash
gcc main.c libestruturas.c libtest.c -o tester

Execução:

O programa tester requer dois argumentos na linha de comando: o caminho para o arquivo de entrada de testes e o caminho para o arquivo de saída de resultados.
Sintaxe:
Bash
./tester <arquivo_entrada.txt> <arquivo_saida.txt>

Exemplo:
Bash
./tester testes.txt resultados.txt

O arquivo resultados.txt será gerado com o relatório de cada teste executado.
