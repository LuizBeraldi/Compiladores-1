%option noyywrap 
%{
	#include <string.h>
	#include <sintatico.tab.h>
	int linha = 1;
	int coluna = 1;

void warning(){
	for(int i = 0; i < strlen(yytext); i++){
		if(yytext[i] == '\n'){
			linha += 1; 
			coluna = 1;
		}else{
			coluna += 1;
		}

		if(yytext[i] == '/' && i < (strlen(yytext)-1) && i > 0){
			if(yytext[i+1] == '*' && yytext[i+2] != '/')	{
				printf("warning:%d:%d: \'/*\' within block comment\n", linha, coluna-1);
			}
		}	
	}	
}

%}

%% 
"void" 		{coluna += 4; return VOID; }
"int" 		{coluna += 3; return INT; }
"char" 		{coluna += 4; return CHAR; }
"return" 	{coluna += 6; return RETURN; }
"break" 	{coluna += 5; return BREAK; }
"switch" 	{coluna += 6; return SWITCH; }
"case" 		{coluna += 4; return CASE; }
"default" 	{coluna += 7; return DEFAULT;}
"do" 		{coluna += 2; return DO;}
"while" 	{coluna += 5; return WHILE;}
"for" 		{coluna += 3; return FOR; }
"if" 		{coluna += 2; return IF; }
"else" 		{coluna += 4; return ELSE; }
"typedef" 	{coluna += 7; return TYPEDEF; }
"struct" 	{coluna += 6; return STRUCT; }
"printf" 	{coluna += 6; return PRINTF; }
"scanf" 	{coluna += 5; return SCANF; }
"exit" 		{coluna += 4; return EXIT; }
"#" 		{coluna += 1; return NUMBER_SIGN; }
"define" 	{coluna += 6; return DEFINE; }

"+"     {coluna += 1; return PLUS; }
"-"     {coluna += 1; return MINUS; }
"*"     {coluna += 1; return MULTIPLY;}
"/"     {coluna += 1; return DIV; }
"%"     {coluna += 1; return REMAINDER; }
"++"    {coluna += 2; return INC; }
"--"    {coluna += 2; return DEC; }
"&"     {coluna += 1; return BITWISE_AND; }
"|"     {coluna += 1; return BITWISE_OR; }
"~"     {coluna += 1; return BITWISE_NOT; }
"^"     {coluna += 1; return BITWISE_XOR; }
"&&"    {coluna += 2; return LOGICAL_AND; }
"||"    {coluna += 2; return LOGICAL_OR; }
"!"     {coluna += 1; return NOT; }
"=="    {coluna += 2; return EQUAL; }
"!="    {coluna += 2; return NOT_EQUAL; }
"<"     {coluna += 1; return LESS_THAN; }
">"     {coluna += 1; return GREATER_THAN; }
"<="    {coluna += 2; return LESS_EQUAL; }
">="    {coluna += 2; return GREATER_EQUAL; }
">>"    {coluna += 2; return R_SHIFT; }
"<<"    {coluna += 2; return L_SHIFT; }
"="     {coluna += 1; return ASSIGN; }
"+="    {coluna += 2; return ADD_ASSIGN; }
"-="    {coluna += 2; return MINUS_ASSIGN; }
";"     {coluna += 1; return SEMICOLON; }
","     {coluna += 1; return COMMA; }
":"     {coluna += 1; return COLON; }
"("     {coluna += 1; return L_PAREN; }
")"     {coluna += 1; return R_PAREN; }
"{"     {coluna += 1; return L_CURLY_BRACKET; }
"}"     {coluna += 1; return R_CURLY_BRACKET; }
"["     {coluna += 1; return L_SQUARE_BRACKET;}
"]"     {coluna += 1; return R_SQUARE_BRACKET;}
"?"     {coluna += 1; return TERNARY_CONDITIONAL; }
"->"    {coluna += 2; return POINTER; }

[_a-zA-Z][_a-zA-Z0-9]* {if(strlen(yytext)>255){return IDENTIFIER_TOO_LONG;}else{coluna += strlen(yytext);return IDENTIFIER; }}

"0"[1-7][0-7]* {coluna += strlen(yytext);return NUM_OCTAL; }

[0-9]+ { coluna += strlen(yytext);return NUM_INTEGER;}

0[xX][0-9a-fA-F]+ {coluna += strlen(yytext);return NUM_HEXA; }

["]([^"\\\n]|\\.|\\\n)*["] {coluna += strlen(yytext);return STRING;}

"\'""\\"?."\'" {coluna += strlen(yytext); return CHARACTER;}

[\r\t \f] {coluna += 1;}

"//".*[\n] {linha += 1; coluna = 1;}

"//".* {return END_OF_FILE;}

("/*"([^*]|[\n]|("*"+([^*/]|[\n])))*"*/") {warning();}

("/*"([^*]|[\n]|("*"+([^*/]|[\n])))*)	{return  UNTERMINATED_COMMENT;}

[\n] {linha += 1; coluna = 1;}

<<EOF>> {return END_OF_FILE;}

. { coluna += strlen(yytext); return OTHER;}

%%