EXEC = gcc
CFLAGS = -fstack-protector-all -g -Wall
PROJECT_NAME = portugol
OBJETCS = lexico.o sintatico.o lista.o

$(PROJECT_NAME): $(OBJETCS)
	$(EXEC) $(CFLAGS) $(OBJETCS) -o $(PROJECT_NAME) -lm

lexico.o: lexico.c lexico.h
	$(EXEC) $(CFLAGS) -c lexico.c

sintatico.o: sintatico.c sintatico.h
	$(EXEC) $(CFLAGS) -c sintatico.c

lista.o: lista.c lista.h
	$(EXEC) $(CFLAGS) -c lista.c

clear: 
	rm -f *.o
	rm -f $(PROJECT_NAME)
	rm -f diff.txt