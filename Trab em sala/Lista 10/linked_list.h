#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int valor;
    struct node *prox;
}nodeList;

typedef struct list{
    nodeList *head;
}listHeader;

void *criarLista();

void inserirNo(listHeader *list, int valor);

void removerNo(listHeader *list);

int getNo(listHeader *list);

void imprimirLista(listHeader *list);

void freeLista(listHeader *list);

#endif