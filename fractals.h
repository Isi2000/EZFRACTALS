#include <cmath>
#include <complex>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int num_iter(std::complex<double> z0, std::complex<double> c, int max_iter,
             double thresh = 4) {
  /*
    function that given a point on the complex plane a given constant c
    calculates the orbit given by the recursive formula z = z**2 + c of that
    point
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
  // board to rapresent the mandelbrot and julia fractals
private:
  int dim;
  std::vector<double> board;

public:
  fractals(int dim) : dim(dim), board(dim * dim, 1.0) {}
  int getDimension() const { return dim; }
  const std::vector<double> &getBoard() const { return board; }
  void mandel_gen(const double &scaling_factor = 1.0,
                  const double &zoom_real = -2.00,
                  const double &zoom_imaginary = -1.13) {
    /*
       generates the mandelbrot set and can zoom in an arbitrary point (re, im)
       scaling_factor: how much it scales
       zoom_real: real coordinate in Argand Gauss plane for zoom
       zoom_imaginary: imag coordinate in Argand Gauss plane zoom
       The numeric constants are choosen in a way so that the img is centered
    */

    const double z_real_bound = 2.48 * scaling_factor / (this->dim - 1);
    const double z_im_bound = 2.26 * scaling_factor / (this->dim - 1);
    for (int x = 0; x < this->dim; ++x) {
      for (int y = 0; y < this->dim; ++y) {
        double real = (x)*z_real_bound - 2 * scaling_factor + zoom_real;
        double im = y * z_im_bound - 1.13 * scaling_factor + zoom_imaginary;
        int number_iterations =
            num_iter(0, std::complex<double>(real, im), 300);
        this->board[y * this->dim + x] = 1.0 - number_iterations / 300.0;
      }
    }
  }
  void julia_gen(const std::complex<double> &c) {
    /*
       Generates the Julia set as a function of a complex variable 'c'
    */
    const int max_iterations = 100;
    const double z_real_bound = 4.0 / (dim - 1);
    const double z_im_bound = 4.0 / (dim - 1);

    for (int x = 0; x < dim; ++x) {
      for (int y = 0; y < dim; ++y) {
        double real = x * z_real_bound - 2.0;
        double im = y * z_im_bound - 2.0;
        int number_iterations =
            num_iter(std::complex<double>(real, im), c, max_iterations);
        board[y * dim + x] =
            1.0 - number_iterations / static_cast<double>(max_iterations);
      }
    }
  }

  const std::string smkdir(const std::string &name) {
    /*
       smart mkdir, checks if there is a dir and if there is not it creates it
    */

    std::filesystem::path directoryPath =
        std::filesystem::current_path() / name;

    if (std::filesystem::exists(directoryPath) &&
        std::filesystem::is_directory(directoryPath)) {
      std::cout << " ... "
                << "\n"; // ... = dir arleady existing
    } else {
      if (std::filesystem::create_directory(directoryPath)) {
        std::cout << "Directory created!!! :)" << '\n';
      } else {
        std::cout << ":(" << '\n';
      }
    }
    return name;
  }

  void save_to_file_j(const std::complex<double> &c, const std::string &p) {
    /*
     saves the board in directory created with smkdir
     c: constant associated with julia set
     p: directory name
     */

    std::string dir_name = smkdir(p) + '/';
    std::string path = "./";
    std::string filename = path + dir_name + std::to_string(c.real()) + "_" +
                           std::to_string(c.imag()) + ".ppm";
    std::ofstream outfile(filename);
    outfile << "P3\n";
    outfile << dim << " " << dim << "\n";
    outfile << "255\n";

    for (int i = 0; i < this->dim; i++) {
      for (int j = 0; j < this->dim; j++) {
        int pixel_value =
            static_cast<int>(this->board[i * this->dim + j] * 255);
        outfile << pixel_value << " " << pixel_value << " " << pixel_value
                << " ";
      }
      outfile << "\n";
    }

    outfile.close();
  }

  void save_to_file_m(const double &scaling_factor, const std::string &p) {
    /*
    saves the board in directory created with smkdir
    scaling_factor: scaling coefficient to zoom
    p: directory name
    */

    std::string dir_name = smkdir(p) + '/';
    std::string path = "./";
    std::string filename = path + dir_name + "output_scaling_" +
                           std::to_string(scaling_factor) + ".ppm";
    std::ofstream outfile(filename);
    // format for ppm file
    outfile << "P3\n";
    outfile << dim << " " << dim << "\n";
    outfile << "255\n";

    for (int i = 0; i < this->dim; i++) {
      for (int j = 0; j < this->dim; j++) {
        int pixel_value =
            static_cast<int>(this->board[i * this->dim + j] * 255);
        outfile << pixel_value << " " << pixel_value << " " << pixel_value
                << " ";
      }
      outfile << "\n";
    }

    outfile.close();
  }
};

void generate_scaled_outputs(const int &dim, const double &start_scaling_factor,
                             const double &end_scaling_factor,
                             const double &scaling_factor_step,
                             const std::string &dir,
                             const double &zoom_real = -0.7004,
                             const double &zoom_imaginary = -0.1) {

  /*
    generates images of the mandelbrot set with different scaling factors
    dim: resolution of the board
    start_scaling_factor: initial value of the scaling factor
    end_scaling: last value of the scaling factor
    dir: location for the generated files
    last 2 parameters are reference to the gen function:
    The default is a fairly intresting point to zoom, change them and have fun!
  */

  for (double scaling_factor = start_scaling_factor;
       scaling_factor >= end_scaling_factor;
       scaling_factor -= scaling_factor_step) {
    fractals board(dim);
    board.mandel_gen(scaling_factor, zoom_real, zoom_imaginary);
    board.save_to_file_m(scaling_factor, dir);
  }
}

void generate_julia_set(const int &dim, const int &num_points,
                        const double &step, const std::string &dir) {

  /*
    generates images of julia sets with different complex constant
    dim: resolution of the board
    num_points: number of images
    end_scaling: last value of the scaling factor
    dir: location for the generated files
   */
  for (int i = 0; i < num_points; ++i) {
    double real_c = 0.0 + i * step;
    double imag_c = 0.0 - i * step;
    std::complex<double> c(real_c, imag_c);
    fractals board(dim);
    board.julia_gen(c);
    board.save_to_file_j(c, dir);
  }
}
