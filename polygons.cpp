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

// ------------------------------------------------------------------------------
// //

// Função para imprimir os polígonos
void printPolygons(const vector<Polygon> &polygons) {
  cout << endl << "Printando polígonos lidos: " << endl;
  for (const auto &polygon : polygons) {
    polygon.printPolygon();
  }
}

// ------------------------------------------------------------------------------
// //

// Função para imprimir os pontos
void printDots(const vector<Dot> &dots) {
  cout << endl << "Printando pontos lidos: " << endl;
  for (const auto &dot : dots) {
    dot.printDot();
  }
}

// ------------------------------------------------------------------------------
// //

double crossProduct(const Dot &p1, const Dot &p2, const Dot &p3) {
  return (p2.x - p1.x) * (p3.y - p2.y) - (p2.y - p1.y) * (p3.x - p2.x);
}

// ------------------------------------------------------------------------------
// //

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

// ------------------------------------------------------------------------------
// //

bool intersectionCheck(const Dot &p1, const Dot &p2, const Dot &p3,
                       const Dot &p4) {
  int o1 = (crossProduct(p1, p2, p3) > 0)
               ? 1
               : (crossProduct(p1, p2, p3) < 0 ? -1 : 0);
  int o2 = (crossProduct(p1, p2, p4) > 0)
               ? 1
               : (crossProduct(p1, p2, p4) < 0 ? -1 : 0);
  int o3 = (crossProduct(p3, p4, p1) > 0)
               ? 1
               : (crossProduct(p3, p4, p1) < 0 ? -1 : 0);
  int o4 = (crossProduct(p3, p4, p2) > 0)
               ? 1
               : (crossProduct(p3, p4, p2) < 0 ? -1 : 0);

  return (o1 != o2 && o3 != o4);
}

// ------------------------------------------------------------------------------
// //

void simpleCheck(Polygon &polygon) {
  size_t size = polygon.getNumVertices();

  if (size < 3) {
    polygon.setSimple(false);
    return;
  }

  for (size_t i = 0; i < size; i++) {
    Dot a1 = polygon.getVertex(i);
    Dot a2 = polygon.getVertex((i + 1) % size);

    for (size_t j = i + 1; j < size; j++) {
      // Pega próxima aresta (b1, b2), evitando vizinhas
      size_t j1 = j % size;
      size_t j2 = (j + 1) % size;

      // Evita contabilizar arestas subsequentes como autointersecção
      if (i == j1 || i == j2 || (i + 1) % size == j1 || (i + 1) % size == j2)
        continue;

      Dot b1 = polygon.getVertex(j1);
      Dot b2 = polygon.getVertex(j2);

      if (intersectionCheck(a1, a2, b1, b2)) {
        polygon.setSimple(false);
        return;
      }
    }
  }
}

// ------------------------------------------------------------------------------
// //

bool isOnSegment(const Dot &a, const Dot &b, const Dot &p) {
  // Verifica se p está no segmento ab
  return (min(a.x, b.x) <= p.x && p.x <= max(a.x, b.x)) &&
         (min(a.y, b.y) <= p.y && p.y <= max(a.y, b.y)) &&
         ((b.x - a.x) * (p.y - a.y) ==
          (p.x - a.x) * (b.y - a.y)); // Produto vetorial == 0
}

// ------------------------------------------------------------------------------
// //
bool insideCheck(Polygon &polygon, const Dot &p) {
  size_t size = polygon.getNumVertices();
  bool inside = false;

  for (size_t i = 0, j = size - 1; i < size; j = i++) {
    const Dot &vi = polygon.getVertex(i);
    const Dot &vj = polygon.getVertex(j);

    // Verifica se o ponto é um vértice
    if ((p.x == vi.x && p.y == vi.y) || (p.x == vj.x && p.y == vj.y)) {
      return true;
    }

    // Verifica se o ponto está sobre a aresta (vj -> vi)
    if (isOnSegment(vj, vi, p)) {
      return true;
    }

    // Ajusta os extremos para evitar contar vértice superior
    int y1 = vi.y, y2 = vj.y;
    int x1 = vi.x, x2 = vj.x;

    if (y1 > y2) {
      swap(y1, y2);
      swap(x1, x2);
    }

    // Verifica se p.y está estritamente entre y1 e y2 (não inclui y2)
    if (p.y > y1 && p.y <= y2) {
      double intersectX = (double)(x2 - x1) * (p.y - y1) / (y2 - y1) + x1;
      if (p.x < intersectX) {
        inside = !inside;
      }
    }
  }

  return inside;
}
