#include <cmath>
#include <iostream>
#include <stdlib.h>
#include <string>
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

  std::tuple<float, float, float> updatePoint(float xAngle, float yAngle,
                                              float zAngle) {
    int newX = x;
    int newY = y;
    int newZ = z;

    // x axis
    if (xAngle) {
      newX = x;
      newY = y * cos(xAngle) - z * sin(xAngle);
      newZ = y * sin(xAngle) + z * cos(xAngle);
    }

    if (yAngle) {
      newX = x * cos(yAngle) + z * sin(yAngle);
      newY = y;
      newZ = z * cos(yAngle) - x * sin(yAngle);
    }

    if (zAngle) {
      newX = x * cos(zAngle) - y * sin(zAngle);
      newY = x * sin(zAngle) + y * cos(zAngle);
      newZ = z;
    }

    return std::make_tuple(newX, newY, newZ);
  };
};

int main() {
  int m = 50;
  int n = 50;
  int FPS = 30;
  int xAngle = 0;
  int yAngle = 0;
  int zAngle = 0;

  std::string brightness = ",,..++::vvoo00XXXXPPPP####BBBB@@@@";

  std::vector<Point> points = {};

  points.push_back(Point(15, -15, 0));
  points.push_back(Point(15, 15, 0));

  points.push_back(Point(-15, -15, 0));
  points.push_back(Point(-15, 15, 0));

  int **grid = new int *[m];

  for (int i = 0; i < m; i++) {
    grid[i] = new int[n];
  }

  grid[4][20] = 1;

  while (true) {
    system("clear");

    for (int r = 0; r < m; r++) {
      for (int c = 0; c < n; c++) {
        grid[r][c] = m * 2;
      }
    }

    zAngle += 5;

    for (int i = 0; i < points.size(); i++) {
      float radXAngle = (xAngle % 360) * M_PI / 180;
      float radYAngle = (yAngle % 360) * M_PI / 180;
      float radZAngle = (zAngle % 360) * M_PI / 180;

      std::tuple<float, float, float> point =
          points[i].updatePoint(radXAngle, radYAngle, radZAngle);

      int pointX = (n / 2) + std::get<0>(point);
      int pointY = (m / 2) + std::get<1>(point);
      int pointZ = std::get<2>(point);

      if (pointX >= 0 && pointX < n && pointY >= 0 && pointY < m) {
        if (grid[pointY][pointX] == m * 2 || pointZ > grid[pointY][pointX]) {
          grid[pointY][pointX] = pointZ;
        }
      }
    }

    for (int r = 0; r < m; r++) {
      for (int c = 0; c < n; c++) {
        if (grid[r][c] != m * 2) {
          float percent = ((m / 2) + float(grid[r][c])) / m;
          int result = percent * brightness.size();
          std::cout << brightness[result];
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
