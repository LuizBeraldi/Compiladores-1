%{
#include<stdio.h>
#include<string.h>
#include<stdarg.h>

extern int coluna, linha, yylex();
extern char* yytext;
void yyerror(char *s);
FILE* input_file = NULL;

void imprimirLinha(FILE* input, int n){
	int i = 1;
	char c;
	fseek(input, 0, SEEK_SET);
	while(i < n){
		c = fgetc(input);
		if(c == '\n'){
            i++;
        }else if(c == EOF){
            break;
        }
	}
	c = fgetc(input);

	while(c != '\n' && c != EOF){
		printf("%c", c);
		c = fgetc(input);
	}
	printf("\n");
}

%}

%token VOID
%token INT 
%token CHAR 
%token RETURN 
%token BREAK 
%token SWITCH 
%token CASE 
%token DEFAULT
%token DO 
%token WHILE 
%token FOR 
%token IF 
%token ELSE 
%token TYPEDEF 
%token STRUCT
%token PLUS 
%token MINUS 
%token MULTIPLY
%token DIV
%token REMAINDER
%token INC 
%token DEC 
%token BITWISE_AND
%token BITWISE_OR
%token BITWISE_NOT
%token BITWISE_XOR
%token NOT 
%token LOGICAL_AND 
%token LOGICAL_OR
%token EQUAL
%token NOT_EQUAL 
%token LESS_THAN
%token GREATER_THAN
%token LESS_EQUAL
%token GREATER_EQUAL
%token R_SHIFT
%token L_SHIFT
%token ASSIGN
%token ADD_ASSIGN
%token MINUS_ASSIGN
%token SEMICOLON
%token COMMA
%token COLON
%token L_PAREN
%token R_PAREN
%token L_CURLY_BRACKET
%token R_CURLY_BRACKET
%token L_SQUARE_BRACKET
%token R_SQUARE_BRACKET
%token TERNARY_CONDITIONAL
%token NUMBER_SIGN
%token POINTER
%token PRINTF 
%token SCANF 
%token DEFINE 
%token EXIT
%token NUM_HEXA 
%token NUM_OCTAL
%token NUM_INTEGER
%token IDENTIFIER
%token CHARACTER
%token STRING
%token UNTERMINATED_COMMENT
%token IDENTIFIER_TOO_LONG
%token END_OF_FILE
%token OTHER

%start programa

%%

programa: 
    program programa END_OF_FILE {printf("SUCCESSFUL COMPILATION."); return 0;}
	| program END_OF_FILE {printf("SUCCESSFUL COMPILATION."); return 0;}
;

program: 
    declaracao{}
	| funcao{}
;

declaracao: 
    NUMBER_SIGN DEFINE IDENTIFIER expressao{}
    | declaracao_variavel{}
    | declaracao_prot{}
;

funcao: 
    tipo pointer IDENTIFIER parametros L_CURLY_BRACKET declara_variavel_funcao comandos R_CURLY_BRACKET{}
;

declara_variavel_funcao: 
    declaracao_variavel declara_variavel_funcao{}
	|{}
;

declaracao_variavel: 
    tipo dec_var SEMICOLON{}
;

dec_var: 
    pointer IDENTIFIER array ASSIGN atribuicao declara_variavel_aux{}
    | pointer IDENTIFIER array declara_variavel_aux{}
;

declara_variavel_aux: 
    COMMA dec_var{}
    |{}
;

declaracao_prot: 
    tipo pointer IDENTIFIER parametros SEMICOLON{}
;

parametros: 
    L_PAREN param R_PAREN{}
	| L_PAREN R_PAREN{}
;

param: 
    tipo pointer IDENTIFIER array parametros_aux{}
;

parametros_aux: 
    COMMA param{}
	|{}
;

array: 
    L_SQUARE_BRACKET expressao R_SQUARE_BRACKET array{}
	 |{}
;

tipo: 
    INT{}
	| CHAR{}
	| VOID{}
;

bloco: 
    L_CURLY_BRACKET comandos R_CURLY_BRACKET{}
;

comandos: 
    lista_comandos comandos{}
	| lista_comandos{}
;

lista_comandos: 
    DO bloco WHILE L_PAREN expressao R_PAREN SEMICOLON{}
	| IF L_PAREN expressao R_PAREN bloco else_expressao{}
	| WHILE L_PAREN expressao R_PAREN bloco{}
	| FOR L_PAREN expressao_opcional SEMICOLON expressao_opcional SEMICOLON expressao_opcional R_PAREN bloco{}
    | PRINTF L_PAREN STRING printf_expressao R_PAREN SEMICOLON{}
	| SCANF L_PAREN STRING COMMA BITWISE_AND IDENTIFIER R_PAREN SEMICOLON{}
    | EXIT L_PAREN expressao R_PAREN SEMICOLON{}
	| RETURN expressao_opcional SEMICOLON{}
	| expressao SEMICOLON{}
	| SEMICOLON{}
	| bloco{}
;

printf_expressao: 
    COMMA expressao{}
	|{}
