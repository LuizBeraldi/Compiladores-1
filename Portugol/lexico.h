#ifndef _LEXICO_H
#define _LEXICO_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lista.h"

#define SIGMA 91
#define QNT_FINAIS 167
#define INPUT_MAXIMO 131072

int getChar             (char *ler, char input);
bool ehFinal            (int *final, int atual);
void resetarEstados     (int *indice, int definirIndice, int *backupIndice, int *fim, int *estadoAtual);
void imprimirErroLexico (void *cadeia, char *input, int linha, int coluna, bool *textoAntes, bool *flagLexico, char *tokenConteudo);

#endif