#include "LISTA_10_EXERCICIO_4.h"

bool errorFlag = false;

int main() {
    char ler[SIGMA] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
                         'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',
                         'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
                         'u', 'v', 'w', 'x', 'y', 'z', '+', '*', '(', ')', '$'};
    int edges[][SIGMA] = {
        //0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f  g  h  i  j  k  l  m  n  o  p  q  r  s  t  u  v  w  x  y  z  +  *  (  )  $
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 2, 3, 4, 5, 6},  // estado 1
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},  // estado 2 +
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},  // estado 3 *
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},  // estado 4 (
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},  // estado 5 )
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},  // estado 6 $
        {7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0, 0, 0, 0, 0},  // estado 7 id
    };

    int estadoFinal[] = {2, 3, 4, 5, 6, 7};

    bool textoAntes = false;
    char input[MAX_INPUT];
    bool primeiraLinha = true;
    bool flagLexico = false;
    while (fgets(input, MAX_INPUT, stdin) != NULL) {
        int estadoAtual = 1;         // estado inicial
        int index = 0;                // índice do char na entrada
        int indiceBackup = 0;          // índice para lidar com estados não terminais
        bool aceitoComoFinal = true;  // se o estado atual é um estado final
        int fim = -1;                 // estado final

        void *cadeia;
        if(primeiraLinha){
            cadeia = criarLista();
            primeiraLinha = false;
        }else{
            if(!flagLexico){
                processarSyntax(cadeia, &textoAntes);
            }
            flagLexico = false;
            freeLista(cadeia);
            cadeia = criarLista();
        }
        while(input[index] != '\0'){
            int indiceCharAtual = getChar(ler, input[index]);

            if(indiceCharAtual == -1){
                if(fim == -1){
                    if(index == 0){
                        if(input[index] == 10 || input[index] == 32){
                            resetarVariaveis(&index, (index + 1), &indiceBackup, &fim, &estadoAtual);
                            continue;
                        }
                        imprimirErroLexico(input[index], &textoAntes, &flagLexico);
                        resetarVariaveis(&index, (index + 1), &indiceBackup, &fim, &estadoAtual);
                        continue;
                    }

                    resetarVariaveis(&index, (indiceBackup + 1), &indiceBackup, &fim, &estadoAtual);
                    if (input[index - 1] == 10 || input[index - 1] == 32){
                        continue;
                    }
                    imprimirErroLexico(input[index - 2], &textoAntes, &flagLexico);
                    continue;
                }

                if(fim != estadoAtual){
                    index = indiceBackup;
                    indiceBackup = index;
                }

                if(fim != -1){
                    inserirNo(cadeia, fim);
                }

                resetarVariaveis(&index, (index + 1), &indiceBackup, &fim, &estadoAtual);
                if (input[index - 1] == 10 || input[index - 1] == 32){
                    continue;
                }
                imprimirErroLexico(input[index - 2], &textoAntes, &flagLexico);
                continue;
            }

            int proxEstado = edges[estadoAtual - 1][indiceCharAtual];

            if(proxEstado == 0){
                if(fim == -1){
                    imprimirErroLexico(input[index], &textoAntes, &flagLexico);
                    resetarVariaveis(&index, (indiceBackup + 1), &indiceBackup, &fim, &estadoAtual);
                    continue;
                }

                if(fim != -1){
                    inserirNo(cadeia, fim);
                    indiceBackup = index;
                }

                if(estadoAtual != fim){
                    index = indiceBackup - 1;
                    indiceBackup = index;
                }
                fim = -1;
                estadoAtual = 1;
                continue;
            }
            estadoAtual = proxEstado;
            aceitoComoFinal = ehFinal(estadoFinal, estadoAtual);
            if(aceitoComoFinal){
                fim = estadoAtual;
            }
            index++;
            if(aceitoComoFinal){
                indiceBackup = index;
            }
        }
        if(fim == estadoAtual){
            indiceBackup = index;
            inserirNo(cadeia, fim);
        }else{
            if (input[indiceBackup] == 10 || input[indiceBackup] == 32 || input[indiceBackup] == 0){
                continue;
            }
            imprimirErroLexico(input[indiceBackup], &textoAntes, &flagLexico);
            resetarVariaveis(&index, (indiceBackup + 1), &indiceBackup, &fim, &estadoAtual);
        }
        if(!flagLexico){
            processarSyntax(cadeia, &textoAntes);
        }
        flagLexico = false;
        freeLista(cadeia);
    }
    return 0;
}

