#include "fractals.h"

int main() {
  fractals j(800);
  std::complex<double> c (0.3, -0.45);
    std::string img = "README_IMG";
  j.julia_gen(c);
  j.save_to_file_j(c, img);
  

  fractals m(800);
  double scaling_factor = 0.9;
  m.mandel_gen(scaling_factor, -2, -1.13);
  m.save_to_file_j(scaling_factor, img);
  


  int dim = 400;
  int num_points = 50;
  double step = 0.01;
  std::string dir_j = "julia_set";
  generate_julia_set(dim, num_points, step, dir_j);

  double ssf = 1.5;
  double esf = 0.05;
  double st = 0.1;
  std::string dir_m = "pd";
  generate_scaled_outputs(dim, ssf, esf, st, dir_m);
  
}
