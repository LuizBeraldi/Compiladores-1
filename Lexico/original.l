%option noyywrap
%option yylineno
%x COMMENT

%{
int textoAntes = 0;
int yycolumn = 1;
int linhaInicio, colunaInicio;

void imprimirToken(const char *token, int *textoAntesFlag) {
    if (*textoAntesFlag) printf("\n");
    printf("%s", token);
    *textoAntesFlag = 1;
}
%}

%%

"/*" {
    BEGIN(COMMENT);
    linhaInicio = yylineno;
    colunaInicio = yycolumn;
    yycolumn += yyleng;
}

<COMMENT>"*/" {
    BEGIN(INITIAL);
    yycolumn += yyleng;
}

<COMMENT>"/*" {
    char nextChar = input();
    if (nextChar == '\n') yylineno--;
    if (nextChar == '/') {
        BEGIN(INITIAL);
        yycolumn += yyleng + 1;
    } else {
        if (textoAntes) printf("\n");
        printf("warning:%d:%d: '%s' within block comment", yylineno, yycolumn, yytext);
        yycolumn += yyleng;
        if (nextChar == '\n') yylineno++;
        unput(nextChar);
    }
    textoAntes = 1;
}

<COMMENT>. { yycolumn += yyleng; }
<COMMENT>\n { yycolumn = 1; }
<COMMENT><<EOF>> {
    if (textoAntes) printf("\n");
    printf("error:lexical:%d:%d: unterminated comment", linhaInicio, colunaInicio);
    exit(1);
}

"//".*\n { printf("comentario de linha\n"); }
"void" { imprimirToken("VOID", &textoAntes); yycolumn += yyleng; }
"int" { imprimirToken("INT", &textoAntes); yycolumn += yyleng; }
"char" { imprimirToken("CHAR", &textoAntes); yycolumn += yyleng; }
"return" { imprimirToken("RETURN", &textoAntes); yycolumn += yyleng; }
"break" { imprimirToken("BREAK", &textoAntes); yycolumn += yyleng; }
"switch" { imprimirToken("SWITCH", &textoAntes); yycolumn += yyleng; }
"case" { imprimirToken("CASE", &textoAntes); yycolumn += yyleng; }
"default" { imprimirToken("DEFAULT", &textoAntes); yycolumn += yyleng; }
"do" { imprimirToken("DO", &textoAntes); yycolumn += yyleng; }
"while" { imprimirToken("WHILE", &textoAntes); yycolumn += yyleng; }
"for" { imprimirToken("FOR", &textoAntes); yycolumn += yyleng; }
"if" { imprimirToken("IF", &textoAntes); yycolumn += yyleng; }
"else" { imprimirToken("ELSE", &textoAntes); yycolumn += yyleng; }
"typedef" { imprimirToken("TYPEDEF", &textoAntes); yycolumn += yyleng; }
"struct" { imprimirToken("STRUCT", &textoAntes); yycolumn += yyleng; }
"+" { imprimirToken("PLUS", &textoAntes); yycolumn += yyleng; }
"-" { imprimirToken("MINUS", &textoAntes); yycolumn += yyleng; }
"*" { imprimirToken("MULTIPLY", &textoAntes); yycolumn += yyleng; }
"/" { imprimirToken("DIV", &textoAntes); yycolumn += yyleng; }
"%" { imprimirToken("REMAINDER", &textoAntes); yycolumn += yyleng; }
"++" { imprimirToken("INC", &textoAntes); yycolumn += yyleng; }
"--" { imprimirToken("DEC", &textoAntes); yycolumn += yyleng; }
"&" { imprimirToken("BITWISE_AND", &textoAntes); yycolumn += yyleng; }
"|" { imprimirToken("BITWISE_OR", &textoAntes); yycolumn += yyleng; }
"~" { imprimirToken("BITWISE_NOT", &textoAntes); yycolumn += yyleng; }
"^" { imprimirToken("BITWISE_XOR", &textoAntes); yycolumn += yyleng; }
"!" { imprimirToken("NOT", &textoAntes); yycolumn += yyleng; }
"&&" { imprimirToken("LOGICAL_AND", &textoAntes); yycolumn += yyleng; }
"||" { imprimirToken("LOGICAL_OR", &textoAntes); yycolumn += yyleng; }
"==" { imprimirToken("EQUAL", &textoAntes); yycolumn += yyleng; }
"!=" { imprimirToken("NOT_EQUAL", &textoAntes); yycolumn += yyleng; }
"<" { imprimirToken("LESS_THAN", &textoAntes); yycolumn += yyleng; }
">" { imprimirToken("GREATER_THAN", &textoAntes); yycolumn += yyleng; }
"<=" { imprimirToken("LESS_EQUAL", &textoAntes); yycolumn += yyleng; }
">=" { imprimirToken("GREATER_EQUAL", &textoAntes); yycolumn += yyleng; }
">>" { imprimirToken("R_SHIFT", &textoAntes); yycolumn += yyleng; }
"<<" { imprimirToken("L_SHIFT", &textoAntes); yycolumn += yyleng; }
"=" { imprimirToken("ASSIGN", &textoAntes); yycolumn += yyleng; }
"+=" { imprimirToken("ADD_ASSIGN", &textoAntes); yycolumn += yyleng; }
"-=" { imprimirToken("MINUS_ASSIGN", &textoAntes); yycolumn += yyleng; }
";" { imprimirToken("SEMICOLON", &textoAntes); yycolumn += yyleng; }
"," { imprimirToken("COMMA", &textoAntes); yycolumn += yyleng; }
":" { imprimirToken("COLON", &textoAntes); yycolumn += yyleng; }
"(" { imprimirToken("L_PAREN", &textoAntes); yycolumn += yyleng; }
")" { imprimirToken("R_PAREN", &textoAntes); yycolumn += yyleng; }
"{" { imprimirToken("L_CURLY_BRACKET", &textoAntes); yycolumn += yyleng; }
"}" { imprimirToken("R_CURLY_BRACKET", &textoAntes); yycolumn += yyleng; }
"[" { imprimirToken("L_SQUARE_BRACKET", &textoAntes); yycolumn += yyleng; }
"]" { imprimirToken("R_SQUARE_BRACKET", &textoAntes); yycolumn += yyleng; }
"?" { imprimirToken("TERNARY_CONDITIONAL", &textoAntes); yycolumn += yyleng; }
"#" { imprimirToken("NUMBER_SIGN", &textoAntes); yycolumn += yyleng; }
"->" { imprimirToken("POINTER", &textoAntes); yycolumn += yyleng; }
"printf" { imprimirToken("PRINTF", &textoAntes); yycolumn += yyleng; }
"scanf" { imprimirToken("SCANF", &textoAntes); yycolumn += yyleng; }
"define" { imprimirToken("DEFINE", &textoAntes); yycolumn += yyleng; }
"exit" { imprimirToken("EXIT", &textoAntes); yycolumn += yyleng; }

