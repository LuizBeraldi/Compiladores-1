#include "linked_list.h"

void *criarLista(){
    listHeader *l = calloc(1, sizeof(listHeader));
    return l;
}

void inserirNo(listHeader *list, int valor){
    nodeList *node = calloc(1, sizeof(nodeList));
    node->valor = valor;

    if(list->head == NULL){
        list->head = node;

    }else{
        nodeList *aux = list->head;
        while(aux->prox != NULL){
            aux = aux->prox;
        }
        aux->prox = node;
    }
}

void removerNo(listHeader *list){
    if(list->head == NULL){
        return;
    }else{
        nodeList *aux = list->head;
        list->head = aux->prox;
        free(aux);
    }
}

int getNo(listHeader *list){
    if(list->head == NULL){
        return -1;
    }
    return list->head->valor;
}

void imprimirLista(listHeader *list){
    nodeList *aux = list->head;
    while(aux != NULL){
        printf("%d ", aux->valor);
        aux = aux->prox;
    }
    printf("\n");
}

void freeLista(listHeader *list){
    nodeList *aux = list->head;
    while(aux != NULL){
        nodeList *aux2 = aux->prox;
        free(aux);
        aux = aux2;
    }
    free(list);
}