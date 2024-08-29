%option noyywrap
%option yylineno
%x COMMENT

%{
int yycolumn = 1, existeToken = 0, linhaInicio, colunaInicio;

void imprimirToken(char *token){
    if(existeToken == 0){
        printf("%s", token);
        existeToken = 1;
    }else{ 
        printf("\n%s", token);
    }
}

void imprimirErro(int yylineno, int yycolumn, char *yytext){
    if(existeToken == 0){
        printf("error:lexical:%d:%d: %s", yylineno, yycolumn, yytext);
        existeToken = 1;
    }else{
        printf("\nerror:lexical:%d:%d: %s", yylineno, yycolumn, yytext);
    }
}

void imprimirErroLongo(int yylineno, int yycolumn){
    if(existeToken == 0){
        printf("error:lexical:%d:%d: identifier too long", yylineno, yycolumn);
        existeToken = 1;
    }else{
        printf("\nerror:lexical:%d:%d: identifier too long", yylineno, yycolumn);
    }
}

void comentarioNaoTerminado(int linhaInicio, int colunaInicio){
    if(existeToken == 0){
        printf("error:lexical:%d:%d: unterminated comment", linhaInicio, colunaInicio);
        existeToken = 1;
    }else{
        printf("\nerror:lexical:%d:%d: unterminated comment", linhaInicio, colunaInicio);
    }
}

void dentroDoBlocoComentario(int yylineno, int yycolumn, char *yytext){
    if(existeToken == 0){
        printf("warning:%d:%d: '%s' within block comment", yylineno, yycolumn, yytext);
        existeToken = 1;
    }else{
       printf("\nwarning:%d:%d: '%s' within block comment", yylineno, yycolumn, yytext);
    }
}
%}

%%

"/*" {
    linhaInicio = yylineno;
    colunaInicio = yycolumn;
    BEGIN(COMMENT);
    yycolumn += yyleng;
}

<COMMENT>"*/" {
    BEGIN(INITIAL);
    yycolumn += yyleng;
}

<COMMENT>"/*" {
    char nextChar = input();
    if (nextChar == '\n'){
        yylineno--;
    }
    if (nextChar == '/'){
        BEGIN(INITIAL);
        yycolumn += yyleng + 1;
    }else{
        dentroDoBlocoComentario(yylineno,yycolumn,yytext);
        yycolumn += yyleng;
        if (nextChar == '\n') yylineno++;
        unput(nextChar);
    }
}

<COMMENT>\n { yycolumn = 1; }
<COMMENT>. { yycolumn += yyleng; }
<COMMENT><<EOF>> {
    comentarioNaoTerminado(linhaInicio,colunaInicio);
    exit(1);
}

