#include "fractals.h"

int main() {
  int dim = 200;
  double scaling_factor = 1.0;
  int num_points = 50;
  double step = 0.02;
  //generate_julia_set(dim, num_points, step, "prova");
  generate_scaled_outputs(dim, 1.0, 1.5, 0.1, "mandel");

  

  return 0;
}
