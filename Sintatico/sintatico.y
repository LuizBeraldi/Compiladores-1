%{
#include<stdio.h>
#include<string.h>
#include<stdarg.h>

extern char* yytext;
extern int yylex();

void yyerror(char *s);
FILE* input_file = NULL;

extern int coluna;
extern int linha;

void print_line(FILE* input, int n){
	int i = 1;
	char c;
	fseek(input, 0, SEEK_SET);
	while(i < n){
		c = fgetc(input);
		if(c == EOF){
            break;
        }
		else if(c == '\n'){
            i++;
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
    declaracao {}
	| funcao {}
;

declaracao: 
    NUMBER_SIGN DEFINE IDENTIFIER expressao {}
    | declaracao_var {}
    | declaracao_prot {}
;

funcao: 
    tipo pointer IDENTIFIER parametros L_CURLY_BRACKET dec_var_func comandos R_CURLY_BRACKET {}
;

dec_var_func: 
    declaracao_var dec_var_func	{}
	| {}
;

declaracao_var: 
    tipo dec_var SEMICOLON {}
;

dec_var: 
    pointer IDENTIFIER array ASSIGN atribuicao dec_var_aux {}
    | pointer IDENTIFIER array dec_var_aux {}
;

dec_var_aux: 
    COMMA dec_var {}
    | {}
;

declaracao_prot: 
    tipo pointer IDENTIFIER parametros SEMICOLON {}
;

parametros: 
    L_PAREN param R_PAREN {}
	| L_PAREN R_PAREN {}
;

param: 
    tipo pointer IDENTIFIER array param_aux	{}
;

param_aux: 
    COMMA param	{}
	| {}
;

array: 
    L_SQUARE_BRACKET expressao R_SQUARE_BRACKET array {}
	 | {}
;

tipo: 
    INT {}
	| CHAR {}
	| VOID {}
;

bloco: 
    L_CURLY_BRACKET comandos R_CURLY_BRACKET {}
;

comandos: 
    lista_comandos comandos	{}
	| lista_comandos {}
;

lista_comandos: 
    DO bloco WHILE L_PAREN expressao R_PAREN SEMICOLON {}
	| IF L_PAREN expressao R_PAREN bloco else_exp	{}
	| WHILE L_PAREN expressao R_PAREN bloco {}
	| FOR L_PAREN exp_opcional SEMICOLON exp_opcional SEMICOLON exp_opcional R_PAREN bloco {}
    | PRINTF L_PAREN STRING printf_exp R_PAREN SEMICOLON {}
	| SCANF L_PAREN STRING COMMA BITWISE_AND IDENTIFIER R_PAREN SEMICOLON {}
    | EXIT L_PAREN expressao R_PAREN SEMICOLON {}
	| RETURN exp_opcional SEMICOLON {}
	| expressao SEMICOLON {}
	| SEMICOLON {}
	| bloco	{}
;

printf_exp: 
    COMMA expressao	{}
	| {}
;

else_exp: 
    ELSE bloco {}
	| {}
;

exp_opcional: 
    expressao {}
	| {}
;

expressao: 
    atribuicao {}
    | atribuicao COMMA expressao {}
;

atribuicao: 
    exp_cond {}
    | exp_unaria atribuicao_aux atribuicao {}
;

atribuicao_aux: 
    ASSIGN {}
	| ADD_ASSIGN {}
	| MINUS_ASSIGN {}
;

exp_cond: 
    exp_or_log {}
    | exp_or_log TERNARY_CONDITIONAL expressao COLON exp_cond {}
;

exp_or_log: 
    exp_and_log {}
    | exp_and_log LOGICAL_OR exp_or_log {}
;

exp_and_log: 
    exp_or {}
    | exp_or LOGICAL_AND exp_and_log {}
;

exp_or: 
    exp_xor {}
    | exp_xor BITWISE_OR exp_or {}
;

exp_xor: 
    exp_and {}
    | exp_and BITWISE_XOR exp_xor {}
;

exp_and: 
    exp_igualdade {}
    | exp_igualdade BITWISE_AND exp_and {}
;

exp_igualdade: 
    exp_relacional {}
    | exp_relacional exp_igualdade_aux exp_igualdade {}
;

exp_igualdade_aux: 
    EQUAL {}
	| NOT_EQUAL {}
;

exp_relacional: 
    exp_shift {}
	| exp_shift exp_relacional_aux exp_relacional {}
;

exp_relacional_aux: 
    LESS_THAN {}
	| LESS_EQUAL {}
	| GREATER_THAN {}
	| GREATER_EQUAL {}
;

exp_shift: 
    exp_add {}
	| exp_add exp_shift_aux exp_shift {}
;

exp_shift_aux: 
    L_SHIFT {}
	| R_SHIFT {}
;

exp_add: 
    exp_mult {}
	| exp_mult exp_add_aux exp_add {}
;

exp_add_aux: 
    PLUS {}
	| MINUS {}
;

exp_mult: 
    exp_cast {}
	| exp_cast exp_mult_aux exp_mult {}
;

exp_mult_aux: 
    MULTIPLY {}
	| DIV {}
	| REMAINDER {}
;

exp_cast: 
    exp_unaria {}
	| L_PAREN tipo pointer R_PAREN exp_cast {}
;

exp_unaria: 
    exp_posfixa	{}
	| INC exp_unaria {}
	| DEC exp_unaria {}
	| exp_un_aux exp_cast {}
;

exp_un_aux: 
    BITWISE_AND {}
	| PLUS {}
	| MINUS {}
	| BITWISE_NOT {}
	| NOT {}
;

exp_posfixa: 
    exp_prim {}
	| exp_posfixa INC {}
	| exp_posfixa DEC {}
	| exp_posfixa L_SQUARE_BRACKET expressao R_SQUARE_BRACKET {}
	| exp_posfixa L_PAREN R_PAREN	{}
	| exp_posfixa L_PAREN atribuicao exp_pf_aux R_PAREN {}
;

exp_pf_aux: 
    COMMA atribuicao exp_pf_aux	{}
	| {}
;

exp_prim: 
    IDENTIFIER {}
	| num {}
	| CHARACTER {}
	| STRING {}
	| L_PAREN expressao R_PAREN {}
;

num: 
    NUM_INTEGER	{}
    | NUM_HEXA {}
    | NUM_OCTAL {}
;

pointer: 
    MULTIPLY pointer {}
    | {}
;

%%

void yyerror(char *s){
	int i = 1;
	switch(yychar){
		case IDENTIFIER_TOO_LONG:
			printf("error:lexical:%d:%d: identifier too long", linha, coluna);
			break;

		case UNTERMINATED_COMMENT:
			printf("error:lexical:%d:%d: unterminated comment", linha, coluna);
			break;
		case OTHER:
			coluna -= strlen(yytext);
			printf("error:lexical:%d:%d: %s", linha, coluna, yytext);
			break;
		case END_OF_FILE:
			printf("error:syntax:%d:%d: expected declaration or statement at end of input\n", linha, coluna);
			print_line(input_file, linha);
			for(i; i < coluna; i++){ 
                printf(" "); 
            }
			printf("^");
			break;
		default:
			coluna -= strlen(yytext);
			printf("error:syntax:%d:%d: %s\n", linha, coluna, yytext);
			print_line(input_file, linha);
			for(i; i < coluna; i++){ 
                printf(" "); 
            }
			printf("^");
			break;
	}
}

int main(int argc, char **argv){
	input_file = stdin;
	yyparse();
    return 0;
}