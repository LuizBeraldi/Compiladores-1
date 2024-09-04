%{
//O CODIGO NÃO FUNCIONA
#include "sintatico.tab.h"

unsigned columnCounter = 1;
%}

%%

[ \t\n]             ; // Ignora espaços e quebras de linha
"+"                 { columnCounter += strlen(yytext);return MAIS; }
"-"                 { columnCounter += strlen(yytext);return MENOS; }
"*"                 { columnCounter += strlen(yytext);return VEZES; }
"/"                 { columnCounter += strlen(yytext);return DIV; }
"^"                 { columnCounter += strlen(yytext);return EXP; }
"%"                 { columnCounter += strlen(yytext);return MOD; }
"("                 { columnCounter += strlen(yytext);return ABREPARENTESE; }
")"                 { columnCounter += strlen(yytext);return FECHAPARENTESE; }
"sen"               { columnCounter += strlen(yytext);return SEN; }
"cos"               { columnCounter += strlen(yytext);return COS; }
"tan"               { columnCounter += strlen(yytext);return TAN; }
"abs"               { columnCounter += strlen(yytext);return ABS; }
[0-9]+              { columnCounter += strlen(yytext);yylval.inteiro = atoi(yytext); return NUMINT; }
[0-9]*"."[0-9]+     { columnCounter += strlen(yytext);yylval.real = atof(yytext); return NUMREAL; }
[a-zA-Z_][a-zA-Z0-9_]* { columnCounter += strlen(yytext);yylval.var = strdup(yytext); return VARIAVEL; }
.                   { columnCounter++; //printf("Erro de sintaxe na coluna [%d]: %c\n", columnCounter, yytext[0]); wrongChars[wrongCharsCount] = yytext[0];
wrongCharsCount++; lexicalError = true; }

%%

int yywrap() {
    return 1;
}
