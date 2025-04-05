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
    polygon.setSimple(false);
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
      simpleCheck(polygon, i);
      return;
    }
  }
}

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

void simpleCheck(Polygon &polygon, size_t index) {
  size_t size = polygon.getNumVertices();
  for (size_t i = index; (i + 1) % size != index; i = (i + 1) % size) {
    for (size_t j = (i + 2) % size; (j + 1) % size != index && j != index;
         j = (j + 1) % size) {
      if ((i == 0 && j == size - 1) || (j == (i + 1) % size))
        continue;
      if (intersectionCheck(
              polygon.getVertex(i), polygon.getVertex((i + 1) % size),
              polygon.getVertex(j), polygon.getVertex((j + 1) % size))) {
        polygon.setSimple(false);
        return;
      }
    }
  }
}

bool isOnSegment(const Dot &a, const Dot &b, const Dot &p) {
  // Verifica se p está no segmento ab
  return (std::min(a.x, b.x) <= p.x && p.x <= std::max(a.x, b.x)) &&
         (std::min(a.y, b.y) <= p.y && p.y <= std::max(a.y, b.y)) &&
         ((b.x - a.x) * (p.y - a.y) ==
          (p.x - a.x) * (b.y - a.y)); // Produto vetorial == 0
}

bool checkInside(Polygon &polygon, const Dot &p) {
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

    // Teste do raio (ray casting)
    if ((vi.y > p.y) != (vj.y > p.y)) {
      double intersectX = (vj.x - vi.x) * (p.y - vi.y) / (vj.y - vi.y) + vi.x;
      if (p.x < intersectX) {
        inside = !inside;
      }
    }
  }

  return inside;
}

void addOwner(vector<Polygon> &Polygons, vector<Dot> &points) {
  size_t i = 0;
  for (auto &poly : Polygons) {
    i += 1;
    for (auto &point : points) {
      if (checkInside(poly, point)) {
        point.owners.push_back(i);
      }
    }
  }
}
