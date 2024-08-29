#include "sintatico.h"

void processarSintaxe(void *cadeia, bool *textoAntes, char *input){
    int tokenGlobal = getNo(cadeia);
    if(tokenGlobal == -1){
        imprimirResultados("ERRO LISTA VAZIA", textoAntes);
        exit(0);
    }
    defineID(&tokenGlobal);
    comecar(cadeia, &tokenGlobal, textoAntes, input);
}

void consumirToken(void *cadeia, int tokenAnalisado, int *tokenGlobal, bool *textoAntes, char *input){
    if(tokenAnalisado == *tokenGlobal){
        removerNo(cadeia);
        *tokenGlobal = getNo(cadeia);
        defineID(tokenGlobal);
    }else{
        int column = getColuna(cadeia) - strlen(getConteudoToken(cadeia)) + 1;
        printf("ERRO DE SINTAXE. Linha: %d Coluna: %d -> '%s'", getLinha(cadeia), column, getConteudoToken(cadeia));
        freeLista(cadeia);
        free(input);
        exit(-2);
    }
}

void tratarErro(void *cadeia){
    int column = getColuna(cadeia) - strlen(getConteudoToken(cadeia)) + 1;
    printf("ERRO DE SINTAXE. Linha: %d Coluna: %d -> '%s'", getLinha(cadeia), column, getConteudoToken(cadeia));
}

void tratarErroSintatico(void *cadeia, char *input){
    tratarErro(cadeia);
    freeLista(cadeia);
    free(input);
    exit(-2);
}

void imprimirResultados(char *resultado, bool *textoAntes){
    if(!resultado){
        return;
    }

    if(*textoAntes){
        printf("\n");
    }
    printf("%s", resultado);
    *textoAntes = true;
}

void comecar(void *cadeia, int *tokenGlobal, bool *textoAntes, char *input){
    switch(*tokenGlobal){
        case ALGORITMO:
            programa(cadeia, tokenGlobal, textoAntes, input);
            consumirToken(cadeia, EOF_TOKEN, tokenGlobal, textoAntes, input);
            break;

        default:
            tratarErroSintatico(cadeia, input);
            break;
    }
}

void programa(void *cadeia, int *tokenGlobal, bool *textoAntes, char *input){
    switch(*tokenGlobal){
        case ALGORITMO:
            consumirToken(cadeia, ALGORITMO, tokenGlobal, textoAntes, input);
            consumirToken(cadeia, ID, tokenGlobal, textoAntes, input);
            consumirToken(cadeia, PONTO_VIRGULA, tokenGlobal, textoAntes, input);
            blocoVariaveis(cadeia, tokenGlobal, textoAntes, input);
            procedimentoFuncao(cadeia, tokenGlobal, textoAntes, input);
            blocoComandos(cadeia, tokenGlobal, textoAntes, input);
            consumirToken(cadeia, PONTO, tokenGlobal, textoAntes, input);
            break;

        case EOF_TOKEN:
            break;

        default:
            tratarErroSintatico(cadeia, input);
            break;
    }
}

void procedimentoFuncao(void *cadeia, int *tokenGlobal, bool *textoAntes, char *input){
    switch(*tokenGlobal){
        case PROCEDIMENTO:
            declaraProcedimento(cadeia, tokenGlobal, textoAntes, input);
            procedimentoFuncao(cadeia, tokenGlobal, textoAntes, input);
            break;

        case FUNCAO:
            declaraFuncao(cadeia, tokenGlobal, textoAntes, input);
            procedimentoFuncao(cadeia, tokenGlobal, textoAntes, input);
            break;

        case INICIO:
            break;

        default:
            tratarErroSintatico(cadeia, input);
            break;
    }
}

void declaraProcedimento(void *cadeia, int *tokenGlobal, bool *textoAntes, char *input){
    switch(*tokenGlobal){
        case PROCEDIMENTO:
            consumirToken(cadeia, PROCEDIMENTO, tokenGlobal, textoAntes, input);
            consumirToken(cadeia, ID, tokenGlobal, textoAntes, input);
            parametros(cadeia, tokenGlobal, textoAntes, input);
            consumirToken(cadeia, PONTO_VIRGULA, tokenGlobal, textoAntes, input);
            declaraParametros(cadeia, tokenGlobal, textoAntes, input);
            blocoVariaveis(cadeia, tokenGlobal, textoAntes, input);
            blocoComandos(cadeia, tokenGlobal, textoAntes, input);
            consumirToken(cadeia, PONTO_VIRGULA, tokenGlobal, textoAntes, input);
            break;

        default:
            tratarErroSintatico(cadeia, input);
            break;
    }
}

