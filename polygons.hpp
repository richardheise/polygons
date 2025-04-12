/***********************************************************************
 *
 * Autor: Richard Fernando Heise Ferreira
 * Matrícula: 201900121214
 * Data: 03/2025
 * Instituição: Universidade Federal do Paraná
 * Curso: Mestrado em Segurança da Computação - PPG-Inf
 * Motivo: Trabalho da disciplina de Geometria Computacional
 *
 ************************************************************************/

#ifndef __POLIGONS_H__
#define __POLIGONS_H__

#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;

// ------------------------------------------------------------------------------ //

// Definindo a classe Dot para representar um ponto (x, y)
class Dot {
public:
  int x, y;
  vector<int> owners;

  // Construtor padrão
  Dot() : x(0), y(0) {}

  // Construtor com parâmetros
  Dot(int x, int y) : x(x), y(y) {}

  // Meto para escrever na saida padrão um ponto
  void printDot() const {
    cout << "Ponto: (" << x << "," << y << ")" << endl << "Owners: " << endl;
    for (const auto &owner : owners) {
      cout << owner << " ";
    }
    cout << endl;
  }
};

// ------------------------------------------------------------------------------ //

// Definição da classe Polygon
class Polygon {
private:
  vector<Dot> vertices; // Vetor de pontos (vértices) do polígono
  bool isSimple;        // Propriedade para indicar se o polígono é simples
  bool isConvex;        // Propriedade para indicar se o polígono é convexo

public:
  // Construtor padrão
  Polygon() : isSimple(true), isConvex(true) {}

  // Método para adicionar um vértice ao polígono
  void addVertex(const Dot &vertex) { vertices.push_back(vertex); }

  // Método para obter o número de vértices do polígono
  size_t getNumVertices() const { return vertices.size(); }

  // Método para obter um vértice específico do polígono
  Dot getVertex(size_t index) const {
    if (index < vertices.size()) {
      return vertices[index];
    }
    throw out_of_range("Índice fora do intervalo");
  }

  // Método para definir se o polígono é simples
  void setSimple(bool simple) { isSimple = simple; }

  // Método para verificar se o polígono é simples
  bool getSimple() const { return isSimple; }

  // Método para definir se o polígono é convexo
  void setConvex(bool convex) { isConvex = convex; }

  // Método para verificar se o polígono é convexo
  bool getConvex() const { return isConvex; }

  // Método para escrever na saída padrão um polígono
  void printPolygon() const {
    cout << "Polígono: " << endl;
    for (const auto &dot : vertices) {
      dot.printDot();
    }
    cout << (isSimple ? "Simples" : "Complexo") << endl;
    cout << (isConvex ? "Convexo" : "Não-convexo") << endl;
  }
};

// ------------------------------------------------------------------------------ //

void printPolygons(const vector<Polygon> &polygons);

void printDots(const vector<Dot> &dots);

double crossProduct(const Dot &p1, const Dot &p2, const Dot &p3);

void convexCheck(Polygon &polygon);

void simpleCheck(Polygon &polygon);

// Checa a intersecção entre duas retas, definidas por 4 pontos
bool intersectionCheck(const Dot &p1, const Dot &p2, const Dot &p3, const Dot &p4);

// Checa se um ponto está dentro de um polígono ou não
bool insideCheck(Polygon &polygon, const Dot &p);

// Checa se um ponto p está sobre um segmento definido por a e b
bool isOnSegment(const Dot &a, const Dot &b, const Dot &p);

#endif // __POLIGONS_H__
