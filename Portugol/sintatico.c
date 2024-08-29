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
    if(*tokenGlobal == ALGORITMO){
        programa(cadeia, tokenGlobal, textoAntes, input);
        consumirToken(cadeia, EOF_TOKEN, tokenGlobal, textoAntes, input);
    }else{
        tratarErroSintatico(cadeia, input);
    }
}

void programa(void *cadeia, int *tokenGlobal, bool *textoAntes, char *input){
    if(*tokenGlobal == ALGORITMO){
        consumirToken(cadeia, ALGORITMO, tokenGlobal, textoAntes, input);
        consumirToken(cadeia, ID, tokenGlobal, textoAntes, input);
        consumirToken(cadeia, PONTO_VIRGULA, tokenGlobal, textoAntes, input);
        blocoVariaveis(cadeia, tokenGlobal, textoAntes, input);
        procedimentoFuncao(cadeia, tokenGlobal, textoAntes, input);
        blocoComandos(cadeia, tokenGlobal, textoAntes, input);
        consumirToken(cadeia, PONTO, tokenGlobal, textoAntes, input);
    }else if(*tokenGlobal == EOF_TOKEN){
        return;
    }else{
        tratarErroSintatico(cadeia, input);
    }
}

void procedimentoFuncao(void *cadeia, int *tokenGlobal, bool *textoAntes, char *input){
    if(*tokenGlobal == PROCEDIMENTO){
        declaraProcedimento(cadeia, tokenGlobal, textoAntes, input);
        procedimentoFuncao(cadeia, tokenGlobal, textoAntes, input);
    }else if(*tokenGlobal == FUNCAO){
        declaraFuncao(cadeia, tokenGlobal, textoAntes, input);
        procedimentoFuncao(cadeia, tokenGlobal, textoAntes, input);
    }else if(*tokenGlobal == INICIO){
        return;
    }else{
        tratarErroSintatico(cadeia, input);
    }
}

void declaraProcedimento(void *cadeia, int *tokenGlobal, bool *textoAntes, char *input){
    if(*tokenGlobal == PROCEDIMENTO){
        consumirToken(cadeia, PROCEDIMENTO, tokenGlobal, textoAntes, input);
        consumirToken(cadeia, ID, tokenGlobal, textoAntes, input);
        parametros(cadeia, tokenGlobal, textoAntes, input);
        consumirToken(cadeia, PONTO_VIRGULA, tokenGlobal, textoAntes, input);
        declaraParametros(cadeia, tokenGlobal, textoAntes, input);
        blocoVariaveis(cadeia, tokenGlobal, textoAntes, input);
        blocoComandos(cadeia, tokenGlobal, textoAntes, input);
        consumirToken(cadeia, PONTO_VIRGULA, tokenGlobal, textoAntes, input);
    }else{
        tratarErroSintatico(cadeia, input);
    }
}

void declaraFuncao(void *cadeia, int *tokenGlobal, bool *textoAntes, char *input){
    if(*tokenGlobal == FUNCAO){
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
    }else{
        tratarErroSintatico(cadeia, input);
    }
}

void parametros(void *cadeia, int *tokenGlobal, bool *textoAntes, char *input){
    if(*tokenGlobal == PONTO_VIRGULA || *tokenGlobal == DOIS_PONTOS){
        return;
    }else if(*tokenGlobal == ABRE_PARENTESES){
        consumirToken(cadeia, ABRE_PARENTESES, tokenGlobal, textoAntes, input);
        declaraIdentificador(cadeia, tokenGlobal, textoAntes, input);
        consumirToken(cadeia, FECHA_PARENTESES, tokenGlobal, textoAntes, input);
    }else{
        tratarErroSintatico(cadeia, input);
    }
}

