%option yylineno
%x COMMENT
%{
int temBranco = 1;
int linhasEmBranco = 0;
int linhasDeComentario = 0;
int linhasSemBrancoEComentario = 0;
int pontoVirgula = 0;
int diretivas = 0;
int totalDeLinhas = 0;
int totalDeLinhasEmBranco = 0;
int totalDeLinhasDeComentario = 0;
int totalDeLinhasSemBrancoEComentario = 0;
int totalDePontoVirgula = 0; 
int totalDiretivas = 0;
int EhLinhaEmBranco = 0;
int variasLinhasDeComentario = 0;
%}

%%

";" { pontoVirgula++; }
"/*" { BEGIN(COMMENT); variasLinhasDeComentario = yylineno; }
<COMMENT>"\n" { 
    if (EhLinhaEmBranco) {
        linhasEmBranco++;
        temBranco = 0;
    }
    EhLinhaEmBranco = 1;
 }
<COMMENT>";" { pontoVirgula++; }
<COMMENT>. { EhLinhaEmBranco = 0; }
<COMMENT>"*/" { 
    BEGIN(INITIAL); 
    linhasDeComentario += yylineno - variasLinhasDeComentario; 
    linhasDeComentario++; 
    int c = input();
    if (c == '\n') {
        linhasEmBranco++;
    } else {
        unput(c);
    }
}
"//".*\n { linhasDeComentario++; }
"\n" {
    if (EhLinhaEmBranco) {
        linhasEmBranco++;
        temBranco = 0;
    }
    EhLinhaEmBranco = 1;
}
. { EhLinhaEmBranco = 0; }
"#"("include"|"define") { diretivas++; }

%%

int yywrap() {}

int main(int argc, char *argv[]) {
    if(argc < 2) { /* just read stdin */
        yylex();
        return 0;
    }

    printf(" total  blank  lines w/  nb, nc  semi-  preproc.  file\n");
    printf(" lines  lines  comments  lines  colons  direct.  \n");
    printf("------+-------+-------+-------+-------+-------+-------");

    for (int i = 1; i < argc; i++) {
        FILE *f = fopen(argv[i], "r");
        if(!f) {
            printf("Nao foi possivel abrir o arquivo %s\n", argv[i]);
            return 1;
        }

        yyrestart(f);
        yylex();
        fclose(f);
        if (temBranco) {
            linhasEmBranco = 0;
        }
        linhasSemBrancoEComentario = yylineno - linhasEmBranco - linhasDeComentario;
        printf("\n%4d\t%4d\t%4d\t%4d\t%4d\t%4d\t%s", yylineno, linhasEmBranco, linhasDeComentario, linhasSemBrancoEComentario, pontoVirgula, diretivas, argv[i]);

        totalDeLinhas += yylineno;
        totalDeLinhasEmBranco += linhasEmBranco;
        totalDeLinhasDeComentario += linhasDeComentario;
        totalDeLinhasSemBrancoEComentario += linhasSemBrancoEComentario;
        totalDePontoVirgula += pontoVirgula;
        totalDiretivas += diretivas;

        yylineno = 1;
        linhasEmBranco = 0;
        linhasDeComentario = 0;
        linhasSemBrancoEComentario = 0;
        pontoVirgula = 0;
        diretivas = 0; 
        temBranco = 1;
    }
    printf("\n%4d\t%4d\t%4d\t%4d\t%4d\t%4d\ttotal", totalDeLinhas, totalDeLinhasEmBranco, totalDeLinhasDeComentario, totalDeLinhasSemBrancoEComentario, totalDePontoVirgula, totalDiretivas);
    printf("\n");
    return 0;
}