void declaraFuncao(void *cadeia, int *tokenGlobal, bool *textoAntes, char *input){
    switch(*tokenGlobal){
        case FUNCAO:
            consumirToken(cadeia, FUNCAO, tokenGlobal, textoAntes, input);
            consumirToken(cadeia, ID, tokenGlobal, textoAntes, input);
            parametros(cadeia, tokenGlobal, textoAntes, input);
            consumirToken(cadeia, DOIS_PONTOS, tokenGlobal, textoAntes, input);
            tipoBasico(cadeia, tokenGlobal, textoAntes, input);
            consumirToken(cadeia, PONTO_VIRGULA, tokenGlobal, textoAntes, input);
            declaraParametros(cadeia, tokenGlobal, textoAntes, input);
            blocoVariaveis(cadeia, tokenGlobal, textoAntes, input);
            blocoComandos(cadeia, tokenGlobal, textoAntes, input);
            consumirToken(cadeia, PONTO_VIRGULA, tokenGlobal, textoAntes, input);
            break;

        default:
            tratarErroSintatico(cadeia, input);
            break;
    }
}

void parametros(void *cadeia, int *tokenGlobal, bool *textoAntes, char *input){
    switch(*tokenGlobal){
        case PONTO_VIRGULA:
        case DOIS_PONTOS:
            break;

        case ABRE_PARENTESES:
            consumirToken(cadeia, ABRE_PARENTESES, tokenGlobal, textoAntes, input);
            declaraIdentificador(cadeia, tokenGlobal, textoAntes, input);
            consumirToken(cadeia, FECHA_PARENTESES, tokenGlobal, textoAntes, input);
            break;

        default:
            tratarErroSintatico(cadeia, input);
            break;
    }
}

void declaraParametros(void *cadeia, int *tokenGlobal, bool *textoAntes, char *input){
    switch(*tokenGlobal){
        case ID:
        case TIPO:
        case INTEIRO:
        case REAL:
        case CARACTERE:
        case LOGICO:
            declaracoes(cadeia, tokenGlobal, textoAntes, input);
            break;

        case PROCEDIMENTO:
        case FUNCAO:
        case VARIAVEIS:
        case INICIO:
            break;

        default:
            tratarErroSintatico(cadeia, input);
            break;
    }
}

void blocoVariaveis(void *cadeia, int *tokenGlobal, bool *textoAntes, char *input){
    switch(*tokenGlobal){
        case PROCEDIMENTO:
        case FUNCAO:
        case INICIO:
        case EOF_TOKEN:
            break;

        case VARIAVEIS:
            consumirToken(cadeia, VARIAVEIS, tokenGlobal, textoAntes, input);
            declaracoes(cadeia, tokenGlobal, textoAntes, input);
            break;

        default:
            tratarErroSintatico(cadeia, input);
            break;
    }
}

void declaracoes(void *cadeia, int *tokenGlobal, bool *textoAntes, char *input){
    switch(*tokenGlobal){
        case ID:
        case INTEIRO:
        case REAL:
        case CARACTERE:
        case LOGICO:
            declaraVariaveis(cadeia, tokenGlobal, textoAntes, input);
            declaracoesLinha(cadeia, tokenGlobal, textoAntes, input);
            break;

        case TIPO:
            declaraTipo(cadeia, tokenGlobal, textoAntes, input);
            declaracoesLinha(cadeia, tokenGlobal, textoAntes, input);
            break;

        default:
            tratarErroSintatico(cadeia, input);
            break;
    }
}

void declaracoesLinha(void *cadeia, int *tokenGlobal, bool *textoAntes, char *input){
    switch(*tokenGlobal){
        case ID:
        case TIPO:
        case INTEIRO:
        case REAL:
        case CARACTERE:
        case LOGICO:
            declaracoes(cadeia, tokenGlobal, textoAntes, input);
            break;

        case PROCEDIMENTO:
        case FUNCAO:
        case VARIAVEIS:
        case INICIO:
        case EOF_TOKEN:
            break;

        default:
            tratarErroSintatico(cadeia, input);
            break;
    }
}