;

else_expressao: 
    ELSE bloco{}
	|{}
;

expressao_opcional: 
    expressao{}
	|{}
;

expressao: 
    atribuicao{}
    | atribuicao COMMA expressao{}
;

atribuicao: 
    expressao_condicional{}
    | expressao_unaria atribuicao_aux atribuicao{}
;

atribuicao_aux: 
    ASSIGN{}
	| ADD_ASSIGN{}
	| MINUS_ASSIGN{}
;

expressao_condicional: 
    expressao_ou_logico{}
    | expressao_ou_logico TERNARY_CONDITIONAL expressao COLON expressao_condicional{}
;

expressao_ou_logico: 
    expressao_e_logico{}
    | expressao_e_logico LOGICAL_OR expressao_ou_logico{}
;

expressao_e_logico: 
    expressao_ou{}
    | expressao_ou LOGICAL_AND expressao_e_logico{}
;

expressao_ou: 
    expressao_ou_exclusivo{}
    | expressao_ou_exclusivo BITWISE_OR expressao_ou{}
;

expressao_ou_exclusivo: 
    expressao_e{}
    | expressao_e BITWISE_XOR expressao_ou_exclusivo{}
;

expressao_e: 
    expressao_igualdade{}
    | expressao_igualdade BITWISE_AND expressao_e{}
;

expressao_igualdade: 
    expressao_relacional{}
    | expressao_relacional expressao_igualdade_aux expressao_igualdade{}
;

expressao_igualdade_aux: 
    EQUAL{}
	| NOT_EQUAL{}
;

expressao_relacional: 
    expressao_shift{}
	| expressao_shift expressao_relacional_aux expressao_relacional{}
;

expressao_relacional_aux: 
    LESS_THAN{}
	| LESS_EQUAL{}
	| GREATER_THAN{}
	| GREATER_EQUAL{}
;

expressao_shift: 
    expressao_add{}
	| expressao_add expressao_shift_aux expressao_shift{}
;

expressao_shift_aux: 
    L_SHIFT{}
	| R_SHIFT{}
;

expressao_add: 
    expressao_multiplicacao{}
	| expressao_multiplicacao expressao_add_aux expressao_add{}
;

expressao_add_aux: 
    PLUS{}
	| MINUS{}
;

expressao_multiplicacao: 
    expressao_cast{}
	| expressao_cast expressao_multiplicacao_aux expressao_multiplicacao{}
;

expressao_multiplicacao_aux: 
    MULTIPLY{}
	| DIV{}
	| REMAINDER{}
;

expressao_cast: 
    expressao_unaria{}
	| L_PAREN tipo pointer R_PAREN expressao_cast{}
;

expressao_unaria: 
    expressao_posfixa{}
	| INC expressao_unaria{}
	| DEC expressao_unaria{}
	| expressao_unaria_aux expressao_cast{}
;

expressao_unaria_aux: 
    BITWISE_AND{}
	| PLUS{}
	| MINUS{}
	| BITWISE_NOT{}
	| NOT{}
;

expressao_posfixa: 
    expressao_prim{}
	| expressao_posfixa INC{}
	| expressao_posfixa DEC{}
	| expressao_posfixa L_SQUARE_BRACKET expressao R_SQUARE_BRACKET{}
	| expressao_posfixa L_PAREN R_PAREN{}
	| expressao_posfixa L_PAREN atribuicao expressao_posfixa_aux R_PAREN{}
;

expressao_posfixa_aux: 
    COMMA atribuicao expressao_posfixa_aux{}
	|{}
;

expressao_prim: 
    IDENTIFIER{}
	| num{}
	| CHARACTER{}
	| STRING{}
	| L_PAREN expressao R_PAREN{}
;

num: 
    NUM_INTEGER{}
    | NUM_HEXA{}
    | NUM_OCTAL{}
;

pointer: 
    MULTIPLY pointer{}
    |{}
;

%%

void yyerror(char *s){
	int i = 1;

	if(yychar == IDENTIFIER_TOO_LONG){
		printf("error:lexical:%d:%d: identifier too long", linha, coluna);
	}else if(yychar == UNTERMINATED_COMMENT){
		printf("error:lexical:%d:%d: unterminated comment", linha, coluna);
	}else if(yychar == OTHER){
		coluna -= strlen(yytext);
		printf("error:lexical:%d:%d: %s", linha, coluna, yytext);
	}else if(yychar == END_OF_FILE){
		printf("error:syntax:%d:%d: expected declaration or statement at end of input\n", linha, coluna);
		imprimirLinha(input_file, linha);

		for(i; i < coluna; i++){ 
			printf(" "); 
		}
		printf("^");
	}else{
		coluna -= strlen(yytext);
		printf("error:syntax:%d:%d: %s\n", linha, coluna, yytext);
		imprimirLinha(input_file, linha);

		for(i; i < coluna; i++){ 
			printf(" "); 
		}
		printf("^");		
	}
}

int main(int argc, char **argv){
	input_file = stdin;
	yyparse();
    return 0;
}