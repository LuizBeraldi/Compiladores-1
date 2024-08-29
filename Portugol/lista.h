#ifndef LISTA_H
#define LISTA_H

#include <stdio.h>
#include <stdlib.h>

typedef struct no{
    int valor, linha, coluna;
    char *token;
    struct no *prox;
}ListaNo;

typedef struct lista{
    ListaNo *inicio;
}Lista;

void *criarLista();
void inserirNo(Lista *l, int valor, int linha, int coluna, char *token);
void removerNo(Lista *l);
int getNo(Lista *l);
int getLinha(Lista *l);
int getColuna(Lista *l);
char *getConteudoToken(Lista *l);
void imprimirLista(Lista *l);
void freeLista(Lista *l);

#endif