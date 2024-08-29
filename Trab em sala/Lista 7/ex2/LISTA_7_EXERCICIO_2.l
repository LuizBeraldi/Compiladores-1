%{
int textoAntes = 0;
%}

%%

if { 
    if(textoAntes){
        printf("\n");
    } 
    printf("%s IF", yytext); 
    textoAntes = 1;
}
i {
    if(textoAntes){
        printf("\n");
    } 
    printf("%s ID", yytext); 
    textoAntes = 1;
}
if[a-z0-9]+ {
    if(textoAntes){
        printf("\n");
    } 
    printf("%s ID", yytext); 
    textoAntes = 1;
}
i[a-eg-z0-9][a-z0-9]* {
    if(textoAntes){
        printf("\n");
    } 
    printf("%s ID", yytext); 
    textoAntes = 1;
}
[a-hj-z][a-z0-9]* {
    if(textoAntes){
        printf("\n");
    } 
    printf("%s ID", yytext); 
    textoAntes = 1;
}
(([0-9]+"."[0-9]*)|([0-9]*"."[0-9]+)) {
    if(textoAntes){
        printf("\n");
    } 
    printf("%s REAL", yytext); 
    textoAntes = 1;
}   
[0-9]+ {
    if(textoAntes){
        printf("\n");
    } 
    printf("%s NUM", yytext); 
    textoAntes = 1;
}
"." {
    if(textoAntes){
        printf("\n");
    } 
    printf("%s erro", yytext); 
    textoAntes = 1;
}
--([a-z]+)\n {
    if(textoAntes){
        printf("\n");
    } 
    for(int i = 0; i < strlen(yytext); i++){
        if(yytext[i] != '\n'){
            printf("%c", yytext[i]);
        }
    }
    printf(" comment"); 
    textoAntes = 1;
}
"-" {
    if(textoAntes){
        printf("\n");
    } 
    printf("%s erro", yytext); 
    textoAntes = 1;
}
[" "]+ {
    if(textoAntes){
        printf("\n");
    } 
    printf("white space"); 
    textoAntes = 1;
}
\n|\r\n? {}
<<EOF>> { return 0; }
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