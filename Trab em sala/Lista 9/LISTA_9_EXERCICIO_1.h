#ifndef _LISTA_9_EXERCICIO_1_H
#define _LISTA_9_EXERCICIO_1_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linked_list.h"

#define SIGMA 27
#define QNTD_FINAL 9
#define MAX_INPUT 131072

#define SEMICOLON 2
#define EQUAL 3
#define NUM 5
#define IF 7
#define THEN 11
#define BEGIN 16
#define PRINT 21
#define ELSE 25
#define END 27

int getChar(char *ler, char input);

bool ehFinal(int *finals, int atual);

void resetarVariaveis(int *indice, int indiceToSet, int *IndiceBackup, int *fim, int *estadoAtual);

void processarSyntax(void *cadeia, bool *textoAntes);

void consumirToken(void *cadeia, int tokenAnalisado, int *tokenGlobal, bool *textoAntes);

void S(void *cadeia, int *tokenGlobal, bool *textoAntes);

void L(void *cadeia, int *tokenGlobal, bool *textoAntes);

void E(void *cadeia, int *tokenGlobal, bool *textoAntes);

void imprimirResultado(char *result, bool *textoAntes);

char *defineErro(int tokenGlobal, int tokenAnalisado);

void stringIncompleta(void *cadeia, int *tokenGlobal, bool *textoAntes);

void switchTokens(char *text, int token);

#endif