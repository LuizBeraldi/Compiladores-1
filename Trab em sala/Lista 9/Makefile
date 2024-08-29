EXEC = gcc
CFLAGS = -fstack-protector-all -g -Wall
PROJECT_NAME = l9e1
OBJETCS = LISTA_9_EXERCICIO_1.o linked_list.o

$(PROJECT_NAME): $(OBJETCS)
	$(EXEC) $(CFLAGS) $(OBJETCS) -o $(PROJECT_NAME) -lm

clear: 
	rm -f *.o
	rm -f $(PROJECT_NAME)
	rm -f diff.txt

LISTA_9_EXERCICIO_1.o: LISTA_9_EXERCICIO_1.c LISTA_9_EXERCICIO_1.h
	$(EXEC) $(CFLAGS) -c LISTA_9_EXERCICIO_1.c

linked_list.o: linked_list.c linked_list.h
	$(EXEC) $(CFLAGS) -c linked_list.c