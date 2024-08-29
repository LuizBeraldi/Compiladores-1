#include "lista.h"
#include "sintatico.h"

void *criarLista(){
    Lista *l = calloc(1, sizeof(Lista));
    return l;
}

void inserirNo(Lista *l, int valor, int linha, int coluna, char *token){
    ListaNo *no = calloc(1, sizeof(ListaNo));
    no->valor = valor;
    no->linha = linha;
    no->coluna = coluna;

    if(valor != 19 && token[0] == '/'){
        token++;
    }
    no->token = calloc(strlen(token) + 1, sizeof(char));
    strcpy(no->token, token);

    if(!l->inicio){
        l->inicio = no;
    }else{
        ListaNo *aux = l->inicio;

        while(aux->prox){
            aux = aux->prox;
        }
        aux->prox = no;
    }
}

void removerNo(Lista *l){
    if(!l->inicio){
        return;
    }else{
        ListaNo *aux = l->inicio;
        l->inicio = aux->prox;

        if(aux->token){
            free(aux->token);
        }
        free(aux);
    }
}

int getNo(Lista *l){
    if(!l->inicio){
         return -1;
    }
    return l->inicio->valor;
}

int getLinha(Lista *l){
    if(!l->inicio){
         return -1;
    }
    return l->inicio->linha;
}

int getColuna(Lista *l){
    if(!l->inicio){
         return -1;
    }
    return l->inicio->coluna;
}

char *getConteudoToken(Lista *l){
    if(!l->inicio){
        return NULL;
    }
    return l->inicio->token;
}

void imprimirLista(Lista *l){
    ListaNo *aux = l->inicio;

    while(aux != NULL){
        printf("%d ", aux->valor);
        aux = aux->prox;
    }
    printf("\n");
}

void freeLista(Lista *l){
    ListaNo *aux = l->inicio;

    while(aux != NULL){
        ListaNo *temp = aux->prox;

        if(aux){
            if(aux->token){
                free(aux->token);
            }
            free(aux);
        }
        aux = temp;
    }
    
    if(l){
        free(l);
    }
}