int getChar(char *ler, char input){
    for(int i = 0; i < SIGMA; i++){
        if(ler[i] == input){
            return i;
        }
    }
    return -1;
}

bool ehFinal(int *finals, int atual){
    for(int i = 0; i < QNTD_FINAL; i++){
        if(finals[i] == atual){
            return true;
        }
    }
    return false;
}

void resetarVariaveis(int *index, int definirIndice, int *indiceBackup, int *fim, int *estadoAtual){
    *index = definirIndice;
    *indiceBackup = *index;
    *fim = -1;
    *estadoAtual = 1;
}

void imprimirErroLexico(char errado, bool *textoAntes, bool *flagLexico){
    if(*flagLexico){
        return;
    }
    if(*textoAntes){
        printf("\n");
    }
    printf("ERRO LEXICO EM: %c", errado);
    *textoAntes = true;
    *flagLexico = true;
}

void processarSyntax(void *cadeia, bool *textoAntes){
    int tokenGlobal = getNo(cadeia);
    if(tokenGlobal == -1){
        imprimirResultado("ERRO LISTA VAZIA", textoAntes);
        exit(0);
    }
    errorFlag = false;
    S(cadeia, &tokenGlobal, textoAntes);

    if(!errorFlag && getNo(cadeia) == -1){
        imprimirResultado("CADEIA ACEITA", textoAntes);
    }
}

void consumirToken(void *cadeia, int tokenAnalisado, int *tokenGlobal, bool *textoAntes){
    if(tokenAnalisado == *tokenGlobal){
        removerNo(cadeia);
        *tokenGlobal = getNo(cadeia);
    }else{
        char *text = defineErro(*tokenGlobal, tokenAnalisado);
        imprimirResultado(text, textoAntes);
        free(text);
        errorFlag = true;
    }
}

void S(void *cadeia, int *tokenGlobal, bool *textoAntes){
    switch (*tokenGlobal){
        case ID:
        case L_PAREN:
            E(cadeia, tokenGlobal, textoAntes);
            if(errorFlag){
                return;
            }
            consumirToken(cadeia, EOL, tokenGlobal, textoAntes);
            break;

        default:
            if(!errorFlag){
                char *text = defineErro(*tokenGlobal, -1);
                strcat(text, " id, (");
                imprimirResultado(text, textoAntes);
                free(text);
                errorFlag = true;
            }
            break;
    }
}

void E(void *cadeia, int *tokenGlobal, bool *textoAntes){
    switch (*tokenGlobal){
        case ID:
        case L_PAREN:
            T(cadeia, tokenGlobal, textoAntes);
            if(errorFlag){
                return;
            }
            E_Prime(cadeia, tokenGlobal, textoAntes);
            break;

        default:
            if(!errorFlag){
                char *text = defineErro(*tokenGlobal, -1);
                strcat(text, " id, (");
                imprimirResultado(text, textoAntes);
                free(text);
                errorFlag = true;
            }
            break;
    }
}

void E_Prime(void *cadeia, int *tokenGlobal, bool *textoAntes){
    switch (*tokenGlobal){
        case PLUS:
            consumirToken(cadeia, PLUS, tokenGlobal, textoAntes);
            stringIncompleta(cadeia, tokenGlobal, textoAntes, false);
            if(errorFlag){
                return;
            }
            T(cadeia, tokenGlobal, textoAntes);
            if (errorFlag){
                return;
            }
            E_Prime(cadeia, tokenGlobal, textoAntes);
            break;

        case R_PAREN:
        case EOL:
            break;

        default:
            if(!errorFlag){
                char *text = defineErro(*tokenGlobal, -1);
                strcat(text, " +, ), $");
                imprimirResultado(text, textoAntes);
                free(text);
                errorFlag = true;
            }
            break;
    }
}