void declaraTipo(void *cadeia, int *tokenGlobal, bool *textoAntes, char *input){
    switch(*tokenGlobal){
        case TIPO:
            consumirToken(cadeia, TIPO, tokenGlobal, textoAntes, input);
            consumirToken(cadeia, ID, tokenGlobal, textoAntes, input);
            consumirToken(cadeia, IGUAL, tokenGlobal, textoAntes, input);
            vetorMatriz(cadeia, tokenGlobal, textoAntes, input);
            consumirToken(cadeia, ABRE_COLCHETE, tokenGlobal, textoAntes, input);
            dimensoes(cadeia, tokenGlobal, textoAntes, input);
            consumirToken(cadeia, FECHA_COLCHETE, tokenGlobal, textoAntes, input);
            tipoBasico(cadeia, tokenGlobal, textoAntes, input);
            consumirToken(cadeia, PONTO_VIRGULA, tokenGlobal, textoAntes, input);
            break;

        default:
            tratarErroSintatico(cadeia, input);
            break;
    }
}

void declaraVariaveis(void *cadeia, int *tokenGlobal, bool *textoAntes, char *input){
    switch(*tokenGlobal){
        case ID:
        case INTEIRO:
        case REAL:
        case CARACTERE:
        case LOGICO:
            tipoBasico(cadeia, tokenGlobal, textoAntes, input);
            consumirToken(cadeia, DOIS_PONTOS, tokenGlobal, textoAntes, input);
            declaraIdentificador(cadeia, tokenGlobal, textoAntes, input);
            consumirToken(cadeia, PONTO_VIRGULA, tokenGlobal, textoAntes, input);
            break;

        default:
            tratarErroSintatico(cadeia, input);
            break;
    }
}

void declaraIdentificador(void *cadeia, int *tokenGlobal, bool *textoAntes, char *input){
    switch(*tokenGlobal){
        case ID:
            consumirToken(cadeia, ID, tokenGlobal, textoAntes, input);
            declaraIdentificadorLinha(cadeia, tokenGlobal, textoAntes, input);
            break;

        default:
            tratarErroSintatico(cadeia, input);
            break;
    }
}

void declaraIdentificadorLinha(void *cadeia, int *tokenGlobal, bool *textoAntes, char *input){
    switch(*tokenGlobal){
        case PONTO_VIRGULA:
        case FECHA_PARENTESES:
            break;

        case VIRGULA:
            consumirToken(cadeia, VIRGULA, tokenGlobal, textoAntes, input);
            declaraIdentificador(cadeia, tokenGlobal, textoAntes, input);
            break;

        default:
            tratarErroSintatico(cadeia, input);
            break;
    }
}

void vetorMatriz(void *cadeia, int *tokenGlobal, bool *textoAntes, char *input){
    switch(*tokenGlobal){
        case VETOR:
            consumirToken(cadeia, VETOR, tokenGlobal, textoAntes, input);
            break;

        case MATRIZ:
            consumirToken(cadeia, MATRIZ, tokenGlobal, textoAntes, input);
            break;

        default:
            tratarErroSintatico(cadeia, input);
            break;
    }
}

void dimensoes(void *cadeia, int *tokenGlobal, bool *textoAntes, char *input){
    switch(*tokenGlobal){
        case NUMERO_INTEIRO:
            consumirToken(cadeia, NUMERO_INTEIRO, tokenGlobal, textoAntes, input);
            consumirToken(cadeia, DOIS_PONTOS, tokenGlobal, textoAntes, input);
            consumirToken(cadeia, NUMERO_INTEIRO, tokenGlobal, textoAntes, input);
            dimensoesLinha(cadeia, tokenGlobal, textoAntes, input);
            break;

        default:
            tratarErroSintatico(cadeia, input);
            break;
    }
}

void dimensoesLinha(void *cadeia, int *tokenGlobal, bool *textoAntes, char *input){
    switch(*tokenGlobal){
        case FECHA_COLCHETE:
            break;

        case VIRGULA:
            consumirToken(cadeia, VIRGULA, tokenGlobal, textoAntes, input);
            dimensoes(cadeia, tokenGlobal, textoAntes, input);
            break;

        default:
            tratarErroSintatico(cadeia, input);
            break;
    }
}

