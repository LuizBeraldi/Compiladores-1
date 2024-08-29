#include "LISTA_5_EXERCICIO_2.hpp"

int main() {
    char reads[SIGMA] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
                         'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',
                         'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
                         'u', 'v', 'w', 'x', 'y', 'z', '.', '-', 32, 10};
    int edges[][SIGMA] = {
        {7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 4, 4, 4, 4, 4, 4, 4, 4, 2, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5, 9, 12, 0},                            // estado 1
        {4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0},                             // estado 2
        {4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0},                             // estado 3
        {4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0},                             // estado 4
        {6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},                             // estado 5
        {6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},                             // estado 6
        {7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0},                             // estado 7
        {8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},                             // estado 8
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 0, 0},                            // estado 9
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 0, 0, 0, 11},  // estado 10
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},                             // estado 11
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 12, 0},                            // estado 12
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},                             // estado 13
    };

    char specialTransitions[QNTD_SPECIAL] = {'\n'};  // o que é lido para um estado intermediário não final ir para um estado final
    int specialTransitionStates[] = {11};            // após ler o caractere especial no índice i de specialTransitions, vai para o estado no índice i deste array

    int finalStates[QNTD_FINAL] = {2, 3, 4, 5, 6, 7, 8, 9, 11, 12, 13};
    const char *tokens[] = {"nda", "ID", "IF", "ID", "ERROR", "REAL", "NUM", "REAL", "ERROR", "nda", "comemnt", "white space", "ERROR"};

    bool textBefore = false;
    char input[200];
    int limitIndex;
    while (fgets(input, 200, stdin) != NULL) {
        int currentState = 1;         // estado inicial
        int index = 0;                // índice do caractere na entrada
        int backupIndex = 0;          // índice para lidar com estados não terminais
        bool allowPrint = true;       // se o estado atual é um estado final
        bool acceptedAsFinal = true;  // se o estado atual é um estado final
        int end = -1;                 // estado final

        while (input[index] != '\0') {
            int currentCharIndex = getChar(reads, input[index]);  // obtém o índice do caractere no array

            // bloco especial apenas para lidar com erros e outros símbolos que não estão no array
            if (currentCharIndex == -1) {
                if (end != -1) {  // se o estado final não é -1, o token é impresso
                    if (input[index - 1] == 32) {
                        printf("%s", tokens[11]);
                    } else {
                        printf(" %s", tokens[end - 1]);
                    }
                    textBefore = true;
                }
                // atualiza variáveis para começar novamente
                end = -1;
                currentState = 1;
                index++;

                if (input[index - 1] == 10) continue;
                if (input[index - 1] == 32) {
                    printf("%s", tokens[11]);
                    continue;
                } else {
                    if (textBefore) {
                        //printf("\n");
                        std::cout << "\n";
                    }
                    printf("%c", input[index - 1]);  // imprime o caractere que não está no array
                    printf(" %s", tokens[12]);       // imprime o token de ERRO
                    textBefore = true;
                }
                continue;  // vai para a próxima iteração
            }

            int nextState = edges[currentState - 1][currentCharIndex];  // obtém o próximo estado, dado um estado atual e um caractere lido

            // se a transição não é válida
            if (nextState == 0) {
                if (currentState == end) {  // no caso da última string lida alcançar um estado final, é o maior token possível
                    for (int i = backupIndex; i < limitIndex; i++) {
                        if (textBefore) {
                            printf("\n");
                            textBefore = false;
                        }
                        printf("%c", input[i]);  // imprime os caracteres que foram lidos
                    }
                    allowPrint = true;
                } else {
                    index = backupIndex;  // se o estado atual não é o estado final, o índice é atualizado para encontrar o próximo token
                }

                if (input[index - 1] == 32) {
                    printf("\n%s", tokens[11]);
                } else {
                    printf(" %s", tokens[end - 1]);
                }

                textBefore = true;
                end = -1;
                currentState = 1;
                continue;
            }

            currentState = nextState;  // atualiza o estado atual

            acceptedAsFinal = isFinal(finalStates, currentState);  // verifica se o estado atual é um estado final

            // se o estado atual é um estado final, o estado final é atualizado
            if (acceptedAsFinal) {
                end = currentState;
                allowPrint = true;
            } else {
                allowPrint = false;  // se o atual não é um estado final, desabilitar impressão para verificar o maior token
            }

            if (input[index] != 10 && input[index] != 32 && allowPrint) {
                if (textBefore) {
                    printf("\n");
                    textBefore = false;
                }
                printf("%c", input[index]);
            }
            index++;
            limitIndex = index;

            // alcançar um estado final após sair de um estado intermediário não final não atualiza o backupIndex
            // a intenção é salvar o índice do que era o estado final antes de entrar no não final
            if (acceptedAsFinal && !isSpecialTransition(specialTransitionStates, specialTransitions, currentState, input[index - 1])) {
                backupIndex = index;
            }

            // limpando buffer
            if (input[index] == '\n' && currentState != 10) {
                input[strcspn(input, "\n")] = 0;
            }
        }

        // Verifica a classificação para o último token
        if (end == currentState) {
            for (int i = backupIndex; i < limitIndex; i++) {
                if (input[i] != 10) {
                    if (textBefore) {
                        printf("\n");
                        textBefore = false;
                    }
                    printf("%c", input[i]);  // imprime os caracteres que foram lidos
                }
            }
            printf(" %s", tokens[end - 1]);
            textBefore = true;
        }
    }
    printf("\n");
    return 0;
}

// Função que retorna o índice do caractere no array para que possamos saber quais símbolos foram lidos na entrada
int getChar(char *reads, char input) {
    for (int i = 0; i < SIGMA; i++) {
        if (reads[i] == input) {
            // printf("%c - %d \n", input, input);
            return i;
        }
    }
    return -1;  // erro
}

// Função que retorna o estado final se o estado atual é um estado final ou o estado final se não for
bool isFinal(int *finals, int current) {
    for (int i = 0; i < QNTD_FINAL; i++) {
        if (finals[i] == current) {
            return true;
        }
    }
    return false;
}

// Função para verificar se uma entrada pode fazer um estado intermediário não final ir para o estado final st
bool isSpecialTransition(int *states, char *transitions, int st, char in) {
    for (int i = 0; i < QNTD_SPECIAL; i++) {
        if (transitions[i] == in && states[i] == st) {
            return true;
        }
    }
    return false;
}
