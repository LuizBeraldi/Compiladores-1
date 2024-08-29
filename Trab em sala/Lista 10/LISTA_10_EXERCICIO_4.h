#ifndef _LISTA_10_EXERCICIO_4_H
#define _LISTA_10_EXERCICIO_4_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linked_list.h"

#define SIGMA 41
#define QNTD_FINAL 6
#define MAX_INPUT 131072

#define PLUS 2
#define TIMES 3
#define L_PAREN 4
#define R_PAREN 5
#define EOL 6
#define ID 7

int getChar(char *ler, char input);

bool ehFinal(int *finals, int atual);

void resetarVariaveis(int *index, int definirIndice, int *indiceBackup, int *fim, int *estadoAtual);

void imprimirErroLexico(char errado, bool *textoAntes, bool *flagLexico);

void processarSyntax(void *cadeia, bool *textoAntes);

void consumirToken(void *cadeia, int tokenAnalisado, int *tokenGlobal, bool *textoAntes);

void S(void *cadeia, int *tokenGlobal, bool *textoAntes);

void E(void *cadeia, int *tokenGlobal, bool *textoAntes);

void E_Prime(void *cadeia, int *tokenGlobal, bool *textoAntes);

void T(void *cadeia, int *tokenGlobal, bool *textoAntes);

void T_Prime(void *cadeia, int *tokenGlobal, bool *textoAntes);

void F(void *cadeia, int *tokenGlobal, bool *textoAntes);

void imprimirResultado(char *result, bool *textoAntes);

char *defineErro(int tokenGlobal, int tokenAnalisado);

void stringIncompleta(void *cadeia, int *tokenGlobal, bool *textoAntes, bool couldBeOver);

void switchTokens(char *text, int token);

#endif