# Definindo variáveis
CXX = g++
CXXFLAGS = -Wall -Wextra

# Arquivos de entrada
SRC = main.cpp polygons.cpp
OBJ = main.o polygons.o
HEADER = polygons.hpp
EXE = app

# Regra principal
$(EXE): $(OBJ)
	$(CXX) $(OBJ) -o $(EXE)


polygons.o: polygons.cpp $(HEADER)
	$(CXX) $(CXXFLAGS) -c polygons.cpp

# Regras de compilação dos arquivos .cpp
main.o: main.cpp $(HEADER)
	$(CXX) $(CXXFLAGS) -c main.cpp

# Limpeza dos arquivos intermediários
clean:
	rm -f $(OBJ) $(EXE)