void tipoBasico(void *cadeia, int *tokenGlobal, bool *textoAntes, char *input){
    switch(*tokenGlobal){
        case ID:
            consumirToken(cadeia, ID, tokenGlobal, textoAntes, input);
            break;

        case INTEIRO:
            consumirToken(cadeia, INTEIRO, tokenGlobal, textoAntes, input);
            break;

        case REAL:
            consumirToken(cadeia, REAL, tokenGlobal, textoAntes, input);
            break;

        case CARACTERE:
            consumirToken(cadeia, CARACTERE, tokenGlobal, textoAntes, input);
            break;

        case LOGICO:
            consumirToken(cadeia, LOGICO, tokenGlobal, textoAntes, input);
            break;

        default:
            tratarErroSintatico(cadeia, input);
            break;
    }
}

void blocoComandos(void *cadeia, int *tokenGlobal, bool *textoAntes, char *input){
    switch(*tokenGlobal){
        case INICIO:
            consumirToken(cadeia, INICIO, tokenGlobal, textoAntes, input);
            listaComandos(cadeia, tokenGlobal, textoAntes, input);
            consumirToken(cadeia, FIM, tokenGlobal, textoAntes, input);
            break;

        default:
            tratarErroSintatico(cadeia, input);
            break;
    }
}

void listaComandos(void *cadeia, int *tokenGlobal, bool *textoAntes, char *input){
    switch(*tokenGlobal){
        case ID:
        case SE:
        case ENQUANTO:
        case PARA:
        case REPITA:
        case LEIA:
        case IMPRIMA:
            comandos(cadeia, tokenGlobal, textoAntes, input);
            consumirToken(cadeia, PONTO_VIRGULA, tokenGlobal, textoAntes, input);
            listaComandosLinha(cadeia, tokenGlobal, textoAntes, input);
            break;

        default:
            tratarErroSintatico(cadeia, input);
            break;
    }
}

void listaComandosLinha(void *cadeia, int *tokenGlobal, bool *textoAntes, char *input){
    switch(*tokenGlobal){
        case ID:
        case SE:
        case ENQUANTO:
        case PARA:
        case REPITA:
        case LEIA:
        case IMPRIMA:
            listaComandos(cadeia, tokenGlobal, textoAntes, input);
            break;

        case FIM:
        case SENAO:
        case ATE:
            break;

        default:
            tratarErroSintatico(cadeia, input);
            break;
    }
}

void comandos(void *cadeia, int *tokenGlobal, bool *textoAntes, char *input){
    switch(*tokenGlobal){
        case ID:
            consumirToken(cadeia, ID, tokenGlobal, textoAntes, input);
            comandos1(cadeia, tokenGlobal, textoAntes, input);
            break;

        case SE:
            consumirToken(cadeia, SE, tokenGlobal, textoAntes, input);
            expressao(cadeia, tokenGlobal, textoAntes, input);
            consumirToken(cadeia, ENTAO, tokenGlobal, textoAntes, input);
            listaComandos(cadeia, tokenGlobal, textoAntes, input);
            comandos2(cadeia, tokenGlobal, textoAntes, input);
            break;

        case ENQUANTO:
            consumirToken(cadeia, ENQUANTO, tokenGlobal, textoAntes, input);
            expressao(cadeia, tokenGlobal, textoAntes, input);
            consumirToken(cadeia, FACA, tokenGlobal, textoAntes, input);
            listaComandos(cadeia, tokenGlobal, textoAntes, input);
            consumirToken(cadeia, FIM, tokenGlobal, textoAntes, input);
            consumirToken(cadeia, ENQUANTO, tokenGlobal, textoAntes, input);
            break;

        case PARA:
            consumirToken(cadeia, PARA, tokenGlobal, textoAntes, input);
            consumirToken(cadeia, ID, tokenGlobal, textoAntes, input);
            consumirToken(cadeia, DE, tokenGlobal, textoAntes, input);
            expressao(cadeia, tokenGlobal, textoAntes, input);
            consumirToken(cadeia, ATE, tokenGlobal, textoAntes, input);
            expressao(cadeia, tokenGlobal, textoAntes, input);
            comandos3(cadeia, tokenGlobal, textoAntes, input);
            break;

        case REPITA:
            consumirToken(cadeia, REPITA, tokenGlobal, textoAntes, input);
            listaComandos(cadeia, tokenGlobal, textoAntes, input);
            consumirToken(cadeia, ATE, tokenGlobal, textoAntes, input);
            expressao(cadeia, tokenGlobal, textoAntes, input);
            break;

        case LEIA:
            consumirToken(cadeia, LEIA, tokenGlobal, textoAntes, input);
            consumirToken(cadeia, ABRE_PARENTESES, tokenGlobal, textoAntes, input);
            variavel(cadeia, tokenGlobal, textoAntes, input);
            consumirToken(cadeia, FECHA_PARENTESES, tokenGlobal, textoAntes, input);
            break;

        case IMPRIMA:
            consumirToken(cadeia, IMPRIMA, tokenGlobal, textoAntes, input);
            consumirToken(cadeia, ABRE_PARENTESES, tokenGlobal, textoAntes, input);
            exprIter(cadeia, tokenGlobal, textoAntes, input);
            consumirToken(cadeia, FECHA_PARENTESES, tokenGlobal, textoAntes, input);
            break;

        default:
            tratarErroSintatico(cadeia, input);
            break;
    }
}

