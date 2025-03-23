# Compilador
CXX = g++

# Opções de compilação
CXXFLAGS = -Wall -Wextra

# Nome do executável
TARGET = main

# Arquivos fonte
SRCS = main.cpp polygons.cpp

# Arquivos objeto (gerados a partir dos arquivos fonte)
OBJS = $(SRCS:.cpp=.o)

# Regra padrão (alvo principal)
all: $(TARGET)

# Regra para compilar o executável
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Regra para compilar arquivos .cpp em arquivos .o
%.o: %.cpp polygons.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regra para limpar os arquivos gerados
clean:
	rm -f $(OBJS) $(TARGET)

# Regra para rodar o programa
run: $(TARGET)
	./$(TARGET)

# Indica que "clean" e "run" não são arquivos
.PHONY: clean run