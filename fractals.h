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


class fractals {
  
private:
    int dim;
    std::vector<double> board;

public:
  fractals(int dim) : dim(dim), board(dim * dim, 1.0) {}
  int getDimension() const {
    return dim;
  }
  const std::vector<double>& getBoard() const {
    return board;
  }

  void mandel_gen(const int scaling_factor) {
    //generates the mandelbrot set and zooms
    const int max_iterations = 100;
    // choose where to scale basing on math, as of right now it scales in
    // -2.-113, which is the "center" of the mandelbrot set
    const double z_real_bound = 2.48 * scaling_factor/ (this->dim - 1);
    const double z_im_bound = 2.26 *scaling_factor / (this->dim - 1);
    for (int x = 0; x < this->dim; ++x) {
      for (int y = 0; y < this->dim; ++y) {
	double real = x * z_real_bound - 2 * scaling_factor;
        double im = y * z_im_bound - 1.13 * scaling_factor;
        int number_iterations=
	  num_iter(0, std::complex<double>(real, im), max_iterations);
	this->board[y * this->dim + x] =
	  1.0 - number_iterations / static_cast<double>(max_iterations);
      }
    }
  }

  void julia_gen(const std::complex<double> c) {
    const int max_iterations = 100;
    const double z_real_bound = 4 / (this->dim - 1);
    const double z_im_bound = 4 / (this->dim - 1);
    for (int x = 0; x < this->dim; ++x) {
      for (int y = 0; y < this->dim; ++y) {
        double real = x * z_real_bound - 2;
        double im = y * z_im_bound - 2;
        int number_iterations =
	  num_iter(std::complex<double>(real, im), c, max_iterations);
        this->board[y * this->dim + x] =
            1.0 - number_iterations / static_cast<double>(max_iterations);
        }
      }
    }
};
