#ifndef _LISTA_6_EXERCICIO_1_H
#define _LISTA_6_EXERCICIO_1_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIGMA 20
#define QNTD_FINAL 12

// Retorna o índice do char no array, ou -1 se não estiver no array
// Basicamente obtém a coluna da matriz (o estado para onde ela vai) que corresponde ao char lido
int getChar(char *leitura, char input);

// Retorna verdadeiro se o estado atual for um estado final, falso caso contrário
bool ehFinal(int *final, int atual);

// Imprime o token, e se havia texto antes dele, imprime uma nova linha antes de imprimir o token
void imprimirToken(bool *textoAntes, char *paraImprimir);

// Imprime a sessão, que são os chars que foram lidos
void imprimirSecao(char *output, int tam);

//Limpa o buffer de saída e redefine o índice de saída
void limparOutput(char *output, int tam, int *outputIndice);

// Redefine as variáveis ​​que são usadas no loop principal, para que o autômato possa começar a ler o próximo token
void resetarVariaveis(int *indice, int definirIndice, int *backupIndice, int *fim, int *estadoAtual);

#endif