void comandos1(void *cadeia, int *tokenGlobal, bool *textoAntes, char *input){
    switch(*tokenGlobal){
        case PONTO_VIRGULA:
            break;

        case ABRE_PARENTESES:
            consumirToken(cadeia, ABRE_PARENTESES, tokenGlobal, textoAntes, input);
            exprIter(cadeia, tokenGlobal, textoAntes, input);
            consumirToken(cadeia, FECHA_PARENTESES, tokenGlobal, textoAntes, input);
            break;

        case ABRE_COLCHETE:
            consumirToken(cadeia, ABRE_COLCHETE, tokenGlobal, textoAntes, input);
            exprIter(cadeia, tokenGlobal, textoAntes, input);
            consumirToken(cadeia, FECHA_COLCHETE, tokenGlobal, textoAntes, input);
            consumirToken(cadeia, ATRIBUICAO, tokenGlobal, textoAntes, input);
            expressao(cadeia, tokenGlobal, textoAntes, input);
            break;

        case ATRIBUICAO:
            consumirToken(cadeia, ATRIBUICAO, tokenGlobal, textoAntes, input);
            expressao(cadeia, tokenGlobal, textoAntes, input);
            break;

        default:
            tratarErroSintatico(cadeia, input);
            break;
    }
}

void comandos2(void *cadeia, int *tokenGlobal, bool *textoAntes, char *input){
    switch(*tokenGlobal){
        case FIM:
            consumirToken(cadeia, FIM, tokenGlobal, textoAntes, input);
            consumirToken(cadeia, SE, tokenGlobal, textoAntes, input);
            break;

        case SENAO:
            consumirToken(cadeia, SENAO, tokenGlobal, textoAntes, input);
            listaComandos(cadeia, tokenGlobal, textoAntes, input);
            consumirToken(cadeia, FIM, tokenGlobal, textoAntes, input);
            consumirToken(cadeia, SE, tokenGlobal, textoAntes, input);
            break;

        default:
            tratarErroSintatico(cadeia, input);
            break;
    }
}

void comandos3(void *cadeia, int *tokenGlobal, bool *textoAntes, char *input){
    switch(*tokenGlobal){
        case FACA:
            consumirToken(cadeia, FACA, tokenGlobal, textoAntes, input);
            listaComandos(cadeia, tokenGlobal, textoAntes, input);
            consumirToken(cadeia, FIM, tokenGlobal, textoAntes, input);
            consumirToken(cadeia, PARA, tokenGlobal, textoAntes, input);
            break;

        case PASSO:
            consumirToken(cadeia, PASSO, tokenGlobal, textoAntes, input);
            expressao(cadeia, tokenGlobal, textoAntes, input);
            consumirToken(cadeia, FACA, tokenGlobal, textoAntes, input);
            listaComandos(cadeia, tokenGlobal, textoAntes, input);
            consumirToken(cadeia, FIM, tokenGlobal, textoAntes, input);
            consumirToken(cadeia, PARA, tokenGlobal, textoAntes, input);
            break;

        default:
            tratarErroSintatico(cadeia, input);
            break;
    }
}

void expressao(void *cadeia, int *tokenGlobal, bool *textoAntes, char *input){
    switch(*tokenGlobal){
        case ID:
        case NUMERO_INTEIRO:
        case NUMERO_REAL:
        case NAO:
        case VERDADEIRO:
        case FALSO:
        case STRING:
        case ABRE_PARENTESES:
        case MAIS:
        case MENOS:
            expressaoSimples(cadeia, tokenGlobal, textoAntes, input);
            expressaoLinha(cadeia, tokenGlobal, textoAntes, input);
            break;

        default:
            tratarErroSintatico(cadeia, input);
            break;
    }
}

