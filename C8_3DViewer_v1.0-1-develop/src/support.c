#include "ddd_viewer.h"

static double minValue(double *vertexes, int count_vertexes, int index) {
  double res = vertexes[0];
  for (int i = 0; i < count_vertexes * 3; i += 3) {
    if (vertexes[i + index] < res) {
      res = vertexes[i + index];
    }
  }
  return res;
}

static double maxValue(double *vertexes, int count_vertexes, int index) {
  double res = vertexes[0];
  for (int i = 0; i < count_vertexes * 3; i += 3) {
    if (vertexes[i + index] > res) {
      res = vertexes[i + index];
    }
  }
  return res;
}

static double maxOf3(double a, double b, double c) {
  return (a >= b && a >= c) ? a : (b >= a && b >= c) ? b : c;
}

void centering(double *vertexes, int count_vertexes) {
  double x_min = minValue(vertexes, count_vertexes, 0);
  double y_min = minValue(vertexes, count_vertexes, 1);
  double z_min = minValue(vertexes, count_vertexes, 2);
  double x_max = maxValue(vertexes, count_vertexes, 0);
  double y_max = maxValue(vertexes, count_vertexes, 1);
  double z_max = maxValue(vertexes, count_vertexes, 2);
  double x_diff = x_max - x_min;
  double y_diff = y_max - y_min;
  double z_diff = z_max - z_min;
  double x_middle = x_min + x_diff / 2.0;
  double y_middle = y_min + y_diff / 2.0;
  double z_middle = z_min + z_diff / 2.0;
  double max3 = maxOf3(x_diff, y_diff, z_diff) / 2.0;
  for (int i = 0; i < count_vertexes * 3; i += 3) {
    vertexes[i] -= x_middle;
    vertexes[i + 1] -= y_middle;
    vertexes[i + 2] -= z_middle;
    vertexes[i] /= max3;
    vertexes[i + 1] /= max3;
    vertexes[i + 2] /= max3;
  }
}