void T(void *cadeia, int *tokenGlobal, bool *textoAntes){
    switch (*tokenGlobal){
        case ID:
        case L_PAREN:
            F(cadeia, tokenGlobal, textoAntes);
            if(errorFlag){
                return;
            }
            T_Prime(cadeia, tokenGlobal, textoAntes);
            break;

        default:
            if(!errorFlag){
                char *text = defineErro(*tokenGlobal, -1);
                strcat(text, " id, (");
                imprimirResultado(text, textoAntes);
                free(text);
                errorFlag = true;
            }
            break;
    }
}

void T_Prime(void *cadeia, int *tokenGlobal, bool *textoAntes){
    switch (*tokenGlobal){
        case PLUS:
        case R_PAREN:
        case EOL:
            break;

        case TIMES:
            consumirToken(cadeia, TIMES, tokenGlobal, textoAntes);
            stringIncompleta(cadeia, tokenGlobal, textoAntes, false);
            if(errorFlag){
                return;
            }
            F(cadeia, tokenGlobal, textoAntes);
            if(errorFlag){
                return;
            }
            T_Prime(cadeia, tokenGlobal, textoAntes);
            break;

        default:
            if(!errorFlag){
                char *text = defineErro(*tokenGlobal, -1);
                strcat(text, " +, *, ), $");
                imprimirResultado(text, textoAntes);
                free(text);
                errorFlag = true;
            }
            break;
    }
}

void F(void *cadeia, int *tokenGlobal, bool *textoAntes){
    switch (*tokenGlobal){
        case ID:
            consumirToken(cadeia, ID, tokenGlobal, textoAntes);
            break;

        case L_PAREN:
            consumirToken(cadeia, L_PAREN, tokenGlobal, textoAntes);
            stringIncompleta(cadeia, tokenGlobal, textoAntes, false);
            if(errorFlag){
                return;
            }
            E(cadeia, tokenGlobal, textoAntes);
            if(errorFlag){
                return;
            }
            consumirToken(cadeia, R_PAREN, tokenGlobal, textoAntes);
            break;

        default:
            if(!errorFlag){
                char *text = defineErro(*tokenGlobal, -1);
                strcat(text, " id, (");
                imprimirResultado(text, textoAntes);
                free(text);
                errorFlag = true;
            }
            break;
    }
}

void imprimirResultado(char *result, bool *textoAntes){
    if (!result){
        return;
    }
    if (*textoAntes){
        printf("\n");
    }
    printf("%s", result);
    *textoAntes = true;
}

char *defineErro(int tokenGlobal, int tokenAnalisado){
    char *text = calloc(200, sizeof(char));
    strcat(text, "ERRO SINTATICO EM:");
    switchTokens(text, tokenGlobal);
    strcat(text, " ESPERADO:");
    if(tokenAnalisado != -1){
        switchTokens(text, tokenAnalisado);
    }
    return text;
}

void stringIncompleta(void *cadeia, int *tokenGlobal, bool *textoAntes, bool couldBeOver){
    if(getNo(cadeia) == -1 && couldBeOver){
        imprimirResultado("ERRO SINTATICO: CADEIA INCOMPLETA", textoAntes);
        errorFlag = true;
    }
}

void switchTokens(char *text, int token){
    switch (token) {
        case -1:
            break;
        case PLUS:
            strcat(text, " +");
            break;
        case TIMES:
            strcat(text, " *");
            break;
        case L_PAREN:
            strcat(text, " (");
            break;
        case R_PAREN:
            strcat(text, " )");
            break;
        case EOL:
            strcat(text, " $");
            break;
        case ID:
            strcat(text, " id");
            break;
        default:
            break;
    }
}