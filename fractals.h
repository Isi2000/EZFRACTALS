#include <cmath>
#include <complex>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>


int num_iter(std::complex<double> z0, std::complex<double> c, int max_iter,
             double thresh = 4) {
  /*
function that given a point on the complex plane a given constant c calculates
the orbit given by the recursive formula z = z**2 + c of that point
   */
  std::complex<double> zn = std::move(z0);
  int it = 0;
  while ((std::norm(zn) < thresh) && it < max_iter) {
    zn = zn * zn + c;
    it += 1;
  }
  return it;
}