void expressaoLinha(void *cadeia, int *tokenGlobal, bool *textoAntes, char *input){
    switch(*tokenGlobal){
        case PONTO_VIRGULA:
        case FECHA_PARENTESES:
        case FECHA_COLCHETE:
        case VIRGULA:
        case ENTAO:
        case FACA:
        case ATE:
        case PASSO:
            break;

        case IGUAL:
        case DIFERENTE:
        case MENOR:
        case MENOR_IGUAL:
        case MAIOR:
        case MAIOR_IGUAL:
            operadorRelacional(cadeia, tokenGlobal, textoAntes, input);
            expressaoSimples(cadeia, tokenGlobal, textoAntes, input);
            expressaoLinha(cadeia, tokenGlobal, textoAntes, input);
            break;

        default:
            tratarErroSintatico(cadeia, input);
            break;
    }
}

void expressaoSimples(void *cadeia, int *tokenGlobal, bool *textoAntes, char *input){
    switch(*tokenGlobal){
        case ID:
        case NUMERO_INTEIRO:
        case NUMERO_REAL:
        case NAO:
        case VERDADEIRO:
        case FALSO:
        case STRING:
        case ABRE_PARENTESES:
            termo(cadeia, tokenGlobal, textoAntes, input);
            expressaoSimplesLinha(cadeia, tokenGlobal, textoAntes, input);
            break;

        case MAIS:
        case MENOS:
            operadorBinario(cadeia, tokenGlobal, textoAntes, input);
            termo(cadeia, tokenGlobal, textoAntes, input);
            expressaoSimplesLinha(cadeia, tokenGlobal, textoAntes, input);
            break;

        default:
            tratarErroSintatico(cadeia, input);
            break;
    }
}

void expressaoSimplesLinha(void *cadeia, int *tokenGlobal, bool *textoAntes, char *input){
    switch(*tokenGlobal){
        case PONTO_VIRGULA:
        case FECHA_PARENTESES:
        case FECHA_COLCHETE:
        case VIRGULA:
        case IGUAL:
        case DIFERENTE:
        case MENOR:
        case MENOR_IGUAL:
        case MAIOR:
        case MAIOR_IGUAL:
        case ENTAO:
        case FACA:
        case ATE:
        case PASSO:
            break;

        case MAIS:
        case MENOS:
            operadorBinario(cadeia, tokenGlobal, textoAntes, input);
            termo(cadeia, tokenGlobal, textoAntes, input);
            expressaoSimplesLinha(cadeia, tokenGlobal, textoAntes, input);
            break;

        case OU:
            consumirToken(cadeia, OU, tokenGlobal, textoAntes, input);
            termo(cadeia, tokenGlobal, textoAntes, input);
            expressaoSimplesLinha(cadeia, tokenGlobal, textoAntes, input);
            break;

        default:
            tratarErroSintatico(cadeia, input);
            break;
    }
}

void operadorRelacional(void *cadeia, int *tokenGlobal, bool *textoAntes, char *input){
    switch(*tokenGlobal){
        case IGUAL:
            consumirToken(cadeia, IGUAL, tokenGlobal, textoAntes, input);
            break;

        case DIFERENTE:
            consumirToken(cadeia, DIFERENTE, tokenGlobal, textoAntes, input);
            break;

        case MAIOR:
            consumirToken(cadeia, MAIOR, tokenGlobal, textoAntes, input);
            break;

        case MAIOR_IGUAL:
            consumirToken(cadeia, MAIOR_IGUAL, tokenGlobal, textoAntes, input);
            break;

        case MENOR:
            consumirToken(cadeia, MENOR, tokenGlobal, textoAntes, input);
            break;

        case MENOR_IGUAL:
            consumirToken(cadeia, MENOR_IGUAL, tokenGlobal, textoAntes, input);
            break;

        default:
            tratarErroSintatico(cadeia, input);
            break;
    }
}

void operadorBinario(void *cadeia, int *tokenGlobal, bool *textoAntes, char *input){
    switch(*tokenGlobal){
        case MAIS:
            consumirToken(cadeia, MAIS, tokenGlobal, textoAntes, input);
            break;

        case MENOS:
            consumirToken(cadeia, MENOS, tokenGlobal, textoAntes, input);
            break;

        default:
            tratarErroSintatico(cadeia, input);
            break;
    }
}

