%{
//O CODIGO NÃO FUNCIONA
#include <stdio.h>
#include <stdlib.h>
#include <math.h>  // Para funções matemáticas como sin, cos, etc.
void yyerror(const char *s);
int yylex(void);
%}

%union {
    int inteiro;
    float real;
    char* var;
}

%token MAIS MENOS VEZES DIV EXP MOD ABREPARENTESE FECHAPARENTESE
%token SEN COS TAN ABS
%token <inteiro> NUMINT
%token <real> NUMREAL
%token <var> VARIAVEL

%left MAIS MENOS
%left VEZES DIV MOD
%right EXP
%left ABREPARENTESE FECHAPARENTESE

%type <inteiro> expr

%%

input:
    /* vazio */
    | input linha
    ;

linha:
    expr '\n' { printf("EXPRESSAO CORRETA\n"); }
    ;

expr:
    expr MAIS expr   { $$ = $1 + $3; }
    | expr MENOS expr { $$ = $1 - $3; }
    | expr VEZES expr { $$ = $1 * $3; }
    | expr DIV expr   { $$ = $1 / $3; }
    | expr EXP expr   { $$ = pow($1, $3); }
    | expr MOD expr   { $$ = $1 % $3; }
    | ABREPARENTESE expr FECHAPARENTESE { $$ = $2; }
    | MENOS expr      { $$ = -$2; }
    | SEN ABREPARENTESE expr FECHAPARENTESE { $$ = sin($3); }
    | COS ABREPARENTESE expr FECHAPARENTESE { $$ = cos($3); }
    | TAN ABREPARENTESE expr FECHAPARENTESE { $$ = tan($3); }
    | ABS ABREPARENTESE expr FECHAPARENTESE { $$ = abs($3); }
    | NUMINT          { $$ = $1; }
    | NUMREAL         { $$ = $1; }
    | VARIAVEL        { $$ = 0; } // Variáveis podem ser usadas, mas sem valor definido
    ;

%%

void yyerror(char const *s) {
    if(!error && !lexicalError) {
        unsigned columnNumber = columnCounter - strlen(yytext);

        if(yytext[0] != '\n' && yytext[0] != '\0') {
            sprintf(strError, "Erro de sintaxe na coluna [%u]: %s", columnNumber, yytext);
        }
        else {
            sprintf(strError, "A expressao terminou de forma inesperada.");
        }

        error = true;
    }
}

int main(void) {
    return yyparse();
}
