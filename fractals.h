#include <complex>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>

int num_iter(std::complex<double> z0, std::complex<double> c, int max_iter,
             double thresh = 4) {
  std::complex<double> zn = std::move(z0);
  int it = 0;
  while ((std::norm(zn) < thresh) && it < max_iter) {
    zn = zn * zn + c;
    it += 1;
  }
  return it;
}

const std::string smkdir(const std::string &name) {
  std::filesystem::path directoryPath = std::filesystem::current_path() / name;
  bool existence = std::filesystem::exists(directoryPath);
  bool isdir = std::filesystem::is_directory(directoryPath);
  if ( existence && isdir) {
    std::cout << "Directory already exists.\n";
  } else {
    if (std::filesystem::create_directory(directoryPath)) {
      std::cout << "Directory created!!! :)\n";
    } else {
      std::cout << "Failed to create directory.\n";
    }
  }
  return name;
}

class Fractals {
private:
  int dim;
  std::vector<double> board;

public:
  Fractals(int dim) : dim(dim), board(dim * dim, 1.0) {}
  int getDimension() const { return dim; }
  const std::vector<double> &getBoard() const { return board; }
  void board_gen(const double &z_real_bound,
               const double &z_im_bound,
               const double &center_real,
               const double &center_im,
               std::complex<double> c = std::complex<double>(0.0, 0.0),
               bool mandel_or_julia = true)
{
    const int max_iterations = 300;
    for (int x = 0; x < this->dim; ++x) {
        for (int y = 0; y < this->dim; ++y) {
            double real = x * z_real_bound + center_real;
            double im = y * z_im_bound + center_im;
            int number_iterations = 0;
            if (mandel_or_julia) {
                // Generate the Mandelbrot set (c = 0)
	      number_iterations = num_iter( 0.0, std::complex<double>(real, im), max_iterations);
            }
            else {
                // Generate the Julia set with the specified constant c
                number_iterations = num_iter(std::complex<double>(real, im), c, max_iterations);
            }
            this->board[y * this->dim + x] =
                1.0 - number_iterations / static_cast<double>(max_iterations);
        }
    }
}


  void save_to_file(const std::string &filename, const std::string &dirname) {
    std::string path = "./";
    std::string fn = path + dirname + "/" + filename + ".ppm";
    std::ofstream outfile(fn);
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
  // class that inherits from Fractals for creating and visualizing the
  // mandelbrot set with different scaling on different points
private:
  std::string data_dir;
public:
  Mandelbrot(int dim): Fractals(dim), data_dir("MANDELBROT") {smkdir(this->data_dir);}
  std::complex<double> boundries(const double &scaling_factor) {
    /*
      calculates the boundries of an image of the mandelbrot set for a given
      scaling factor
    */

    const double unscaled_real_domain = 2.48;
    const double unscaled_im_domain = 2.26;
    const double z_real_bound =
      unscaled_real_domain * scaling_factor / (getDimension() - 1);
    const double z_im_bound =
      unscaled_im_domain * scaling_factor / (getDimension() - 1);
    return std::complex(z_real_bound, z_im_bound) ;
  }

  void mandelbrot_generator(const double &scaling_factor,
                            const double &center_real,
                            const double &center_im) {
    /*
      Creates the mandelbrot set and saves it to file
      scaling_factor: it's the level of zoom on the image
      center_real: where the image is centered on the real axis
      where the image is centered on the real axis
     */
    bool mandelbrot_mode = true; //sets the mode to mandelbrot
    const double real_bound = boundries(scaling_factor).real();
    const double im_bound = boundries(scaling_factor).imag();
    board_gen(real_bound, im_bound, center_real, center_im, mandelbrot_mode);
    std::string filename = std::to_string(scaling_factor);
    save_to_file(filename, this->data_dir);
  }
  
  void mandelbrot_multiple_images(const int &end_scaling_factor, const double &step, const double &center_zoom_real, const double &center_zoom_im) {
    double scaling_factor = 1.0;
    while (scaling_factor > end_scaling_factor) {
      scaling_factor = scaling_factor - step;
      mandelbrot_generator(scaling_factor, center_zoom_real, center_zoom_im);
	}
  }
};

class Julia : public Fractals {

  std::string data_dir;
public:
  Julia(int dim): Fractals(dim), data_dir("JULIA") {smkdir(this->data_dir);}

  void julia_generator(const std::complex<double> &c) {
    bool julia_mode = false;
    
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
      for (int i = 0; i < num_points; ++i) {
	double real_c = 0.0 + i * step;
	double imag_c = 0.0 - i * step;
	std::complex<double> c(real_c, imag_c);
	julia_generator(c);
      }
  }
};