void termo(void *cadeia, int *tokenGlobal, bool *textoAntes, char *input){
    switch(*tokenGlobal){
        case ID:
        case NUMERO_INTEIRO:
        case NUMERO_REAL:
        case NAO:
        case VERDADEIRO:
        case FALSO:
        case STRING:
        case ABRE_PARENTESES:
            fator(cadeia, tokenGlobal, textoAntes, input);
            termoLinha(cadeia, tokenGlobal, textoAntes, input);
            break;

        default:
            tratarErroSintatico(cadeia, input);
            break;
    }
}

void termoLinha(void *cadeia, int *tokenGlobal, bool *textoAntes, char *input){
    switch(*tokenGlobal){
        case PONTO_VIRGULA:
        case FECHA_PARENTESES:
        case FECHA_COLCHETE:
        case VIRGULA:
        case IGUAL:
        case DIFERENTE:
        case MAIOR:
        case MAIOR_IGUAL:
        case MENOR:
        case MENOR_IGUAL:
        case MAIS:
        case MENOS:
        case OU:
        case ENTAO:
        case FACA:
        case ATE:
        case PASSO:
            break;

        case VEZES:
            consumirToken(cadeia, VEZES, tokenGlobal, textoAntes, input);
            fator(cadeia, tokenGlobal, textoAntes, input);
            termoLinha(cadeia, tokenGlobal, textoAntes, input);
            break;

        case DIVISAO:
            consumirToken(cadeia, DIVISAO, tokenGlobal, textoAntes, input);
            fator(cadeia, tokenGlobal, textoAntes, input);
            termoLinha(cadeia, tokenGlobal, textoAntes, input);
            break;

        case DIV:
            consumirToken(cadeia, DIV, tokenGlobal, textoAntes, input);
            fator(cadeia, tokenGlobal, textoAntes, input);
            termoLinha(cadeia, tokenGlobal, textoAntes, input);
            break;

        case AND:
            consumirToken(cadeia, AND, tokenGlobal, textoAntes, input);
            fator(cadeia, tokenGlobal, textoAntes, input);
            termoLinha(cadeia, tokenGlobal, textoAntes, input);
            break;

        default:
            tratarErroSintatico(cadeia, input);
            break;
    }
}

void fator(void *cadeia, int *tokenGlobal, bool *textoAntes, char *input){
    switch(*tokenGlobal){
        case ID:
            consumirToken(cadeia, ID, tokenGlobal, textoAntes, input);
            fatorLinha(cadeia, tokenGlobal, textoAntes, input);
            break;

        case NUMERO_INTEIRO:
            consumirToken(cadeia, NUMERO_INTEIRO, tokenGlobal, textoAntes, input);
            break;

        case NUMERO_REAL:
            consumirToken(cadeia, NUMERO_REAL, tokenGlobal, textoAntes, input);
            break;

        case VERDADEIRO:
            consumirToken(cadeia, VERDADEIRO, tokenGlobal, textoAntes, input);
            break;

        case FALSO:
            consumirToken(cadeia, FALSO, tokenGlobal, textoAntes, input);
            break;

        case STRING:
            consumirToken(cadeia, STRING, tokenGlobal, textoAntes, input);
            break;

        case NAO:
            consumirToken(cadeia, NAO, tokenGlobal, textoAntes, input);
            fator(cadeia, tokenGlobal, textoAntes, input);
            break;

        case ABRE_PARENTESES:
            consumirToken(cadeia, ABRE_PARENTESES, tokenGlobal, textoAntes, input);
            expressao(cadeia, tokenGlobal, textoAntes, input);
            consumirToken(cadeia, FECHA_PARENTESES, tokenGlobal, textoAntes, input);
            break;

        default:
            tratarErroSintatico(cadeia, input);
            break;
    }
}

void fatorLinha(void *cadeia, int *tokenGlobal, bool *textoAntes, char *input){
    switch(*tokenGlobal){
        case PONTO_VIRGULA:
        case FECHA_PARENTESES:
        case FECHA_COLCHETE:
        case VIRGULA:
        case IGUAL:
        case DIFERENTE:
        case MAIOR:
        case MAIOR_IGUAL:
        case MENOR:
        case MENOR_IGUAL:
        case MAIS:
        case MENOS:
        case OU:
        case VEZES:
        case DIVISAO:
        case DIV:
        case AND:
        case ENTAO:
        case FACA:
        case ATE:
        case PASSO:
            break;

        case ABRE_PARENTESES:
            consumirToken(cadeia, ABRE_PARENTESES, tokenGlobal, textoAntes, input);
            exprIter(cadeia, tokenGlobal, textoAntes, input);
            consumirToken(cadeia, FECHA_PARENTESES, tokenGlobal, textoAntes, input);
            break;

        case ABRE_COLCHETE:
            consumirToken(cadeia, ABRE_COLCHETE, tokenGlobal, textoAntes, input);
            exprIter(cadeia, tokenGlobal, textoAntes, input);
            consumirToken(cadeia, FECHA_COLCHETE, tokenGlobal, textoAntes, input);
            break;

        default:
            tratarErroSintatico(cadeia, input);
            break;
    }
}

