%{

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define HASH_SIZE 211

extern int yylex();
void yyerror(void *s);

extern int yychar, textoAntes, myEof;

int erroAux = 0, erroSemantico = 0, currentType;

typedef struct node {
    int chave;
    char *value;
    struct node *prox;
} HashNode;

int hash();
void insertHash();
int lookForValueInHash();
void freeHash();

void **myHashTable = NULL;

%}

%union {
    struct {
        char *valor;
        int column;
        int line;
    } token;
}

%token EOL
%token COMMA
%token INT
%token CHAR
%token FLOAT
%token ID

%start S

%%

S: D D_Prime EOL { erroAux = 0; return 0; }
    | error { erroAux = 1; return 0; } ;

D_Prime: D D_Prime { }
    | { } ;

D: T I { } ;

T: INT { currentType = INT; }
    | CHAR { currentType = CHAR; }
    | FLOAT { currentType = FLOAT; } ;

I: ID {
    if (!lookForValueInHash())
        insertHash(); 
}
    | I COMMA ID {
        if (!lookForValueInHash())
            insertHash(); 
} ;

%%

void yyerror(void *s) {}

int hash() {
    int hash = 0;
    for(int i = 0; i < strlen(yylval.token.valor); i++){
        hash += yylval.token.valor[i];
    }
    return hash % HASH_SIZE;
}

void insertHash() {
    int index = hash(yylval.token.valor);
    HashNode *aux = calloc(1, sizeof(HashNode));
    aux->chave = currentType;
    aux->value = calloc(strlen(yylval.token.valor) + 1, sizeof(char));
    strcpy(aux->value, yylval.token.valor);

    HashNode *inicio = (HashNode *) myHashTable[index];
    if(!inicio){
        myHashTable[index] = aux;
    }else{
        while(inicio->prox){
            inicio = inicio->prox;
        }
        inicio->prox = aux;
    }

}

int lookForValueInHash(){
    if(!myHashTable){
        return 0;
    }
    int index = hash(yylval.token.valor);
    int ocorrencias = 0;
    HashNode *inicio = (HashNode *) myHashTable[index];

    while(inicio){
        if(!strcmp(yylval.token.valor, inicio->value)){
            ocorrencias++;
            if(ocorrencias == 1){
                continue;
            }
            if(currentType == inicio->chave){
                if (textoAntes){
                    printf("\n");
                }
                printf("%d: identifier '%s' already declared", yylval.token.line, yylval.token.valor);
                erroSemantico = 1;
                textoAntes = 1;
                return 1;

            }else{
                if (textoAntes){
                    printf("\n");
                }
                printf("%d: redefinition of identifier '%s'", yylval.token.line, yylval.token.valor);
                erroSemantico = 1;
                textoAntes = 1;
                return 1;
            }
        }
        inicio = inicio->prox;
    }
    return 0;
}

void freeHash() {
    for(int i = 0; i < HASH_SIZE; i++){
        HashNode *inicio = myHashTable[i];
        while(inicio){
            HashNode *aux = inicio->prox;
            if(inicio->value){
                free(inicio->value);
            }
            free(inicio);
            inicio = aux;
        }
        myHashTable[i] = NULL; 
    }
}

int main(int argc, char *argv[]) {
    myHashTable = calloc(HASH_SIZE, sizeof(HashNode));
    while(!myEof){
        yyparse();

        if(yychar == 0){
            break;
        }

        if(erroSemantico == 0){
            if(textoAntes){
                printf("\n");
            }
            printf("%d: All Identifiers on Hash.", yylval.token.line);
            textoAntes = 1;
            freeHash();
        }else{
            erroSemantico = 0;
            freeHash();
        }        
    }
    if(myHashTable){
        freeHash(myHashTable);
        free(myHashTable);
    }
    return 0;
}