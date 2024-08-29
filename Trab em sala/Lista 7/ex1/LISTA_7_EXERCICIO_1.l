%{
int textoAntes = 0;
%}

%%

[a-z]+[a-z0-9]* { 
    if(textoAntes){
        printf("\n");
    } 
    printf("%s", yytext); 
    textoAntes = 1;
}
[0-9]+ { 
    if(textoAntes){
        printf("\n");
    }
    printf("%s", yytext); 
    textoAntes = 1;
}
[0-9]+e[+|-]?[0-9]+ { 
    if(textoAntes){
        printf("\n");
    } 
    printf("%s", yytext); 
    textoAntes = 1;
}
[+|-] { 
    if(textoAntes){
        printf("\n");
    } 
    printf("%s", yytext); 
    textoAntes = 1;
}
\n {}
<<EOF>> { return 0; }
. { 
    if(textoAntes){
        printf("\n");
    } 
    printf("ERRO"); 
    textoAntes = 1;
}

%%

int yywrap() {}

int main() {
    yylex();
    printf("\n");
    return 0;
}