#include "LISTA_5_EXERCICIO_1.hpp"

int main() {
    char reads[SIGMA] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
                         'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',
                         'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
                         'u', 'v', 'w', 'x', 'y', 'z', '+', '-'};
    int edges[][SIGMA] = {
        {5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 4},  // estado 1
        {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0},  // estado 2
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},  // estado 3
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},  // estado 4
        {5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},  // estado 5
        {8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7},  // estado 6
        {8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},  // estado 7
        {8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},  // estado 8
    };

    int estadosFinais[] = {2, 3, 4, 5, 8};
    bool textoAntes = false;
    char input[200];
    while (std::fgets(input, 200, stdin) != NULL) {
        input[std::strcspn(input, "\n")] = 0;  //remove o \n da entrada

        int estadoAtual = 1;
        int indice = 0;
        bool aceito = true;
        int fim = -1;

        while (input[indice] != '\0') {
            int indiceCharAtual = getChar(reads, input[indice]);  //obtém o índice do char no array

            if (indiceCharAtual == -1) {  // se o char não estiver no array, ERRO será impresso
                if (fim != -1) {
                    textoAntes = true;
                }
                fim = -1;
                estadoAtual = 1;
                indice++;
                std::cout << "\nERRO";
                continue;  //vai para a próxima iteração
            }

            estadoAtual = edges[estadoAtual - 1][indiceCharAtual];  // obtém o próximo estado, dado um estado atual e uma leitura de char
            aceito = isFinal(estadosFinais, estadoAtual);             // verifica se o estado atual é um estado final
            indice++;

            if (aceito) {  // se o estado atual for um estado final, o estado fim é atualizado
                fim = estadoAtual;
                if (textoAntes) {
                    std::cout << "\n";
                    textoAntes = false;
                }
                std::cout << input[indice - 1];

            } else {  // se o estado atual não for um estado final, o estado fim é impresso e o estado atual é atualizado para que possamos começar novamente
                estadoAtual = 1;
                indice--;          // o índice é decrementado para que possamos ler o char novamente
                if (fim != -1) {  // se o estado fim não for -1, ele será impresso
                    textoAntes = true;
                }
                fim = -1;  // o estado fim é atualizado para começar novamente
            }
            if (input[indice] == '\n') {
                input[std::strcspn(input, "\n")] = 0;
            }
        }
        if (fim != -1) {
            textoAntes = true;
        }
    }
    std::cout << "\n";
    return 0;
}

//Função que retorna o índice do char do array para sabermos quais símbolos foram lidos no input
int getChar(const char* reads, char input) {
    for (int i = 0; i < SIGMA; i++) {
        if (reads[i] == input) {
            return i;
        }
    }
    return -1;  // erro
}

//Função que retorna o estado final se o estado atual for um estado final ou o estado fim se não for
bool isFinal(const int* finals, int current) {
    for (int i = 0; i < QNTD_FINAL; i++) {
        if (finals[i] == current) {
            return true;
        }
    }
    return false;
}
