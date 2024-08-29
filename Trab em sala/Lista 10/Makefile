EXEC = gcc
CFLAGS = -fstack-protector-all -g -Wall
PROJECT_NAME = l10e4
OBJETCS = LISTA_10_EXERCICIO_4.o linked_list.o

$(PROJECT_NAME): $(OBJETCS)
	$(EXEC) $(CFLAGS) $(OBJETCS) -o $(PROJECT_NAME) -lm

clear: 
	rm -f *.o
	rm -f $(PROJECT_NAME)
	rm -f diff.txt

LISTA_9_EXERCICIO_1.o: LISTA_10_EXERCICIO_4.c LISTA_10_EXERCICIO_4.h
	$(EXEC) $(CFLAGS) -c LISTA_10_EXERCICIO_4.c

linked_list.o: linked_list.c linked_list.h
	$(EXEC) $(CFLAGS) -c linked_list.c