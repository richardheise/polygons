#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <set>
#include <vector>

// Estrutura de ponto
struct Point {
  int x, y;

  bool operator<(const Point &other) const {
    return (x == other.x) ? (y < other.y) : (x < other.x);
  }

  bool operator==(const Point &other) const {
    return x == other.x && y == other.y;
  }
};

// Gera número aleatório entre [min, max]
int randomInRange(int min, int max) { return min + rand() % (max - min + 1); }

// Ordena os pontos no sentido anti-horário
void sortCounterClockwise(std::vector<Point> &points) {
  double cx = 0, cy = 0;
  for (const auto &p : points) {
    cx += p.x;
    cy += p.y;
  }
  cx /= points.size();
  cy /= points.size();

  std::sort(points.begin(), points.end(),
            [cx, cy](const Point &a, const Point &b) {
              double angleA = std::atan2(a.y - cy, a.x - cx);
              double angleB = std::atan2(b.y - cy, b.x - cx);
              return angleA < angleB;
            });

  double area = 0;
  for (size_t i = 0; i < points.size(); ++i) {
    const Point &p1 = points[i];
    const Point &p2 = points[(i + 1) % points.size()];
    area += (p1.x * p2.y - p2.x * p1.y);
  }
  if (area < 0) {
    std::reverse(points.begin(), points.end());
  }
}

int main(int argc, char *argv[]) {
  if (argc != 5) {
    std::cerr << "Uso: " << argv[0]
              << " <num_poligonos> <num_pontos> <range> <semente>\n";
    return 1;
  }

  int m = std::atoi(argv[1]);
  int n = std::atoi(argv[2]);
  int range = std::atoi(argv[3]);
  int seed = std::atoi(argv[4]);

  if (m <= 0 || n <= 0 || range <= 0) {
    std::cerr << "Todos os parâmetros devem ser inteiros positivos.\n";
    return 1;
  }

  srand(seed);
  std::cout << m << " " << n << std::endl;

  for (int i = 0; i < m; ++i) {
    int numVertices = randomInRange(3, 8);
    std::cout << numVertices << std::endl;

    std::set<Point> unique_points;
    while ((int)unique_points.size() < numVertices) {
      Point p = {randomInRange(0, range), randomInRange(0, range)};
      unique_points.insert(p);
    }

    std::vector<Point> polygon(unique_points.begin(), unique_points.end());
    sortCounterClockwise(polygon);

    for (const auto &p : polygon) {
      std::cout << p.x << " " << p.y << std::endl;
    }
  }

  // Evita repetição de pontos soltos
  std::set<Point> unique_free_points;
  while ((int)unique_free_points.size() < n) {
    Point p = {randomInRange(0, range), randomInRange(0, range)};
    unique_free_points.insert(p);
  }

  for (const auto &p : unique_free_points) {
    std::cout << p.x << " " << p.y << std::endl;
  }

  return 0;
}
