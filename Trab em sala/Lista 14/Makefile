FLEX=flex
BISON=bison
CC=gcc
# CFLAGS = -fstack-protector-all -g -Wall

PROGRAMA = l14e1
LEXICO = lexico.l
SINTATICO = sintatico.y

$(PROGRAMA): $(LEXICO) $(SINTATICO)
	$(FLEX) $(LEXICO)
	$(BISON) -d $(SINTATICO)
	$(CC) *.c -I. -o $(PROGRAMA)
# $(CC) $(CFLAGS) *.c -I. -o $(PROGRAMA)

clear:
	rm -f sintatico.tab.c
	rm -f sintatico.tab.h
	rm -f lex.yy.c
	rm -f $(PROGRAMA)
	rm -f diff.txt