"//".*\n {  }
"void"      { imprimirToken("VOID"); yycolumn += yyleng; }
"int"       { imprimirToken("INT"); yycolumn += yyleng; }
"char"      { imprimirToken("CHAR"); yycolumn += yyleng; }
"return"    { imprimirToken("RETURN"); yycolumn += yyleng; }
"break"     { imprimirToken("BREAK"); yycolumn += yyleng; }
"switch"    { imprimirToken("SWITCH"); yycolumn += yyleng; }
"case"      { imprimirToken("CASE"); yycolumn += yyleng; }
"default"   { imprimirToken("DEFAULT"); yycolumn += yyleng; }
"do"        { imprimirToken("DO"); yycolumn += yyleng; }
"while"     { imprimirToken("WHILE"); yycolumn += yyleng; }
"for"       { imprimirToken("FOR"); yycolumn += yyleng; }
"if"        { imprimirToken("IF"); yycolumn += yyleng; }
"else"      { imprimirToken("ELSE"); yycolumn += yyleng; }
"typedef"   { imprimirToken("TYPEDEF"); yycolumn += yyleng; }
"struct"    { imprimirToken("STRUCT"); yycolumn += yyleng; }
"+"         { imprimirToken("PLUS"); yycolumn += yyleng; }
"-"         { imprimirToken("MINUS"); yycolumn += yyleng; }
"*"         { imprimirToken("MULTIPLY"); yycolumn += yyleng; }
"/"         { imprimirToken("DIV"); yycolumn += yyleng; }
"%"         { imprimirToken("REMAINDER"); yycolumn += yyleng; }
"++"        { imprimirToken("INC"); yycolumn += yyleng; }
"--"        { imprimirToken("DEC"); yycolumn += yyleng; }
"&"         { imprimirToken("BITWISE_AND"); yycolumn += yyleng; }
"|"         { imprimirToken("BITWISE_OR"); yycolumn += yyleng; }
"~"         { imprimirToken("BITWISE_NOT"); yycolumn += yyleng; }
"^"         { imprimirToken("BITWISE_XOR"); yycolumn += yyleng; }
"!"         { imprimirToken("NOT"); yycolumn += yyleng; }
"&&"        { imprimirToken("LOGICAL_AND"); yycolumn += yyleng; }
"||"        { imprimirToken("LOGICAL_OR"); yycolumn += yyleng; }
"=="        { imprimirToken("EQUAL"); yycolumn += yyleng; }
"!="        { imprimirToken("NOT_EQUAL"); yycolumn += yyleng; }
"<"         { imprimirToken("LESS_THAN"); yycolumn += yyleng; }
">"         { imprimirToken("GREATER_THAN"); yycolumn += yyleng; }
"<="        { imprimirToken("LESS_EQUAL"); yycolumn += yyleng; }
">="        { imprimirToken("GREATER_EQUAL"); yycolumn += yyleng; }
">>"        { imprimirToken("R_SHIFT"); yycolumn += yyleng; }
"<<"        { imprimirToken("L_SHIFT"); yycolumn += yyleng; }
"="         { imprimirToken("ASSIGN"); yycolumn += yyleng; }
"+="        { imprimirToken("ADD_ASSIGN"); yycolumn += yyleng; }
"-="        { imprimirToken("MINUS_ASSIGN"); yycolumn += yyleng; }
";"         { imprimirToken("SEMICOLON"); yycolumn += yyleng; }
","         { imprimirToken("COMMA"); yycolumn += yyleng; }
":"         { imprimirToken("COLON"); yycolumn += yyleng; }
"("         { imprimirToken("L_PAREN"); yycolumn += yyleng; }
")"         { imprimirToken("R_PAREN"); yycolumn += yyleng; }
"{"         { imprimirToken("L_CURLY_BRACKET"); yycolumn += yyleng; }
"}"         { imprimirToken("R_CURLY_BRACKET"); yycolumn += yyleng; }
"["         { imprimirToken("L_SQUARE_BRACKET"); yycolumn += yyleng; }
"]"         { imprimirToken("R_SQUARE_BRACKET"); yycolumn += yyleng; }
"?"         { imprimirToken("TERNARY_CONDITIONAL"); yycolumn += yyleng; }
"#"         { imprimirToken("NUMBER_SIGN"); yycolumn += yyleng; }
"->"        { imprimirToken("POINTER"); yycolumn += yyleng; }
"printf"    { imprimirToken("PRINTF"); yycolumn += yyleng; }
"scanf"     { imprimirToken("SCANF"); yycolumn += yyleng; }
"define"    { imprimirToken("DEFINE"); yycolumn += yyleng; }
"exit"      { imprimirToken("EXIT"); yycolumn += yyleng; }

\"([^\\\"]|\\.)*\" {
    imprimirToken("STRING");
    printf("(%.*s)", (int)(yyleng - 2), yytext + 1);
    yycolumn += yyleng;
}

" " { yycolumn++; }
\n { yycolumn = 1; }


([_]*[a-zA-Z][_a-zA-Z0-9]*) {
    if(yyleng <= 255){
        imprimirToken("IDENTIFIER");
        printf("(%s)", yytext);
    }else{
        imprimirErroLongo(yylineno,yycolumn);
    }
    yycolumn += yyleng;
}

\'(\\.|[^\\']){1}\' {
    imprimirToken("CHARACTER");
    printf("(%.*s)", (int)(yyleng - 2), yytext + 1);
    yycolumn += yyleng;
}

(0[xX][0-9a-fA-F]+) {
    imprimirToken("NUM_HEXA");
    printf("(%s)", yytext);
    yycolumn += yyleng;
}

(0[1-7][0-7]*) {
    imprimirToken("NUM_OCTAL");
    printf("(%s)", yytext);
    yycolumn += yyleng;
}

[0-9]+ {
    imprimirToken("NUM_INTEGER");
    printf("(%s)", yytext);
    yycolumn += yyleng;
}

. {
    imprimirErro(yylineno,yycolumn,yytext);
    yycolumn += yyleng;
}

%%

int main(int argc, char *argv[]){
    yylex();
    return 0;
}