void declaraParametros(void *cadeia, int *tokenGlobal, bool *textoAntes, char *input){
    if(*tokenGlobal == ID || *tokenGlobal == TIPO || *tokenGlobal == INTEIRO || *tokenGlobal == REAL || *tokenGlobal == CARACTERE || *tokenGlobal == LOGICO){
        declaracoes(cadeia, tokenGlobal, textoAntes, input);
    }else if(*tokenGlobal == PROCEDIMENTO || *tokenGlobal == FUNCAO || *tokenGlobal == VARIAVEIS || *tokenGlobal == INICIO){
        return;
    }else{
        tratarErroSintatico(cadeia, input);
    }
}

void blocoVariaveis(void *cadeia, int *tokenGlobal, bool *textoAntes, char *input){
    if(*tokenGlobal == PROCEDIMENTO || *tokenGlobal == FUNCAO || *tokenGlobal == INICIO || *tokenGlobal == EOF_TOKEN){
        return;
    }else if(*tokenGlobal == VARIAVEIS){
        consumirToken(cadeia, VARIAVEIS, tokenGlobal, textoAntes, input);
        declaracoes(cadeia, tokenGlobal, textoAntes, input);        
    }else{
        tratarErroSintatico(cadeia, input);
    }
}

void declaracoes(void *cadeia, int *tokenGlobal, bool *textoAntes, char *input){
    if(*tokenGlobal == ID || *tokenGlobal == INTEIRO || *tokenGlobal == REAL || *tokenGlobal == CARACTERE || *tokenGlobal == LOGICO){
        declaraVariaveis(cadeia, tokenGlobal, textoAntes, input);
        declaracoesAux(cadeia, tokenGlobal, textoAntes, input);        
    }else if(*tokenGlobal == TIPO){
        declaraTipo(cadeia, tokenGlobal, textoAntes, input);
        declaracoesAux(cadeia, tokenGlobal, textoAntes, input);
    }else{
        tratarErroSintatico(cadeia, input);
    }
}

