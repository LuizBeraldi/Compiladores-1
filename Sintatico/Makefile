FLEX=flex
BISON=bison
CC=gcc

PROGRAMA = sintatico
LEXICO = lexico.l
SINTATICO = sintatico.y
ZIP_NAME = sintatico

$(PROGRAMA): $(LEXICO) $(SINTATICO)
	$(BISON) -d $(SINTATICO)
	$(FLEX) $(LEXICO)
	$(CC) -c *.c -I.
	$(CC) *.o -o $(PROGRAMA)

clean:
	rm -f *.yy.c
	rm -f *.tab.c
	rm -f *.tab.h
	rm -f *.o
	rm -f *.exe
	rm -f $(PROGRAMA)

zip:
	zip $(ZIP_NAME).zip $(LEXICO) $(SINTATICO) Makefile

finish: all run clean create_zip

.PHONY: all clean run create_zip