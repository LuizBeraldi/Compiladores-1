FLEX=flex
BISON=bison
CC=gcc
CFLAGS=

PROGRAMA = l15e1
LEXICO = lexico.l
SINTATICO = sintatico.y

$(PROGRAMA): $(LEXICO) $(SINTATICO)
	$(FLEX) $(LEXICO)
# $(BISON) -d -Wcounterexamples $(SINTATICO)
	$(BISON) -d $(SINTATICO)
	$(CC) $(CFLAGS) *.c -I. -o $(PROGRAMA)

clear:
	rm -f sintatico.tab.c
	rm -f sintatico.tab.h
	rm -f lex.yy.c
	rm -f $(PROGRAMA)
	rm -f diff.txt