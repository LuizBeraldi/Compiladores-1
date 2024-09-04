%{

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define HASH_SIZE 211

extern int yylex();
void yyerror(void *s);

extern int yychar;
extern int textBefore;
extern int myEof;

int erroAux = 0;
int semanticError = 0;

int currentType;

typedef struct node {
    int key;
    char *value;
    struct node *next;
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
    // printf(">> %d %s\n\n", currentType, yylval.token.valor);
    if (!lookForValueInHash())
        insertHash(); 
}
    | I COMMA ID { 
        // printf("-> %d %s\n\n", currentType, yylval.token.valor);
        if (!lookForValueInHash())
            insertHash(); 
} ;

%%

void yyerror(void *s) {}

int hash() {
    int hash = 0;
    for (int i = 0; i < strlen(yylval.token.valor); i++)
        hash += yylval.token.valor[i];
    return hash % HASH_SIZE;
}

void insertHash() {
    int index = hash(yylval.token.valor);
    HashNode *aux = calloc(1, sizeof(HashNode));
    aux->key = currentType;
    aux->value = calloc(strlen(yylval.token.valor) + 1, sizeof(char));
    strcpy(aux->value, yylval.token.valor);

    HashNode *head = (HashNode *) myHashTable[index];
    if (!head) {
        myHashTable[index] = aux;
    } else {
        while (head->next) 
            head = head->next;
        head->next = aux;
    }

}

int lookForValueInHash() {
    if (!myHashTable) return 0;
    int index = hash(yylval.token.valor);
    int ocorrencias = 0;
    HashNode *head = (HashNode *) myHashTable[index];

    while (head) {
        if (!strcmp(yylval.token.valor, head->value)) { // existe outro daquele identificador na hash
            ocorrencias++;
            if (ocorrencias == 1) continue;  // se for o primeiro, continua 
            if (currentType == head->key) {  // se for do mesmo tipo
                if (textBefore) printf("\n");
                printf("%d: identifier '%s' already declared", yylval.token.line, yylval.token.valor);
                semanticError = 1;
                textBefore = 1;
                return 1;

            } else {  // se for de tipo diferente
                if (textBefore) printf("\n");
                printf("%d: redefinition of identifier '%s'", yylval.token.line, yylval.token.valor);
                semanticError = 1;
                textBefore = 1;
                return 1;
            }
        }
        head = head->next;
    }
    return 0;
}

void freeHash() {
    for (int i = 0; i < HASH_SIZE; i++) {
        HashNode *head = myHashTable[i];
        while (head) {
            HashNode *aux = head->next;
            if (head->value) 
                free(head->value);
            free(head);
            head = aux;
        }
        myHashTable[i] = NULL; 
    }
}

int main(int argc, char *argv[]) {
    myHashTable = calloc(HASH_SIZE, sizeof(HashNode));
    while (!myEof) {
        yyparse();

        if (yychar == 0) break;
        if (semanticError == 0) {
            if (textBefore) printf("\n");
            printf("%d: All Identifiers on Hash.", yylval.token.line);
            textBefore = 1;
            freeHash();
        } else {
            semanticError = 0;
            freeHash();
        }        
    }
    if (myHashTable) {
        freeHash(myHashTable);
        free(myHashTable);
    }
    return 0;
}