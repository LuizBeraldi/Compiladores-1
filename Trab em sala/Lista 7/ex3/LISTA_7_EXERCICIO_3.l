%{
int textoAntes = 0;
%}

%%

(aba)+ { 
    if(textoAntes){
        printf("\n");
    } 
    printf("%s action 1", yytext); 
    textoAntes = 1;
}
ab*a {
    if(textoAntes){
        printf("\n");
    } 
    printf("%s action 2", yytext); 
    textoAntes = 1;
}
[a|b] {
    if(textoAntes){
        printf("\n");
    } 
    printf("%s action 3", yytext); 
    textoAntes = 1;
}
. { 
    if(textoAntes){
        printf("\n");
    } 
    printf("%s erro", yytext); 
    textoAntes = 1;
}

%%

int yywrap() {}

int main() {
    yylex();
    printf("\n");
    return 0;
}