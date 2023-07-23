#include "fractals.h"

int main() {
  fractals j(800);
  std::complex<double> c (0.3, -0.45);
    std::string img = "README_IMG";
  j.julia_gen(c);
  j.save_to_file_j(c, img); //single image of julia set
  

  fractals m(800);
  double scaling_factor = 0.9;
  m.mandel_gen(scaling_factor, -2, -1.13);
  m.save_to_file_j(scaling_factor, img); //single image of mandelbrot set
  


  int dim = 400;
  int num_points = 50;
  double step = 0.01;
  std::string dir_j = "julia_set";
  generate_julia_set(dim, num_points, step, dir_j); //images for creating a gif of the julia set

  double start_scaling_factor = 1.5;
  double end_scaling_factor= 0.5;
  double step_ = 0.05;
  std::string dir_m = "mandelbrot_zoom";
  generate_scaled_outputs(dim, start_scaling_factor, end_scaling_factor, step_, dir_m);
  
}
