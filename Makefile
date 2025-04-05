# Definindo variáveis
CXX = g++
CXXFLAGS = -Wall -Wextra

# Arquivos principais
SRC = main.cpp polygons.cpp
OBJ = main.o polygons.o
HEADER = polygons.hpp
EXE = poligonos

# Regra principal
$(EXE): $(OBJ)
	$(CXX) $(OBJ) -o $(EXE)

# Compilação de objetos
polygons.o: polygons.cpp $(HEADER)
	$(CXX) $(CXXFLAGS) -c polygons.cpp

main.o: main.cpp $(HEADER)
	$(CXX) $(CXXFLAGS) -c main.cpp

# Limpeza
clean:
	rm -f $(OBJ) $(EXE) $(GENERATOR_EXE)