void variavel(void *cadeia, int *tokenGlobal, bool *textoAntes, char *input){
    switch(*tokenGlobal){
        case ID:
            consumirToken(cadeia, ID, tokenGlobal, textoAntes, input);
            variavelLinha(cadeia, tokenGlobal, textoAntes, input);
            break;

        default:
            tratarErroSintatico(cadeia, input);
            break;
    }
}

void variavelLinha(void *cadeia, int *tokenGlobal, bool *textoAntes, char *input){
    switch(*tokenGlobal){
        case FECHA_PARENTESES:
            break;

        case ABRE_COLCHETE:
            consumirToken(cadeia, ABRE_COLCHETE, tokenGlobal, textoAntes, input);
            exprIter(cadeia, tokenGlobal, textoAntes, input);
            consumirToken(cadeia, FECHA_COLCHETE, tokenGlobal, textoAntes, input);
            break;

        default:
            tratarErroSintatico(cadeia, input);
            break;
    }
}

void exprIter(void *cadeia, int *tokenGlobal, bool *textoAntes, char *input){
    switch(*tokenGlobal){
        case ID:
        case NUMERO_INTEIRO:
        case NUMERO_REAL:
        case NAO:
        case VERDADEIRO:
        case FALSO:
        case STRING:
        case MAIS:
        case MENOS:
        case ABRE_PARENTESES:
            expressao(cadeia, tokenGlobal, textoAntes, input);
            exprIterLinha(cadeia, tokenGlobal, textoAntes, input);
            break;

        default:
            tratarErroSintatico(cadeia, input);
            break;
    }
}

void exprIterLinha(void *cadeia, int *tokenGlobal, bool *textoAntes, char *input){
    switch(*tokenGlobal){
        case FECHA_PARENTESES:
        case FECHA_COLCHETE:
            break;

        case VIRGULA:
            consumirToken(cadeia, VIRGULA, tokenGlobal, textoAntes, input);
            exprIter(cadeia, tokenGlobal, textoAntes, input);
            break;

        default:
            tratarErroSintatico(cadeia, input);
            break;
    }
}

void defineID(int *tokenGlobal){
    if(*tokenGlobal != -1 && *tokenGlobal != 1 && *tokenGlobal != EOF_TOKEN){
        if(*tokenGlobal >= NUMERO_INTEIRO && *tokenGlobal <= DIVISAO){
            return;
        }

        if(*tokenGlobal >= DIFERENTE && *tokenGlobal <= ATRIBUICAO){
            return;
        }

        if(*tokenGlobal >= PROCEDIMENTO && *tokenGlobal <= COMENT_BLOCO){
            return;
        }

        if(*tokenGlobal == ALGORITMO || *tokenGlobal == ATE || *tokenGlobal == INICIO || *tokenGlobal == IMPRIMA || *tokenGlobal == FIM || *tokenGlobal == FUNCAO || *tokenGlobal == FACA || *tokenGlobal == FALSO || *tokenGlobal == VARIAVEIS || *tokenGlobal == VETOR){
            return;
        }

        if(*tokenGlobal == VERDADEIRO || *tokenGlobal == INTEIRO || *tokenGlobal == REAL || *tokenGlobal == REPITA || *tokenGlobal == SE || *tokenGlobal == SENAO || *tokenGlobal == AND || *tokenGlobal == ENTAO || *tokenGlobal == ENQUANTO || *tokenGlobal == DE || *tokenGlobal == DIV){
            return;
        }

        if(*tokenGlobal == OU || *tokenGlobal == NAO || *tokenGlobal == TIPO || *tokenGlobal == LEIA || *tokenGlobal == LOGICO || *tokenGlobal == MATRIZ || *tokenGlobal == CARACTERE || *tokenGlobal == PARA || *tokenGlobal == PASSO || *tokenGlobal == PROCEDIMENTO){
            return;
        }

        *tokenGlobal = ID;
    }
}