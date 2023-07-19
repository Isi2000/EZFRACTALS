
#include "fractals.h"

int main() {

  fractals j(300);
  std::complex<double> c (0.3, -0.45);
  std::string img = "Mandelbrot_and_julia_sets";
  j.julia_gen(c);
  j.save_to_file_j(c, img);

  fractals m(300);
  double scaling_factor = 1.0;
  
  m.mandel_gen(scaling_factor);
  m.save_to_file_j(scaling_factor, img);



  int dim = 300;
  int num_points = 10;
  double step = 0.1;
  std::string dir_j = "julia_set";
  //  generate_julia_set(dim, num_points, step, dir_j);

  double start_scaling_factor = 1.0;
  double end_scaling_factor = 0.1;
  double scaling_factor_step = 0.05;
  std::string dir_m = "mandelbrot_set";
  //generate_scaled_outputs(dim, start_scaling_factor, end_scaling_factor, scaling_factor_step, dir_m);
  
}
