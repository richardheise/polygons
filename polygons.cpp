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
#include "polygons.hpp"

// Função para imprimir os polígonos
void printPolygons(const vector<Polygon> &polygons) {
  cout << endl << "Printando polígonos lidos: " << endl;
  for (const auto &polygon : polygons) {
    polygon.printPolygon();
  }
}

// Função para imprimir os pontos
void printDots(const vector<Dot> &dots) {
  cout << endl << "Printando pontos lidos: " << endl;
  for (const auto &dot : dots) {
    dot.printDot();
  }
}

double crossProduct(const Dot &p1, const Dot &p2, const Dot &p3) {
  return (p2.x - p1.x) * (p3.y - p2.y) - (p2.y - p1.y) * (p3.x - p2.x);
}

void convexCheck(Polygon &polygon) {
  size_t size = polygon.getNumVertices();

  if (size < 3) {
    polygon.setConvex(false);
    return;
  }

  short int sign = 0;

  for (size_t i = 0; i < size; i++) {
    int cross =
        crossProduct(polygon.getVertex(i), polygon.getVertex((i + 1) % size),
                     polygon.getVertex((i + 2) % size));

    int currentSign = (cross > 0) ? 1 : -1;

    if (sign == 0) {
      sign = currentSign;
    } else if (sign != currentSign) { // Se mudar de sinal, o polígono é côncavo
      polygon.setConvex(false);
      return;
    }
  }
}
