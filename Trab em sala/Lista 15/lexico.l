%option noyywrap
%option yylineno

%{

#include <sintatico.tab.h>
extern YYSTYPE yylval;

int myEof = 0;
int textBefore = 0;
int yycolumn = 1;

void addToUnion() {
    yylval.token.valor = strdup(yytext);
    yylval.token.column = yycolumn;
    yylval.token.line = yylineno;
}

%}

%%

<<EOF>> { myEof = 1; return 0; }

"$" { return EOL; }
"int" { addToUnion(); yycolumn += strlen(yytext); return INT; } 
"char" { addToUnion(); yycolumn += strlen(yytext); return CHAR; }
"float" { addToUnion(); yycolumn += strlen(yytext); return FLOAT; }
"," { addToUnion(); yycolumn++; return COMMA; }
" " { yycolumn++; }
\n { yycolumn = 1; }
[a-z]+ { addToUnion(); yycolumn += strlen(yytext); return ID; }

. { 
    if (textBefore) printf("\n");
    printf("error:lexical:%d:%d: %s", yylineno, yycolumn, yytext);
    yycolumn += strlen(yytext);
    exit(1);
}

%%