void declaracoesAux(void *cadeia, int *tokenGlobal, bool *textoAntes, char *input){
    if(*tokenGlobal == ID || *tokenGlobal == TIPO || *tokenGlobal == INTEIRO || *tokenGlobal == REAL || *tokenGlobal == CARACTERE || *tokenGlobal == LOGICO){
        declaracoes(cadeia, tokenGlobal, textoAntes, input);
    }else if(*tokenGlobal == PROCEDIMENTO || *tokenGlobal == FUNCAO || *tokenGlobal == VARIAVEIS || *tokenGlobal == INICIO || *tokenGlobal == EOF_TOKEN){
        return;
    }else{
        tratarErroSintatico(cadeia, input);
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
    if(*tokenGlobal == ID || *tokenGlobal == INTEIRO || *tokenGlobal == REAL || *tokenGlobal == CARACTERE || *tokenGlobal == LOGICO){
        tipoBasico(cadeia, tokenGlobal, textoAntes, input);
        consumirToken(cadeia, DOIS_PONTOS, tokenGlobal, textoAntes, input);
        declaraIdentificador(cadeia, tokenGlobal, textoAntes, input);
        consumirToken(cadeia, PONTO_VIRGULA, tokenGlobal, textoAntes, input);        
    }else{
        tratarErroSintatico(cadeia, input);
    }
}

void declaraIdentificador(void *cadeia, int *tokenGlobal, bool *textoAntes, char *input){
    if(*tokenGlobal == ID){
        consumirToken(cadeia, ID, tokenGlobal, textoAntes, input);
        declaraIdentificadorAux(cadeia, tokenGlobal, textoAntes, input);
    }else{
        tratarErroSintatico(cadeia, input);
    }
}

void declaraIdentificadorAux(void *cadeia, int *tokenGlobal, bool *textoAntes, char *input){
    if(*tokenGlobal == PONTO_VIRGULA || *tokenGlobal == FECHA_PARENTESES){
        return;
    }else if(*tokenGlobal == VIRGULA){
        consumirToken(cadeia, VIRGULA, tokenGlobal, textoAntes, input);
        declaraIdentificador(cadeia, tokenGlobal, textoAntes, input);
    }else{
        tratarErroSintatico(cadeia, input);
    }
}

void vetorMatriz(void *cadeia, int *tokenGlobal, bool *textoAntes, char *input){
    if(*tokenGlobal == VETOR){
        consumirToken(cadeia, VETOR, tokenGlobal, textoAntes, input);
    }else if(*tokenGlobal == MATRIZ){
        consumirToken(cadeia, MATRIZ, tokenGlobal, textoAntes, input);
    }else{
        tratarErroSintatico(cadeia, input);
    }
}

void dimensoes(void *cadeia, int *tokenGlobal, bool *textoAntes, char *input){
    if(*tokenGlobal == NUMERO_INTEIRO){
        consumirToken(cadeia, NUMERO_INTEIRO, tokenGlobal, textoAntes, input);
        consumirToken(cadeia, DOIS_PONTOS, tokenGlobal, textoAntes, input);
        consumirToken(cadeia, NUMERO_INTEIRO, tokenGlobal, textoAntes, input);
        dimensoesAux(cadeia, tokenGlobal, textoAntes, input);        
    }else{
        tratarErroSintatico(cadeia, input);
    }
}

void dimensoesAux(void *cadeia, int *tokenGlobal, bool *textoAntes, char *input){
    if(*tokenGlobal == FECHA_COLCHETE){
        return;
    }else if(*tokenGlobal == VIRGULA){
        consumirToken(cadeia, VIRGULA, tokenGlobal, textoAntes, input);
        dimensoes(cadeia, tokenGlobal, textoAntes, input);
    }else{
        tratarErroSintatico(cadeia, input);
    }
}

void tipoBasico(void *cadeia, int *tokenGlobal, bool *textoAntes, char *input){
    if(*tokenGlobal == ID){
        consumirToken(cadeia, ID, tokenGlobal, textoAntes, input);
    }else if(*tokenGlobal == INTEIRO){
        consumirToken(cadeia, INTEIRO, tokenGlobal, textoAntes, input);
    }else if(*tokenGlobal == REAL){
        consumirToken(cadeia, REAL, tokenGlobal, textoAntes, input);
    }else if(*tokenGlobal == CARACTERE){
        consumirToken(cadeia, CARACTERE, tokenGlobal, textoAntes, input);
    }else if(*tokenGlobal == LOGICO){
        consumirToken(cadeia, LOGICO, tokenGlobal, textoAntes, input);
    }else{
        tratarErroSintatico(cadeia, input);
    }
}

void blocoComandos(void *cadeia, int *tokenGlobal, bool *textoAntes, char *input){
    if(*tokenGlobal == INICIO){
        consumirToken(cadeia, INICIO, tokenGlobal, textoAntes, input);
        listaComandos(cadeia, tokenGlobal, textoAntes, input);
        consumirToken(cadeia, FIM, tokenGlobal, textoAntes, input);
    }else{
        tratarErroSintatico(cadeia, input);
    }
}

void listaComandos(void *cadeia, int *tokenGlobal, bool *textoAntes, char *input){
    if(*tokenGlobal == ID || *tokenGlobal == SE || *tokenGlobal == ENQUANTO || *tokenGlobal == PARA || *tokenGlobal == REPITA || *tokenGlobal == LEIA || *tokenGlobal == IMPRIMA){
        comandos(cadeia, tokenGlobal, textoAntes, input);
        consumirToken(cadeia, PONTO_VIRGULA, tokenGlobal, textoAntes, input);
        listaComandosAux(cadeia, tokenGlobal, textoAntes, input);        
    }else{
        tratarErroSintatico(cadeia, input);
    }
}

void listaComandosAux(void *cadeia, int *tokenGlobal, bool *textoAntes, char *input){
    if(*tokenGlobal == ID || *tokenGlobal == SE || *tokenGlobal == ENQUANTO || *tokenGlobal == PARA || *tokenGlobal == REPITA || *tokenGlobal == LEIA || *tokenGlobal == IMPRIMA){
        listaComandos(cadeia, tokenGlobal, textoAntes, input);
    }else if(*tokenGlobal == FIM || *tokenGlobal == SENAO || *tokenGlobal == ATE){
        return;
    }else{
        tratarErroSintatico(cadeia, input);
    }
}

void comandos(void *cadeia, int *tokenGlobal, bool *textoAntes, char *input){
    if(*tokenGlobal == ID){
        consumirToken(cadeia, ID, tokenGlobal, textoAntes, input);
        comandos1(cadeia, tokenGlobal, textoAntes, input);        
    }else if(*tokenGlobal == SE){
        consumirToken(cadeia, SE, tokenGlobal, textoAntes, input);
        expressao(cadeia, tokenGlobal, textoAntes, input);
        consumirToken(cadeia, ENTAO, tokenGlobal, textoAntes, input);
        listaComandos(cadeia, tokenGlobal, textoAntes, input);
        comandos2(cadeia, tokenGlobal, textoAntes, input);        
    }else if(*tokenGlobal == ENQUANTO){
        consumirToken(cadeia, ENQUANTO, tokenGlobal, textoAntes, input);
        expressao(cadeia, tokenGlobal, textoAntes, input);
        consumirToken(cadeia, FACA, tokenGlobal, textoAntes, input);
        listaComandos(cadeia, tokenGlobal, textoAntes, input);
        consumirToken(cadeia, FIM, tokenGlobal, textoAntes, input);
        consumirToken(cadeia, ENQUANTO, tokenGlobal, textoAntes, input);        
    }else if(*tokenGlobal == PARA){
        consumirToken(cadeia, PARA, tokenGlobal, textoAntes, input);
        consumirToken(cadeia, ID, tokenGlobal, textoAntes, input);
        consumirToken(cadeia, DE, tokenGlobal, textoAntes, input);
        expressao(cadeia, tokenGlobal, textoAntes, input);
        consumirToken(cadeia, ATE, tokenGlobal, textoAntes, input);
        expressao(cadeia, tokenGlobal, textoAntes, input);
        comandos3(cadeia, tokenGlobal, textoAntes, input);        
    }else if(*tokenGlobal == REPITA){
        consumirToken(cadeia, REPITA, tokenGlobal, textoAntes, input);
        listaComandos(cadeia, tokenGlobal, textoAntes, input);
        consumirToken(cadeia, ATE, tokenGlobal, textoAntes, input);
        expressao(cadeia, tokenGlobal, textoAntes, input);
    }else if(*tokenGlobal == LEIA){
        consumirToken(cadeia, LEIA, tokenGlobal, textoAntes, input);
        consumirToken(cadeia, ABRE_PARENTESES, tokenGlobal, textoAntes, input);
        variavel(cadeia, tokenGlobal, textoAntes, input);
        consumirToken(cadeia, FECHA_PARENTESES, tokenGlobal, textoAntes, input);
    }else if(*tokenGlobal == IMPRIMA){
        consumirToken(cadeia, IMPRIMA, tokenGlobal, textoAntes, input);
        consumirToken(cadeia, ABRE_PARENTESES, tokenGlobal, textoAntes, input);
        exprIter(cadeia, tokenGlobal, textoAntes, input);
        consumirToken(cadeia, FECHA_PARENTESES, tokenGlobal, textoAntes, input);
    }else{
        tratarErroSintatico(cadeia, input);
    }
}

void comandos1(void *cadeia, int *tokenGlobal, bool *textoAntes, char *input){
    if(*tokenGlobal == PONTO_VIRGULA){
        return;
    }else if(*tokenGlobal == ABRE_PARENTESES){
        consumirToken(cadeia, ABRE_PARENTESES, tokenGlobal, textoAntes, input);
        exprIter(cadeia, tokenGlobal, textoAntes, input);
        consumirToken(cadeia, FECHA_PARENTESES, tokenGlobal, textoAntes, input);        
    }else if(*tokenGlobal == ABRE_COLCHETE){
        consumirToken(cadeia, ABRE_COLCHETE, tokenGlobal, textoAntes, input);
        exprIter(cadeia, tokenGlobal, textoAntes, input);
        consumirToken(cadeia, FECHA_COLCHETE, tokenGlobal, textoAntes, input);
        consumirToken(cadeia, ATRIBUICAO, tokenGlobal, textoAntes, input);
        expressao(cadeia, tokenGlobal, textoAntes, input);
    }else if(*tokenGlobal == ATRIBUICAO){
        consumirToken(cadeia, ATRIBUICAO, tokenGlobal, textoAntes, input);
        expressao(cadeia, tokenGlobal, textoAntes, input);
    }else{
        tratarErroSintatico(cadeia, input);
    }
}

void comandos2(void *cadeia, int *tokenGlobal, bool *textoAntes, char *input){
    if(*tokenGlobal == FIM){
        consumirToken(cadeia, FIM, tokenGlobal, textoAntes, input);
        consumirToken(cadeia, SE, tokenGlobal, textoAntes, input);        
    }else if(*tokenGlobal == SENAO){
        consumirToken(cadeia, SENAO, tokenGlobal, textoAntes, input);
        listaComandos(cadeia, tokenGlobal, textoAntes, input);
        consumirToken(cadeia, FIM, tokenGlobal, textoAntes, input);
        consumirToken(cadeia, SE, tokenGlobal, textoAntes, input);        
    }else{
        tratarErroSintatico(cadeia, input);
    }
}

void comandos3(void *cadeia, int *tokenGlobal, bool *textoAntes, char *input){
    if(*tokenGlobal == FACA){
        consumirToken(cadeia, FACA, tokenGlobal, textoAntes, input);
        listaComandos(cadeia, tokenGlobal, textoAntes, input);
        consumirToken(cadeia, FIM, tokenGlobal, textoAntes, input);
        consumirToken(cadeia, PARA, tokenGlobal, textoAntes, input);        
    }else if(*tokenGlobal == PASSO){
        consumirToken(cadeia, PASSO, tokenGlobal, textoAntes, input);
        expressao(cadeia, tokenGlobal, textoAntes, input);
        consumirToken(cadeia, FACA, tokenGlobal, textoAntes, input);
        listaComandos(cadeia, tokenGlobal, textoAntes, input);
        consumirToken(cadeia, FIM, tokenGlobal, textoAntes, input);
        consumirToken(cadeia, PARA, tokenGlobal, textoAntes, input);        
    }else{
        tratarErroSintatico(cadeia, input);
    }
}

void expressao(void *cadeia, int *tokenGlobal, bool *textoAntes, char *input){
    if(*tokenGlobal == ID || *tokenGlobal == NUMERO_INTEIRO || *tokenGlobal == NUMERO_REAL || *tokenGlobal == NAO || *tokenGlobal == VERDADEIRO || *tokenGlobal == FALSO || *tokenGlobal == STRING || *tokenGlobal == ABRE_PARENTESES || *tokenGlobal == MAIS || *tokenGlobal == MENOS){
        expressaoSimples(cadeia, tokenGlobal, textoAntes, input);
        expressaoAux(cadeia, tokenGlobal, textoAntes, input);        
    }else{
        tratarErroSintatico(cadeia, input);
    }
}

void expressaoAux(void *cadeia, int *tokenGlobal, bool *textoAntes, char *input){
    if(*tokenGlobal == PONTO_VIRGULA || *tokenGlobal == FECHA_PARENTESES || *tokenGlobal == FECHA_COLCHETE || *tokenGlobal == VIRGULA || *tokenGlobal == ENTAO || *tokenGlobal == FACA || *tokenGlobal == ATE || *tokenGlobal == PASSO){
        return;
    }else if(*tokenGlobal == IGUAL || *tokenGlobal == DIFERENTE || *tokenGlobal == MENOR || *tokenGlobal == MENOR_IGUAL || *tokenGlobal == MAIOR || *tokenGlobal == MAIOR_IGUAL){
        operadorRelacional(cadeia, tokenGlobal, textoAntes, input);
        expressaoSimples(cadeia, tokenGlobal, textoAntes, input);
        expressaoAux(cadeia, tokenGlobal, textoAntes, input);        
    }else{
        tratarErroSintatico(cadeia, input);
    }
}

void expressaoSimples(void *cadeia, int *tokenGlobal, bool *textoAntes, char *input){
    if(*tokenGlobal == ID || *tokenGlobal == NUMERO_INTEIRO || *tokenGlobal == NUMERO_REAL || *tokenGlobal == NAO || *tokenGlobal == VERDADEIRO || *tokenGlobal == FALSO || *tokenGlobal == STRING || *tokenGlobal == ABRE_PARENTESES){
        termo(cadeia, tokenGlobal, textoAntes, input);
        expressaoSimplesAux(cadeia, tokenGlobal, textoAntes, input);        
    }else if(*tokenGlobal == MAIS || *tokenGlobal == MENOS){
        operadorBinario(cadeia, tokenGlobal, textoAntes, input);
        termo(cadeia, tokenGlobal, textoAntes, input);
        expressaoSimplesAux(cadeia, tokenGlobal, textoAntes, input);        
    }else{
        tratarErroSintatico(cadeia, input);
    }
}

void expressaoSimplesAux(void *cadeia, int *tokenGlobal, bool *textoAntes, char *input){
    if(*tokenGlobal == PONTO_VIRGULA || *tokenGlobal == FECHA_PARENTESES || *tokenGlobal == FECHA_COLCHETE || *tokenGlobal == VIRGULA || *tokenGlobal == IGUAL || *tokenGlobal == DIFERENTE || *tokenGlobal == MENOR || *tokenGlobal == MENOR_IGUAL || *tokenGlobal == MAIOR || *tokenGlobal == MAIOR_IGUAL || *tokenGlobal == ENTAO || *tokenGlobal == FACA || *tokenGlobal == ATE || *tokenGlobal == PASSO){
        return;
    }else if(*tokenGlobal == MAIS || *tokenGlobal == MENOS){
        operadorBinario(cadeia, tokenGlobal, textoAntes, input);
        termo(cadeia, tokenGlobal, textoAntes, input);
        expressaoSimplesAux(cadeia, tokenGlobal, textoAntes, input);        
    }else if(*tokenGlobal == OU){
        consumirToken(cadeia, OU, tokenGlobal, textoAntes, input);
        termo(cadeia, tokenGlobal, textoAntes, input);
        expressaoSimplesAux(cadeia, tokenGlobal, textoAntes, input);        
    }else{
        tratarErroSintatico(cadeia, input);
    }
}

void operadorRelacional(void *cadeia, int *tokenGlobal, bool *textoAntes, char *input){
    if(*tokenGlobal == IGUAL){
        consumirToken(cadeia, IGUAL, tokenGlobal, textoAntes, input);
    }else if(*tokenGlobal == DIFERENTE){
        consumirToken(cadeia, DIFERENTE, tokenGlobal, textoAntes, input);
    }else if(*tokenGlobal == MAIOR){
        consumirToken(cadeia, MAIOR, tokenGlobal, textoAntes, input);
    }else if(*tokenGlobal == MAIOR_IGUAL){
        consumirToken(cadeia, MAIOR_IGUAL, tokenGlobal, textoAntes, input);
    }else if(*tokenGlobal == MENOR){
        consumirToken(cadeia, MENOR, tokenGlobal, textoAntes, input);
    }else if(*tokenGlobal == MENOR_IGUAL){
        consumirToken(cadeia, MENOR_IGUAL, tokenGlobal, textoAntes, input);
    }else{
        tratarErroSintatico(cadeia, input);
    }
}

void operadorBinario(void *cadeia, int *tokenGlobal, bool *textoAntes, char *input){
    if(*tokenGlobal == MAIS){
        consumirToken(cadeia, MAIS, tokenGlobal, textoAntes, input);
    }else if(*tokenGlobal == MENOS){
        consumirToken(cadeia, MENOS, tokenGlobal, textoAntes, input);
    }else{
        tratarErroSintatico(cadeia, input);
    }
}

void termo(void *cadeia, int *tokenGlobal, bool *textoAntes, char *input){
    if(*tokenGlobal == ID || *tokenGlobal == NUMERO_INTEIRO || *tokenGlobal == NUMERO_REAL || *tokenGlobal == NAO || *tokenGlobal == VERDADEIRO || *tokenGlobal == FALSO || *tokenGlobal == STRING || *tokenGlobal == ABRE_PARENTESES){
        fator(cadeia, tokenGlobal, textoAntes, input);
        termoAux(cadeia, tokenGlobal, textoAntes, input);        
    }else{
        tratarErroSintatico(cadeia, input);
    }
}

void termoAux(void *cadeia, int *tokenGlobal, bool *textoAntes, char *input){
    if(*tokenGlobal == PONTO_VIRGULA || *tokenGlobal == FECHA_PARENTESES || *tokenGlobal == FECHA_COLCHETE || *tokenGlobal == VIRGULA || *tokenGlobal == IGUAL || *tokenGlobal == DIFERENTE || *tokenGlobal == MAIOR || *tokenGlobal == MAIOR_IGUAL || *tokenGlobal == MENOR || *tokenGlobal == MENOR_IGUAL || *tokenGlobal == MAIS || *tokenGlobal == MENOS || *tokenGlobal == OU || *tokenGlobal == ENTAO || *tokenGlobal == FACA || *tokenGlobal == ATE || *tokenGlobal == PASSO){
        return;
    }else if(*tokenGlobal == VEZES){
        consumirToken(cadeia, VEZES, tokenGlobal, textoAntes, input);
        fator(cadeia, tokenGlobal, textoAntes, input);
        termoAux(cadeia, tokenGlobal, textoAntes, input);        
    }else if(*tokenGlobal == DIVISAO){
        consumirToken(cadeia, DIVISAO, tokenGlobal, textoAntes, input);
        fator(cadeia, tokenGlobal, textoAntes, input);
        termoAux(cadeia, tokenGlobal, textoAntes, input);        
    }else if(*tokenGlobal == DIV){
        consumirToken(cadeia, DIV, tokenGlobal, textoAntes, input);
        fator(cadeia, tokenGlobal, textoAntes, input);
        termoAux(cadeia, tokenGlobal, textoAntes, input);
    }else if(*tokenGlobal == AND){
        consumirToken(cadeia, AND, tokenGlobal, textoAntes, input);
        fator(cadeia, tokenGlobal, textoAntes, input);
        termoAux(cadeia, tokenGlobal, textoAntes, input);
    }else{
        tratarErroSintatico(cadeia, input);
    }
}

void fator(void *cadeia, int *tokenGlobal, bool *textoAntes, char *input){
    if(*tokenGlobal == ID){
        consumirToken(cadeia, ID, tokenGlobal, textoAntes, input);
        fatorAux(cadeia, tokenGlobal, textoAntes, input);        
    }else if(*tokenGlobal == NUMERO_INTEIRO){
        consumirToken(cadeia, NUMERO_INTEIRO, tokenGlobal, textoAntes, input);
    }else if(*tokenGlobal == NUMERO_REAL){
        consumirToken(cadeia, NUMERO_REAL, tokenGlobal, textoAntes, input);
    }else if(*tokenGlobal == VERDADEIRO){
        consumirToken(cadeia, VERDADEIRO, tokenGlobal, textoAntes, input);
    }else if(*tokenGlobal == FALSO){
        consumirToken(cadeia, FALSO, tokenGlobal, textoAntes, input);
    }else if(*tokenGlobal == STRING){
        consumirToken(cadeia, STRING, tokenGlobal, textoAntes, input);
    }else if(*tokenGlobal == NAO){
        consumirToken(cadeia, NAO, tokenGlobal, textoAntes, input);
        fator(cadeia, tokenGlobal, textoAntes, input);
    }else if(*tokenGlobal == ABRE_PARENTESES){
        consumirToken(cadeia, ABRE_PARENTESES, tokenGlobal, textoAntes, input);
        expressao(cadeia, tokenGlobal, textoAntes, input);
        consumirToken(cadeia, FECHA_PARENTESES, tokenGlobal, textoAntes, input);
    }else{
        tratarErroSintatico(cadeia, input);
    }
}

void fatorAux(void *cadeia, int *tokenGlobal, bool *textoAntes, char *input){
    if(*tokenGlobal == PONTO_VIRGULA || *tokenGlobal == FECHA_PARENTESES || *tokenGlobal == FECHA_COLCHETE || *tokenGlobal == VIRGULA || *tokenGlobal == IGUAL || *tokenGlobal == DIFERENTE || *tokenGlobal == MAIOR || *tokenGlobal == MAIOR_IGUAL || *tokenGlobal == MENOR || *tokenGlobal == MENOR_IGUAL || *tokenGlobal == MAIS || *tokenGlobal == MENOS || *tokenGlobal == OU || *tokenGlobal == VEZES || *tokenGlobal == DIVISAO || *tokenGlobal == DIV || *tokenGlobal == AND || *tokenGlobal == ENTAO || *tokenGlobal == FACA || *tokenGlobal == ATE || *tokenGlobal == PASSO){
        return;
    }else if(*tokenGlobal == ABRE_PARENTESES){
        consumirToken(cadeia, ABRE_PARENTESES, tokenGlobal, textoAntes, input);
        exprIter(cadeia, tokenGlobal, textoAntes, input);
        consumirToken(cadeia, FECHA_PARENTESES, tokenGlobal, textoAntes, input);        
    }else if(*tokenGlobal == ABRE_COLCHETE){
        consumirToken(cadeia, ABRE_COLCHETE, tokenGlobal, textoAntes, input);
        exprIter(cadeia, tokenGlobal, textoAntes, input);
        consumirToken(cadeia, FECHA_COLCHETE, tokenGlobal, textoAntes, input);
    }else{
        tratarErroSintatico(cadeia, input);
    }
}

void variavel(void *cadeia, int *tokenGlobal, bool *textoAntes, char *input){
    if(*tokenGlobal == ID){
        consumirToken(cadeia, ID, tokenGlobal, textoAntes, input);
        variavelAux(cadeia, tokenGlobal, textoAntes, input);        
    }else{
        tratarErroSintatico(cadeia, input);
    }
}

void variavelAux(void *cadeia, int *tokenGlobal, bool *textoAntes, char *input){
    if(*tokenGlobal == FECHA_PARENTESES){
        return;
    }else if(*tokenGlobal == ABRE_COLCHETE){
        consumirToken(cadeia, ABRE_COLCHETE, tokenGlobal, textoAntes, input);
        exprIter(cadeia, tokenGlobal, textoAntes, input);
        consumirToken(cadeia, FECHA_COLCHETE, tokenGlobal, textoAntes, input);        
    }else{
        tratarErroSintatico(cadeia, input);
    }
}

void exprIter(void *cadeia, int *tokenGlobal, bool *textoAntes, char *input){
    if(*tokenGlobal == ID || *tokenGlobal == NUMERO_INTEIRO || *tokenGlobal == NUMERO_REAL || *tokenGlobal == NAO || *tokenGlobal == VERDADEIRO || *tokenGlobal == FALSO || *tokenGlobal == STRING || *tokenGlobal == MAIS || *tokenGlobal == MENOS || *tokenGlobal == ABRE_PARENTESES){
        expressao(cadeia, tokenGlobal, textoAntes, input);
        exprIterAux(cadeia, tokenGlobal, textoAntes, input);        
    }else{
        tratarErroSintatico(cadeia, input);
    }
}

void exprIterAux(void *cadeia, int *tokenGlobal, bool *textoAntes, char *input){
    if(*tokenGlobal == FECHA_PARENTESES || *tokenGlobal == FECHA_COLCHETE){
        return;
    }else if(*tokenGlobal == VIRGULA){
        consumirToken(cadeia, VIRGULA, tokenGlobal, textoAntes, input);
        exprIter(cadeia, tokenGlobal, textoAntes, input);        
    }else{
        tratarErroSintatico(cadeia, input);
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

        if(*tokenGlobal >= PROCEDIMENTO && *tokenGlobal <= COMENTARIO_DE_BLOCO){
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