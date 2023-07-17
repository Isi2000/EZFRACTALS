#include "fractals.h"

int main() {
  
  int dim = 200;
  /*
  double ssf = 1.5;
  double esf = 1.0;
  double s = 0.1;
  std::string nd = "M";
  generate_scaled_outputs(dim, ssf, esf, s, nd);
  return 0;
  */
  int np = 10;
  double step = 0.1;
  std::string dir = "jj";
  generate_julia_set(dim, np, step, dir);
  
}
