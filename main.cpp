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

// Função para verificar se a flag -v foi passada como argumento
bool isVerbose(int argc, char *argv[]) {
  for (int i = 1; i < argc; i++) {
    if (string(argv[i]) == "-v") {
      return true;
    }
  }
  return false;
}

// ------------------------------------------------------------------------------
// //

// Função para ler os polígonos
vector<Polygon> readPolygons(uint m, bool verbose) {
  vector<Polygon> polygons(m);

  for (uint i = 0; i < m; i++) {
    uint verticesNum;
    cin >> verticesNum;

    if (verbose) {
      cout << "Polígono " << i + 1 << " tem " << verticesNum << " vértices."
           << endl;
    }

    while (verticesNum--) {
      Dot newDot;
      cin >> newDot.x >> newDot.y;
      polygons[i].addVertex(newDot);

      if (verbose) {
        cout << "Vértice adicionado: (" << newDot.x << ", " << newDot.y << ")"
             << endl;
      }
    }
  }

  return polygons;
}

// ------------------------------------------------------------------------------
// //

// Função para ler os pontos
vector<Dot> readDots(uint n, bool verbose) {
  vector<Dot> dots(n);

  for (uint i = 0; i < n; i++) {
    Dot newDot;
    cin >> newDot.x >> newDot.y;
    dots[i] = newDot;

    if (verbose) {
      cout << "Ponto adicionado: (" << newDot.x << ", " << newDot.y << ")"
           << endl;
    }
  }

  return dots;
}

// ------------------------------------------------------------------------------
// //

int main(int argc, char *argv[]) {
  // Verifica se a flag -v foi passada
  bool verbose = isVerbose(argc, argv);

  // Lê o número de polígonos (m) e pontos (n)
  uint m, n;
  cin >> m >> n;

  if (verbose) {
    cout << "Número de polígonos: " << m << endl;
    cout << "Número de pontos: " << n << endl;
  }

  // Lê os polígonos e pontos
  vector<Polygon> polygons = readPolygons(m, verbose);
  vector<Dot> dots = readDots(n, verbose);

  // Checagem se os polígonos são simples
  for (auto &polygon : polygons) {
    simpleCheck(polygon);
  }

  // Checagem se os poligonos são convexos
  for (auto &polygon : polygons) {
    if (!polygon.getSimple())
      continue; // pula poligonos nao simples

    convexCheck(polygon);
  }

  // Checagem se os ponhtos estão dentro dos polígonos
  size_t i = 0;
  for (auto &poly : polygons) {
    i += 1;

    if (!poly.getSimple())
      continue; // pula poligonos nao simples

    for (auto &point : dots) {
      if (insideCheck(poly, point)) {
        point.owners.push_back(i);
      }
    }
  }

  if (verbose) {
    printPolygons(polygons);
    printDots(dots);
  }

  // Printa a saída no formato especificado
  // Polígonos
  i = 0;
  for (auto &poly : polygons) {
    i += 1;
    cout << i << " ";
    if (!poly.getSimple()) {
      cout << "nao simples" << endl;
      continue;
    }

    cout << "simples e ";

    if (!poly.getConvex()) {
      cout << "nao convexo" << endl;
      continue;
    }

    cout << "convexo" << endl;
  }

  // Pontos
  i = 0;
  for (auto &point : dots) {
    i += 1;
    cout << i << ":";

    for (const auto &owner : point.owners) {
      cout << owner << " ";
    }

    cout << endl;
  }

  return 0;
}
