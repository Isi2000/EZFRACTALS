#include <complex>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int num_iter(std::complex<double> z0, std::complex<double> c, int max_iter,
             double thresh = 4) {
  /*
  Given a point on the complex plane a given constant c calculates the orbit
  given by the recursive formula z = z**2 + c of that point z0: starting point
  of the orbit c: complex constant thresh: arbitrary threshold to calculate if
  the orbit diverges

  returns the number of iterations before it diverges or reaches a given number
  of iters
 */
  std::complex<double> zn = std::move(z0);
  int it = 0;
  while ((std::norm(zn) < thresh) && it < max_iter) {
    zn = zn * zn + c;
    it += 1;
  }
  return it;
}

const std::string smkdir(const std::string &name) {
  /*
    smart mkdir works on multiple cases:
    if dir does not exist or if name is not a dir -> creates a directory
    if fails to create a directory for any reason in previous case -> warns
  */

  std::filesystem::path directoryPath = std::filesystem::current_path() / name;
  if (!std::filesystem::exists(directoryPath) ||
      !std::filesystem::is_directory(directoryPath)) {
    if (std::filesystem::create_directory(directoryPath)) {
      std::cout << "Directory created!!! :)\n";
    } else {
      std::cout << "Failed to create directory.\n";
    }
  }
  return name;
}

class Fractals {
  // Mother class containing useful methods and attributes for fractals rendering
private:
  int dim; // dimension of the image
  std::vector<double> board; // vector rapresenting the pixels of the images
public:
  Fractals(int dim) : dim(dim), board(dim * dim, 1.0) {}
  int getDimension() const { return dim; }
  const std::vector<double> &getBoard() const { return board; }
  void board_gen(const double &z_real_bound, const double &z_im_bound,
                 const double &center_real, const double &center_im,
                 std::complex<double> c = std::complex<double>(0.0, 0.0),
                 bool mandel_or_julia = true) {
    /*
      Modifies inplace the board vector applying the recursive formula to assign
      a numerical value (color) to each coordinate in the complex plane
      z_real_bound: boundries of the image on the real axis
      z_im_bound: boundries of the image on the imaginary axis
      center_real: center of the image on real axis (translation of 0 in the
      real axis) center_im: center of the image on imaginary axis (translation
      of 0 in the imaginary axis) c: complex constant to generate julia set
      mandel_or_julia: 0 -> generates mandelbrot set, 1 -> generates julia set
     */
    const int max_iterations = 300;
    for (int x = 0; x < this->dim; ++x) {
      for (int y = 0; y < this->dim; ++y) {
        double real = x * z_real_bound + center_real;
        double im = y * z_im_bound + center_im;
        int number_iterations = 0;
        if (mandel_or_julia) {
          number_iterations =
              num_iter(0.0, std::complex<double>(real, im), max_iterations);
        } else {
          number_iterations =
              num_iter(std::complex<double>(real, im), c, max_iterations);
        }
        this->board[y * this->dim + x] =
            1.0 - number_iterations / static_cast<double>(max_iterations);
      }
    }
  }

  void save_to_file(const std::string &filename, const std::string &dirname) {
    /*
      saves the board (image) in a given directory with a given filename
      filename: name of the file containing data
      dirname: name of the directory containing the image
     */
    std::string path = "./";
    std::string fn = path + dirname + "/" + filename + ".ppm";
    std::ofstream outfile(fn);

    // ppm format, the following lines are standard
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

class Mandelbrot : public Fractals {
  // class that inherits from Fractals
  // creates and renders the mandelbrot set
private:
  std::string data_dir;
public:
  Mandelbrot(int dim) : Fractals(dim), data_dir("MANDELBROT") {
    smkdir(this->data_dir);
  }
  std::complex<double> boundries(const double &scaling_factor) {
    /*
      calculates the boundries of an image of the mandelbrot set for a given
      scaling factor
      scaling_factor: the scaling factor of the image

      returns a complex number, the boundries of the images are the real and
      imaginary parts of this number
    */

    const double unscaled_real_domain = 2.48;
    const double unscaled_im_domain = 2.26;

    const double z_real_bound =
        unscaled_real_domain * scaling_factor / (getDimension() - 1);
    const double z_im_bound =
        unscaled_im_domain * scaling_factor / (getDimension() - 1);
    return std::complex(z_real_bound, z_im_bound);
  }

  void mandelbrot_generator(const double &scaling_factor,
                            const double &center_real,
                            const double &center_im) {
    /*
      Creates the mandelbrot set and saves it to file
      scaling_factor: it's the level of zoom on the image
      center_real: where the image is centered on the real axis
      center_im: where the image is centered on the imaginary axis
     */
    bool mandelbrot_mode = true; // sets the mode to mandelbrot

    const double real_bound = boundries(scaling_factor).real();
    const double im_bound = boundries(scaling_factor).imag();

    // if zooming on the image the center of the image needs to change
    const double zoom_center_real = center_real - 2.0 * scaling_factor;
    const double zoom_center_im = center_im - 1.13 * scaling_factor;

    board_gen(real_bound, im_bound, zoom_center_real, zoom_center_im,
              mandelbrot_mode);

    // the file in which the image is stored is called as its scaling_factor
    std::string filename = std::to_string(scaling_factor);
    save_to_file(filename, this->data_dir);
  }

  void mandelbrot_multiple_images(const int &end_scaling_factor,
                                  const double &step,
                                  const double &zoom_center_real,
                                  const double &zoom_center_im) {
    /*
      generates multiple images of the mandebrot set by calling the generate
      mandelbrot function end_scaling_factor: last scaling factor before
      stopping zoom zoom_center_real: where the image is centered on the real
      axis zoom_center_im: where the image is centered on the imaginary axis
    */
    double scaling_factor = 3.0;
    while (scaling_factor > end_scaling_factor) {
      scaling_factor = scaling_factor - step;
      mandelbrot_generator(scaling_factor, zoom_center_real, zoom_center_im);
    }
  }
};

class Julia : public Fractals {
  // class that inherits from Fractals
  // creates and renders the  julia sets
private:
  std::string data_dir;
public:
  Julia(int dim) : Fractals(dim), data_dir("JULIA") { smkdir(this->data_dir); }

  void julia_generator(const std::complex<double> &c) {
    /*
      generates a single julia set for a given c complex constant
      c: complex constant associated to the julia set generated
    */
    bool julia_mode = false; // sets the mode to Julia

    const double unscaled_real_domain = 4;
    const double unscaled_im_domain = 4;

    const double real_bound = unscaled_real_domain / (getDimension() - 1);
    const double im_bound = unscaled_im_domain / (getDimension() - 1);

    double center_real = -2.0;
    double center_im = -2.0;

    board_gen(real_bound, im_bound, center_real, center_im, c, julia_mode);
    std::string filename =
        std::to_string(c.real()) + "_" + std::to_string(c.imag());
    save_to_file(filename, this->data_dir);
  }

  void julia_multiple_images(const int &num_points, const double &step) {
    /*
      generates multiple images of julia sets by calling the generate julia
      function how the c constant changes is chosen arbitrarly, any other orbit
      can be coorect as long as it doesn't diverge

      num_points: number of images generated
      step: how much does the c constant changes between image generated
    */
    for (int i = 0; i < num_points; ++i) {
      double real_c = 0.0 + i * step;
      double imag_c = 0.0 - i * step;
      std::complex<double> c(real_c, imag_c);
      julia_generator(c);
    }
  }
};
