#include "cmath"
#include "iostream"
#include "string"
#include "tuple"
#include "unistd.h"
#include "vector"

class Point {
public:
  int x;
  int y;
  int z;
  wchar_t moji;

  Point(int startX, int startY, int startZ, wchar_t sMoji) {
    x = startX;
    y = startY;
    z = startZ;
    moji = sMoji;
  }

  std::tuple<float, float, float> rotatePoint(float alpha, float beta,
                                              float gamma) {
    float newX =
        x * (cos(alpha) * cos(beta)) +
        y * (cos(alpha) * sin(beta) * sin(gamma) - sin(alpha) * cos(gamma)) +
        z * (cos(alpha) * sin(beta) * cos(gamma) + sin(alpha) * sin(gamma));

    float newY =
        x * (sin(alpha) * cos(beta)) +
        y * (sin(alpha) * sin(beta) * sin(gamma) + cos(alpha) * cos(gamma)) +
        z * (sin(alpha) * sin(beta) * cos(gamma) - cos(alpha) * sin(gamma));
    float newZ = x * (-sin(beta)) + y * (cos(beta) * sin(gamma)) +
                 z * (cos(beta) * cos(gamma));

    return std::tuple(newX, newY, newZ);
  }
};

void clearGrid(wchar_t **grid, int m, int n) {
  for (int r = 0; r < m; r++) {
    for (int c = 0; c < n; c++) {
      grid[r][c] = L'　';
    }
  }
}

void clearZBuffer(float **zBuffer, int m, int n) {
  for (int r = 0; r < m; r++) {
    for (int c = 0; c < n; c++) {
      zBuffer[r][c] = 0;
    }
  }
}

// add array for lighting
void displayGrid(wchar_t **grid, int m, int n) {
  for (int r = 0; r < m; r++) {
    for (int c = 0; c < n; c++) {
      std::wcout << grid[r][c];
    }
    std::wcout << "\n";
  }
}

void updateGrid(wchar_t **grid, std::vector<Point> points, float **zBuffer,
                std::string illumination, float z1, float z2, float alpha,
                float beta, float gamma, int height, int width) {

  for (int i = 0; i < points.size(); i++) {
    std::tuple<float, float, float> newPoint =
        points[i].rotatePoint(alpha, beta, gamma);

    float zDistance = 1.0 / (std::get<2>(newPoint) + z2);
    int xP = (width / 2.0) + std::get<0>(newPoint) * z1 * zDistance;
    int yP = (height / 2.0) - std::get<1>(newPoint) * z1 * zDistance;

    if (xP < 0 || xP >= width || yP < 0 || yP >= height) {
      continue;
    }

    if (zDistance > zBuffer[yP][xP]) {
      zBuffer[yP][xP] = zDistance;
      grid[yP][xP] = points[i].moji;
    }
  }
}

std::vector<Point> cube(float side) {
  std::vector<Point> points;

  float halfSide = side / 2;

  for (int r = -halfSide; r < halfSide; r++) {
    for (int c = -halfSide; c < halfSide; c++) {
      points.push_back(Point(r, c, halfSide, L'！'));
      points.push_back(Point(r, c, -halfSide, L'＠'));

      points.push_back(Point(halfSide, r, c, L'＃'));
      points.push_back(Point(-halfSide, r, c, L'＄'));

      points.push_back(Point(c, halfSide, r, L'％'));
      points.push_back(Point(c, -halfSide, r, L'＆'));
    }
  }

  return points;
}

int main() {
  setlocale(LC_ALL, "ja_JP.utf8");
  int m = 50;
  int n = 50;
  std::string illumination = "、。：；ー〜＝！＊＃＄＠";
  int FPS = 60;

  // camera distance to origin
  float z1 = 50;
  // shape distance to origin
  float z2 = 500;

  float alpha = 0;
  float beta = 0;
  float gamma = 0;

  std::vector<Point> points = cube(100);

  wchar_t **grid = new wchar_t *[m];
  float **zBuffer = new float *[m];

  for (int i = 0; i < m; i++) {
    grid[i] = new wchar_t[n];
    zBuffer[i] = new float[n];
  }

  while (true) {
    system("clear");

    alpha += 0.1;
    beta += 0.1;
    // gamma += 0.1;
    clearZBuffer(zBuffer, m, n);
    clearGrid(grid, m, n);

    updateGrid(grid, points, zBuffer, illumination, z1, z2, alpha, beta, gamma,
               m, n);

    displayGrid(grid, m, n);

    usleep((1.0 / FPS) * pow(10, 6));
  }

  for (int i = 0; i < m; i++) {
    delete grid[i];
    delete zBuffer[i];
  }

  delete *grid;
  delete *zBuffer;

  return 0;
}
