# Nome do executável
TARGET = l6e1

# Lista de arquivos fonte
SOURCES = LISTA_6_EXERCICIO_1.c

# Gerar lista de headers automaticamente (qualquer .c que não seja main.c)
#HEADERS = $(patsubst %.c,%.h,$(filter-out main.c,$(SOURCES)))
HEADERS = LISTA_6_EXERCICIO_1.h

# Definir o compilador
CXX = gcc

# Definir flags do compilador
CXXFLAGS = -Wall -Wextra -std=c11 -g

# Gerar a lista de arquivos objeto a partir dos arquivos fonte
OBJECTS = $(SOURCES:.c=.o)

# Regra padrão para compilar o projeto
all: $(TARGET)

# Regra para gerar o executável
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Regra para compilar arquivos .cpp em .o e gerar dependências
%.o: %.c
	$(CXX) $(CXXFLAGS) -MMD -c $< -o $@

# Incluir dependências geradas automaticamente
-include $(SOURCES:.c=.d)

# Função run: compilar e rodar o executável
run: $(TARGET)
	$(TARGET)

# Função zip: criar um arquivo zip com fontes e headers
zip:
	tar -cf fontes.zip $(SOURCES) $(HEADERS) makefile

# Limpeza dos arquivos gerados
clean:
	rm -f *.o
	rm -f $(TARGET)
	rm -f *.d
	
finish: all run clean_all zip

.PHONY: all clean run zip