\"([^\\\"]|\\.)*\" {
    if (textoAntes) printf("\n");
    printf("STRING(%.*s)", (int)(yyleng - 2), yytext + 1);
    textoAntes = 1;
    yycolumn += yyleng;
}

" " { yycolumn++; }
\n { yycolumn = 1; }

([_]*[a-zA-Z][_a-zA-Z0-9]*) {
    if (textoAntes) printf("\n");
    if (yyleng > 255) {
        printf("error:lexical:%d:%d: identifier too long", yylineno, yycolumn);
    } else {
        printf("IDENTIFIER(%s)", yytext);
    }
    textoAntes = 1;
    yycolumn += yyleng;
}

\'(\\.|[^\\']){1}\' {
    if (textoAntes) printf("\n");
    printf("CHARACTER(%.*s)", (int)(yyleng - 2), yytext + 1);
    textoAntes = 1;
    yycolumn += yyleng;
}

(0[xX][0-9a-fA-F]+) {
    if (textoAntes) printf("\n");
    printf("NUM_HEXA(%s)", yytext);
    textoAntes = 1;
    yycolumn += yyleng;
}

(0[1-7][0-7]*) {
    if (textoAntes) printf("\n");
    printf("NUM_OCTAL(%s)", yytext);
    textoAntes = 1;
    yycolumn += yyleng;
}

[0-9]+ {
    if (textoAntes) printf("\n");
    printf("NUM_INTEGER(%s)", yytext);
    textoAntes = 1;
    yycolumn += yyleng;
}

. {
    if (textoAntes) printf("\n");
    printf("error:lexical:%d:%d: %s", yylineno, yycolumn, yytext);
    textoAntes = 1;
    yycolumn += yyleng;
}

%%

int main(int argc, char *argv[]) {
    yylex();
    return 0;
}
