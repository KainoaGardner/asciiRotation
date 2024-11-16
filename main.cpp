#include <cmath>
#include <iostream>
#include <stdlib.h>
#include <tuple>
#include <unistd.h>
#include <vector>

class Point {
public:
  int x;
  int y;
  int z;

  Point(int startX, int startY, int startZ) {
    x = startX;
    y = startY;
    z = startZ;
  }

  std::tuple<float, float> updatePoint(float angle) {
    // temp 2d

    int newX = x * cos(angle) - y * sin(angle);
    int newY = x * sin(angle) + y * cos(angle);

    return std::make_tuple(newX, newY);
  };
};

int main() {
  int m = 50;
  int n = 50;
  int FPS = 30;
  int angle = 0;

  std::vector<Point> points = {};

  points.push_back(Point(5, -5, 0));
  points.push_back(Point(5, -4, 0));
  points.push_back(Point(5, -3, 0));
  points.push_back(Point(5, -2, 0));
  points.push_back(Point(5, -1, 0));
  points.push_back(Point(5, 0, 0));
  points.push_back(Point(5, 1, 0));
  points.push_back(Point(5, 2, 0));
  points.push_back(Point(5, 3, 0));
  points.push_back(Point(5, 4, 0));
  points.push_back(Point(5, 5, 0));

  points.push_back(Point(-5, -5, 0));
  points.push_back(Point(-5, -4, 0));
  points.push_back(Point(-5, -3, 0));
  points.push_back(Point(-5, -2, 0));
  points.push_back(Point(-5, -1, 0));
  points.push_back(Point(-5, 0, 0));
  points.push_back(Point(-5, 1, 0));
  points.push_back(Point(-5, 2, 0));
  points.push_back(Point(-5, 3, 0));
  points.push_back(Point(-5, 4, 0));
  points.push_back(Point(-5, 5, 0));

  points.push_back(Point(-4, 5, 0));
  points.push_back(Point(-3, 5, 0));
  points.push_back(Point(-2, 5, 0));
  points.push_back(Point(-1, 5, 0));
  points.push_back(Point(0, 5, 0));
  points.push_back(Point(1, 5, 0));
  points.push_back(Point(2, 5, 0));
  points.push_back(Point(3, 5, 0));
  points.push_back(Point(4, 5, 0));

  points.push_back(Point(-4, -5, 0));
  points.push_back(Point(-3, -5, 0));
  points.push_back(Point(-2, -5, 0));
  points.push_back(Point(-1, -5, 0));
  points.push_back(Point(0, -5, 0));
  points.push_back(Point(1, -5, 0));
  points.push_back(Point(2, -5, 0));
  points.push_back(Point(3, -5, 0));
  points.push_back(Point(4, -5, 0));

  int **grid = new int *[m];

  for (int i = 0; i < m; i++) {
    grid[i] = new int[n];
  }

  grid[4][20] = 1;

  while (true) {
    system("clear");

    for (int r = 0; r < m; r++) {
      for (int c = 0; c < n; c++) {
        grid[r][c] = 0;
      }
    }

    angle -= 5;

    for (int i = 0; i < points.size(); i++) {
      float radianAngle = (angle % 360) * M_PI / 180;

      std::tuple<float, float> point = points[i].updatePoint(radianAngle);

      int pointX = (n / 2) + std::get<0>(point);
      int pointY = (m / 2) + std::get<1>(point);

      if (pointX >= 0 && pointX < n && pointY >= 0 && pointY < m) {
        grid[pointY][pointX] = 1;
      }
    }

    for (int r = 0; r < m; r++) {
      for (int c = 0; c < n; c++) {
        if (grid[r][c] != 0) {
          std::cout << "0";
        }
        std::cout << " ";
      }
      std::cout << "\n";
    }
    usleep((1.0 / FPS) * pow(10, 6));
  };

  for (int i = 0; i < m; i++) {
    delete[] grid[i];
  }

  delete[] grid;

  return 0;
}
