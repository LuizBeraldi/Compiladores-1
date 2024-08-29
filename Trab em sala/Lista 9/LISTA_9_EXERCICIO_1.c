#include "LISTA_9_EXERCICIO_1.h"

bool errorFlag = false;

int main() {
    char ler[SIGMA] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
                         'i', 'f', 'e', 'l', 's', 'n', 'd', 't', 'h', 'b',
                         'g', 'p', 'r', '+', '-', '=', ';'};
    int edges[][SIGMA] = {
        // 0  1  2  3  4  5  6  7  8  9  i  f  e  l  s  n  d  t  h  b  g  p  r  +  -  =  ;
        {5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 6, 0, 22, 0, 0, 0, 0, 8, 0, 12, 0, 17, 0, 4, 4, 3, 2},  //estado 1
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},     //estado 2 ;
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},     //estado 3 =
        {5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},     //estado 4
        {5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},     //estado 5 num
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},     //estado 6
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},     //estado 7 if
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 0, 0, 0, 0, 0, 0, 0, 0},     //estado 8
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},    //estado 9
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},    //estado 10
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},     //estado 11 then
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},    //estado 12
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 14, 0, 0, 0, 0, 0, 0},    //estado 13
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},    //estado 14
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},    //estado 15
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},     //estado 16 begin
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 18, 0, 0, 0, 0},    //estado 17
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 19, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},    //estado 18
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},    //estado 19
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 21, 0, 0, 0, 0, 0, 0, 0, 0, 0},    //estado 20
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},     //estado 21 print
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 23, 0, 26, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},   //estado 22
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 24, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},    //estado 23
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 25, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},    //estado 24
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},     //estado 25 else
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 27, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},    //estado 26
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},     //estado 27 end
    };

    int estadoFinal[] = {2, 3, 5, 7, 11, 16, 21, 25, 27};

    bool textoAntes = false;
    char input[MAX_INPUT];
    bool primeiraLinha = true;
    while (fgets(input, MAX_INPUT, stdin) != NULL) {
        int estadoAtual = 1;         // estado inicial
        int indice = 0;                // índice do char na entrada
        int IndiceBackup = 0;          // índice para lidar com estados não terminais
        bool aceitoComoFinal = true;  // se o estado atual é um estado final
        int fim = -1;                 // estado final

        void *cadeia;
        if(primeiraLinha){
            cadeia = criarLista();
            primeiraLinha = false;
        }else{
            processarSyntax(cadeia, &textoAntes);
            free(cadeia);
            cadeia = criarLista();
        }

        while(input[indice] != '\0'){
            int indiceCharAtual = getChar(ler, input[indice]);
            if(indiceCharAtual == -1){
                if(fim == -1){
                    if(indice == 0){
                        if(input[indice] == 10 || input[indice] == 32){
                            resetarVariaveis(&indice, (indice + 1), &IndiceBackup, &fim, &estadoAtual);
                            continue;
                        }
                        resetarVariaveis(&indice, (indice + 1), &IndiceBackup, &fim, &estadoAtual);
                        continue;
                    }

                    resetarVariaveis(&indice, (IndiceBackup + 1), &IndiceBackup, &fim, &estadoAtual);
                    if(input[indice - 1] == 10 || input[indice - 1] == 32){
                        continue;
                    }
                    continue;
                }
                if(fim != estadoAtual){
                    indice = IndiceBackup;
                    IndiceBackup = indice;
                }
                if(fim != -1){
                    inserirNo(cadeia, fim);
                }
                resetarVariaveis(&indice, (indice + 1), &IndiceBackup, &fim, &estadoAtual);
                if(input[indice - 1] == 10 || input[indice - 1] == 32){
                    continue;
                }
                continue;
            }
            int proxEstado = edges[estadoAtual - 1][indiceCharAtual];
            if(proxEstado == 0){
                if(fim == -1){
                    resetarVariaveis(&indice, (IndiceBackup + 1), &IndiceBackup, &fim, &estadoAtual);
                    continue;
                }
                if(fim != -1){
                    inserirNo(cadeia, fim);
                    IndiceBackup = indice;
                }
                if(estadoAtual != fim){
                    indice = IndiceBackup - 1;
                    IndiceBackup = indice;
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
            indice++;
            if(aceitoComoFinal){
                IndiceBackup = indice;
            }
        }
        if(fim == estadoAtual){
            IndiceBackup = indice;
            inserirNo(cadeia, fim);
        }else{
            if(input[IndiceBackup] == 10 || input[IndiceBackup] == 32 || input[IndiceBackup] == 0){
                continue;
            }
            resetarVariaveis(&indice, (IndiceBackup + 1), &IndiceBackup, &fim, &estadoAtual);
        }
        processarSyntax(cadeia, &textoAntes);
        free(cadeia);
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

void resetarVariaveis(int *indice, int indiceToSet, int *IndiceBackup, int *fim, int *estadoAtual){
    *indice = indiceToSet;
    *IndiceBackup = *indice;
    *fim = -1;
    *estadoAtual = 1;
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
    switch(*tokenGlobal){
        case IF:
            consumirToken(cadeia, IF, tokenGlobal, textoAntes);
            stringIncompleta(cadeia, tokenGlobal, textoAntes);
            if(errorFlag){
                return;
            }

            E(cadeia, tokenGlobal, textoAntes);
            if(errorFlag){
                return;
            }
            consumirToken(cadeia, THEN, tokenGlobal, textoAntes);
            stringIncompleta(cadeia, tokenGlobal, textoAntes);
            if(errorFlag){
                return;
            }

            S(cadeia, tokenGlobal, textoAntes);
            if(errorFlag){
                return;
            }
            consumirToken(cadeia, ELSE, tokenGlobal, textoAntes);
            stringIncompleta(cadeia, tokenGlobal, textoAntes);
            if(errorFlag){
                return;
            }

            S(cadeia, tokenGlobal, textoAntes);

            break;

        case BEGIN:
            consumirToken(cadeia, BEGIN, tokenGlobal, textoAntes);
            stringIncompleta(cadeia, tokenGlobal, textoAntes);
            if(errorFlag){
                return;
            }

            S(cadeia, tokenGlobal, textoAntes);
            if(errorFlag){
                return;
            }
            L(cadeia, tokenGlobal, textoAntes);

            break;

        case PRINT:
            consumirToken(cadeia, PRINT, tokenGlobal, textoAntes);
            stringIncompleta(cadeia, tokenGlobal, textoAntes);
            if(errorFlag){
                return;
            }

            E(cadeia, tokenGlobal, textoAntes);

            break;

        default:
            if(!errorFlag){
                char *text = defineErro(*tokenGlobal, -1);
                strcat(text, "if, begin, print");
                imprimirResultado(text, textoAntes);
                free(text);
                errorFlag = true;
            }
            break;
    }
}

void L(void *cadeia, int *tokenGlobal, bool *textoAntes){
    switch(*tokenGlobal){
        case END:
            consumirToken(cadeia, END, tokenGlobal, textoAntes);
            if (errorFlag){
                return;
            }

            break;

        case SEMICOLON:
            consumirToken(cadeia, SEMICOLON, tokenGlobal, textoAntes);
            stringIncompleta(cadeia, tokenGlobal, textoAntes);
            if(errorFlag){
                return;
            }

            S(cadeia, tokenGlobal, textoAntes);
            if(errorFlag){
                return;
            }
            L(cadeia, tokenGlobal, textoAntes);

            break;

        default:
            if(!errorFlag){
                char *text = defineErro(*tokenGlobal, -1);
                strcat(text, "end, ;");
                imprimirResultado(text, textoAntes);
                free(text);
                errorFlag = true;
            }
            break;
    }
}

void E(void *cadeia, int *tokenGlobal, bool *textoAntes){
    consumirToken(cadeia, NUM, tokenGlobal, textoAntes);
    stringIncompleta(cadeia, tokenGlobal, textoAntes);
    if(errorFlag){
        return;
    }

    consumirToken(cadeia, EQUAL, tokenGlobal, textoAntes);
    stringIncompleta(cadeia, tokenGlobal, textoAntes);
    if(errorFlag){
        return;
    }

    consumirToken(cadeia, NUM, tokenGlobal, textoAntes);
    if(errorFlag){
        return;
    }
}

void imprimirResultado(char *result, bool *textoAntes){
    if(!result){
        return;
    }
    if(*textoAntes){
        printf("\n");
    }
    printf("%s", result);
    *textoAntes = true;
}

char *defineErro(int tokenGlobal, int tokenAnalisado){
    if(tokenGlobal == -1){
        return NULL;
    }
    char *text = calloc(200, sizeof(char));
    strcat(text, "ERRO SINTATICO EM: ");
    switchTokens(text, tokenGlobal);
    strcat(text, " ESPERADO: ");
    if(tokenAnalisado != -1){
        switchTokens(text, tokenAnalisado);
    }
    return text;
}

void stringIncompleta(void *cadeia, int *tokenGlobal, bool *textoAntes){
    if(getNo(cadeia) == -1){
        imprimirResultado("ERRO SINTATICO: CADEIA INCOMPLETA", textoAntes);
        errorFlag = true;
    }
}

void switchTokens(char *text, int token){
    switch(token){
        case SEMICOLON:
            strcat(text, ";");
            break;
        case EQUAL:
            strcat(text, "=");
            break;
        case NUM:
            strcat(text, "num");
            break;
        case IF:
            strcat(text, "if");
            break;
        case THEN:
            strcat(text, "then");
            break;
        case BEGIN:
            strcat(text, "begin");
            break;
        case PRINT:
            strcat(text, "print");
            break;
        case ELSE:
            strcat(text, "else");
            break;
        case END:
            strcat(text, "end");
            break;
        default:
            break;
    }
}