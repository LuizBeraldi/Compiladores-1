#include "LISTA_6_EXERCICIO_1.h"

int main() {
    char leitura[SIGMA] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
                         'h', 'e', 'r', 's', 'i', 'c', 'a', 't', '+', '-'};
    int edges[][SIGMA] = {
        {19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 2, 0, 0, 4, 0, 11, 0, 0, 17, 18},  // estado 1
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 7, 0, 0, 0, 0, 0},               // estado 2
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 0, 0, 0, 0, 0, 0, 0},               // estado 3
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0},               // estado 4
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0},               // estado 5
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},               // estado 6
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0},               // estado 7
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},               // estado 8
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 0, 0, 0, 0, 0, 0},              // estado 9
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},               // estado 10
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 12, 0, 0, 0},              // estado 11
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 14, 0, 0, 0, 0, 13, 0, 0},             // estado 12
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 0, 0, 0, 0, 0, 0},              // estado 13
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 16, 0, 0, 0, 0, 0, 0},              // estado 14
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},               // estado 15
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},               // estado 16
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},               // estado 17
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},               // estado 18
        {19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 0, 20, 0, 0, 0, 0, 0, 0, 0, 0},    // estado 19
        {22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 0, 0, 0, 0, 0, 0, 0, 0, 21, 21},   // estado 20
        {22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},     // estado 21
        {22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},     // estado 22
    };

    int estadosFinais[] = {3, 6, 8, 10, 13, 14, 15, 16, 17, 18, 19, 22};
    char *tokens[] = {"nda", "nda", "ELE", "nda", "nda", "ELA", "nda", "DELE", "nda", "DELA",
                      "nda", "nda", "GATO", "CARRO", "GATOS", "CARROS", "MAIS", "MENOS", "INTEIRO", "nda", "nda", "REAL"};

    bool textoAntes = false;
    char input[4096];
    char output[4096];
    int outputIndice = 0;
    int imprimirIndice = 0;
    while (fgets(input, 4096, stdin) != NULL) {
        int estadoAtual = 1;         // estado inicial
        int indice = 0;                // índice do char na entrada
        int backupIndice = 0;          // índice para lidar com estados não terminais
        bool aceitoFinal = true;  // se o estado atual é um estado final
        int fim = -1;                 // estado final

        while (input[indice] != '\0') {
            int indiceCharAtual = getChar(leitura, input[indice]);  // obtém o índice do char no array

            // bloco especial apenas para tratar casos em que o char lido não está no alfabeto
            if (indiceCharAtual == -1) {
                if (fim == -1) {
                    if (indice == 0) {
                        if (input[indice] == 10 || input[indice] == 32) {
                            resetarVariaveis(&indice, (indice + 1), &backupIndice, &fim, &estadoAtual);
                            continue;
                        }
                        imprimirToken(&textoAntes, "ERRO");
                        resetarVariaveis(&indice, (indice + 1), &backupIndice, &fim, &estadoAtual);
                        continue;
                    }

                    resetarVariaveis(&indice, (backupIndice + 1), &backupIndice, &fim, &estadoAtual);
                    if (input[indice - 1] == 10 || input[indice - 1] == 32) continue;
                    imprimirToken(&textoAntes, "ERRO");
                    limparOutput(output, strlen(output), &outputIndice);
                    continue;
                }

                if (fim != estadoAtual) {  // o caractere atual não está no alfabeto e o estado atual não é um estado final
                    indice = backupIndice;
                    backupIndice = indice;
                }

                if (fim != -1) {  // se o estado final não for -1, o token é impresso porque em algum momento ele foi para o estado final
                    printf("%s", tokens[fim - 1]);
                    if (fim == 22 || fim == 19) {  // print numbers
                        imprimirSecao(output, imprimirIndice);
                    }
                    textoAntes = true;
                }

                // atualizar variáveis ​​para começar de novo
                limparOutput(output, strlen(output), &outputIndice);
                resetarVariaveis(&indice, (indice + 1), &backupIndice, &fim, &estadoAtual);
                if (input[indice - 1] == 10 || input[indice - 1] == 32) continue;  // pulando espaços e novas linhas
                imprimirToken(&textoAntes, "ERRO");
                continue;
            }

            // se o caractere estiver no alfabeto, o próximo estado é calculado
            int proximoEstado = edges[estadoAtual - 1][indiceCharAtual];

            // se a transição não for válida
            if (proximoEstado == 0) {
                if (fim == -1) {  // a transição não existe e nenhum estado no token é final
                    imprimirToken(&textoAntes, "ERRO");
                    limparOutput(output, strlen(output), &outputIndice);
                    resetarVariaveis(&indice, (backupIndice + 1), &backupIndice, &fim, &estadoAtual);
                    continue;
                }

                if (fim != -1) {  // a transição não existe e existe um estado final, fim do token
                    printf("%s", tokens[fim - 1]);
                    backupIndice = indice;
                }
                if (estadoAtual == fim) {  // se o estado atual for um estado final, significa que o token é válido
                    if (fim == 22 || fim == 19) {
                        imprimirSecao(output, imprimirIndice);
                    }
                } else {  // transição inválida, o estado atual não é final, é necessário voltar ao último estado final
                    indice = backupIndice - 1;
                    backupIndice = indice;
                }
                limparOutput(output, strlen(output), &outputIndice);
                textoAntes = true;
                fim = -1;
                estadoAtual = 1;
                continue;
            }

            // a transição é válida
            estadoAtual = proximoEstado;                              // atualiza o estado atual
            aceitoFinal = ehFinal(estadosFinais, estadoAtual);  // checa se o estado atual é um estado final

            // se o estado atual for um estado final, o estado final será atualizado
            if (aceitoFinal) {
                fim = estadoAtual;
                imprimirIndice = outputIndice + 1;
            }

            if (input[indice] != 10 && input[indice] != 32) {  // pulando espaços e novas linhas
                if (textoAntes) {
                    printf("\n");
                    textoAntes = false;
                }
                output[outputIndice] = input[indice];
                outputIndice++;
            }
            indice++;

            // chegar a um estado final depois de sair de um estado intermediário não final não atualizará o backupIndice
            // a intenção é salvar o índice do que foi o estado final antes de ir para o não final
            if (aceitoFinal) {
                backupIndice = indice;
            }
        }

        // Verifique a classificação do último token
        if (fim == estadoAtual) {
            backupIndice = indice;
            printf("%s", tokens[fim - 1]);
            if (fim == 22 || fim == 19) {
                imprimirSecao(output, imprimirIndice);
            }
            textoAntes = true;

        } else {  // este é o último token da linha e seu erro
            if (input[backupIndice] == 10 || input[backupIndice] == 32 || input[backupIndice] == 0) continue;
            imprimirToken(&textoAntes, "ERRO");
            resetarVariaveis(&indice, (backupIndice + 1), &backupIndice, &fim, &estadoAtual);
        }
        limparOutput(output, strlen(output), &outputIndice);
    }
    printf("\n");
    return 0;
}

int getChar(char *leitura, char input) {
    for (int i = 0; i < SIGMA; i++) {
        if (leitura[i] == input) {
            return i;
        }
    }
    return -1;  // erro
}

bool ehFinal(int *final, int atual) {
    for (int i = 0; i < QNTD_FINAL; i++) {
        if (final[i] == atual) {
            return true;
        }
    }
    return false;
}

void imprimirToken(bool *textoAntes, char *paraImprimir) {
    if (*textoAntes) {
        printf("\n");
    }
    printf("%s", paraImprimir);
    *textoAntes = true;
}

void imprimirSecao(char *output, int tam) {
    printf(" ");
    for (int i = 0; i < tam; i++) {
        printf("%c", output[i]);  // imprime os caracteres que foram lidos
    }
}

void limparOutput(char *output, int tam, int *outputIndice) {
    for (int i = 0; i < tam; i++) {
        output[i] = '\0';  // limpa o buffer de saída
    }
    *outputIndice = 0;
}

void resetarVariaveis(int *indice, int definirIndice, int *backupIndice, int *fim, int *estadoAtual) {
    *indice = definirIndice;
    *backupIndice = *indice;
    *fim = -1;
    *estadoAtual = 1;
}