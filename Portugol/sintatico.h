#ifndef _SINTATICO_H
#define _SINTATICO_H

#include "lexico.h"

#define ID 2
#define NUMERO_INTEIRO 3
#define NUMERO_REAL 4
#define PONTO_VIRGULA 5
#define VIRGULA 6
#define DOIS_PONTOS 7
#define PONTO 8
#define ABRE_COLCHETE 9
#define FECHA_COLCHETE 10
#define ABRE_PARENTESES 11
#define FECHA_PARENTESES 12
#define IGUAL 13
#define MAIOR 14
#define MENOR 15
#define MAIS 16
#define MENOS 17
#define VEZES 18
#define DIVISAO 19
#define ALGORITMO 28
#define ATE 30
#define DIFERENTE 31
#define MAIOR_IGUAL 32
#define MENOR_IGUAL 33
#define ATRIBUICAO 34
#define INICIO 40
#define IMPRIMA 46
#define FIM 49
#define FUNCAO 54
#define FACA 57
#define FALSO 60
#define VARIAVEIS 69
#define VETOR 73
#define VERDADEIRO 81
#define INTEIRO 86
#define REAL 90
#define REPITA 94
#define SE 96
#define SENAO 99
#define AND 100
#define ENTAO 104
#define ENQUANTO 110
#define DE 112
#define DIV 114
#define OU 116
#define NAO 119
#define TIPO 123
#define LEIA 127
#define LOGICO 132
#define MATRIZ 138
#define CARACTERE 147
#define PARA 151
#define PASSO 154
#define PROCEDIMENTO 165
#define COMENTARIO_DE_LINHA 166
#define STRING 168
#define COMENTARIO_DE_BLOCO 170
#define EOF_TOKEN 185

void processarSintaxe       (void *cadeia, bool *textoAntes, char *input);
void consumirToken          (void *cadeia, int tokenAnalisado, int *tokenGlobal, bool *textoAntes, char *input);
void imprimirResultados     (char *result, bool *textoAntes);
void tratarErro             (void *cadeia);
void tratarErroSintatico    (void *cadeia, char *input);

void comecar                    (void *cadeia, int *tokenGlobal, bool *textoAntes, char *input);
void programa                   (void *cadeia, int *tokenGlobal, bool *textoAntes, char *input);
void procedimentoFuncao         (void *cadeia, int *tokenGlobal, bool *textoAntes, char *input);
void declaraProcedimento        (void *cadeia, int *tokenGlobal, bool *textoAntes, char *input);
void declaraFuncao              (void *cadeia, int *tokenGlobal, bool *textoAntes, char *input);
void parametros                 (void *cadeia, int *tokenGlobal, bool *textoAntes, char *input);
void declaraParametros          (void *cadeia, int *tokenGlobal, bool *textoAntes, char *input);
void blocoVariaveis             (void *cadeia, int *tokenGlobal, bool *textoAntes, char *input);
void declaracoes                (void *cadeia, int *tokenGlobal, bool *textoAntes, char *input);
void declaracoesAux             (void *cadeia, int *tokenGlobal, bool *textoAntes, char *input);
void declaraTipo                (void *cadeia, int *tokenGlobal, bool *textoAntes, char *input);
void declaraVariaveis           (void *cadeia, int *tokenGlobal, bool *textoAntes, char *input);
void declaraIdentificador       (void *cadeia, int *tokenGlobal, bool *textoAntes, char *input);
void declaraIdentificadorAux    (void *cadeia, int *tokenGlobal, bool *textoAntes, char *input);
void vetorMatriz                (void *cadeia, int *tokenGlobal, bool *textoAntes, char *input);
void dimensoes                  (void *cadeia, int *tokenGlobal, bool *textoAntes, char *input);
void dimensoesAux               (void *cadeia, int *tokenGlobal, bool *textoAntes, char *input);
void tipoBasico                 (void *cadeia, int *tokenGlobal, bool *textoAntes, char *input);
void blocoComandos              (void *cadeia, int *tokenGlobal, bool *textoAntes, char *input);
void listaComandos              (void *cadeia, int *tokenGlobal, bool *textoAntes, char *input);
void listaComandosAux           (void *cadeia, int *tokenGlobal, bool *textoAntes, char *input);
void comandos                   (void *cadeia, int *tokenGlobal, bool *textoAntes, char *input);
void comandos1                  (void *cadeia, int *tokenGlobal, bool *textoAntes, char *input);
void comandos2                  (void *cadeia, int *tokenGlobal, bool *textoAntes, char *input);
void comandos3                  (void *cadeia, int *tokenGlobal, bool *textoAntes, char *input);
void expressao                  (void *cadeia, int *tokenGlobal, bool *textoAntes, char *input);
void expressaoAux               (void *cadeia, int *tokenGlobal, bool *textoAntes, char *input);
void expressaoSimples           (void *cadeia, int *tokenGlobal, bool *textoAntes, char *input);
void expressaoSimplesAux        (void *cadeia, int *tokenGlobal, bool *textoAntes, char *input);
void operadorRelacional         (void *cadeia, int *tokenGlobal, bool *textoAntes, char *input);
void operadorBinario            (void *cadeia, int *tokenGlobal, bool *textoAntes, char *input);
void termo                      (void *cadeia, int *tokenGlobal, bool *textoAntes, char *input);
void termoAux                   (void *cadeia, int *tokenGlobal, bool *textoAntes, char *input);
void fator                      (void *cadeia, int *tokenGlobal, bool *textoAntes, char *input);
void fatorAux                   (void *cadeia, int *tokenGlobal, bool *textoAntes, char *input);
void variavel                   (void *cadeia, int *tokenGlobal, bool *textoAntes, char *input);
void variavelAux                (void *cadeia, int *tokenGlobal, bool *textoAntes, char *input);
void exprIter                   (void *cadeia, int *tokenGlobal, bool *textoAntes, char *input);
void exprIterAux                (void *cadeia, int *tokenGlobal, bool *textoAntes, char *input);

void defineID(int *tokenGlobal);

#endif