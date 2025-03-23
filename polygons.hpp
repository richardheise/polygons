/***********************************************************************
 *
 * Autor: Richard Fernando Heise Ferreira
 * Matrícula: 201900121214
 * Data: 11/2024
 * Instituição: Universidade Federal do Paraná
 * Curso: Mestrado em Segurança da Computação - PPG-Inf
 * Motivo: Trabalho da disciplina de Geometria Computacional
 *
************************************************************************/

#ifndef __POLIGONS_H__
#define __POLIGONS_H__

#include <utility>
#include <vector> 
#include <stdexcept>
#include <iostream>

using namespace std;

// Definindo a classe Dot para representar um ponto (x, y)
class Dot {
public:
    int x, y;

    // Construtor padrão
    Dot() : x(0), y(0) {}

    // Construtor com parâmetros
    Dot(int x, int y) : x(x), y(y) {}

    // Meto para escrever na saida padrão um ponto
    void printDot() const {
        cout << "Ponto: (" << x << "," << y << ")" << endl;
    }
};

// Definindo a classe Polygon para representar um polígono
class Polygon {
private:
    vector<Dot> vertices; // Vetor de pontos (vértices) do polígono

public:
    // Construtor padrão
    Polygon() {}

    // Método para adicionar um vértice ao polígono
    void addVertex(const Dot& vertex) {
        vertices.push_back(vertex);
    }

    // Método para obter o número de vértices do polígono
    size_t getNumVertices() const {
        return vertices.size();
    }

    // Método para obter um vértice específico do polígono
    Dot getVertex(size_t index) const {
        if (index < vertices.size()) {
            return vertices[index];
        }
        throw out_of_range("Índice fora do intervalo");
    }

    // Método para escrever na saída padrão um polígono
    void printPolygon() const {
        cout << "Polígono: " << endl;
        for (const auto& dot : vertices) {
            dot.printDot();
        }
    }
};

#endif // __POLIGONS_H__