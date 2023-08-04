#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "fractals.h"

TEST_CASE("num_iter") {

  // Tests for the num_iter function
  /* 
     the num_iter function takes as input 4 arguments:
     z0: a point in the complex plane
     c: a complex constant 
     max_iter: the max number of iteration
     threshould: an arbitraty value to find if the orbit is finite
     The return value is the number of iterations for each z,c couple

     The 3 cases below test 3 couples for which respectively there is:
     
     finiet orbit for every nuber of iterations
     diverging oribit from the start
     diverging orbit after a while
  */
  
  SUBCASE("Point within threshold") {
    // Case in which the orbit stays limited in range max_iter
    std::complex<double> z0(0.5, 0.5); 
    std::complex<double> c(0.1, 0.1); 
    int max_iter = 50; 
    double thresh = 4; 

    int result = num_iter(z0, c, max_iter, thresh);

    CHECK(result == 50);
  }

  SUBCASE("Point outside threshold") {
    //Case in which immidiately it diverges
    std::complex<double> z0(2.0, 2.0);
    std::complex<double> c(0.1, 0.1);
    int max_iter = 50;
    double thresh = 4;

    int result = num_iter(z0, c, max_iter, thresh);

    CHECK(result == 0);
  }

  SUBCASE("num_iter in between 0 and max_iter") {
    //expected to divergence in between 0 and max_iters

    std::complex<double> z0(-1.9, 0.2); //coordinate in complex plane
    std::complex<double> c(0.1, 0.1); //complex constant
    int max_iter = 100; //max_iteraions
    double thresh = 4.0; //threshold

    int result = num_iter(z0, c, max_iter, thresh);

    CHECK(result > 0);
    CHECK(result < max_iter);
  }
}

TEST_CASE("Fractals getters") {

  /*
    the getters of the Fractals class are methods that should return the vals
    of its private attributes
    
    This test contatins 2 tests which check respectively:
    getter for dim -> getDimension()
    getter for board -> getBoard()
  */
  
  const int dim = 100;
  Fractals fractal(dim);
  
  SUBCASE("Fractals getDimension function") {
    //Tests that the getDimension function works properly
    CHECK(fractal.getDimension() == dim);
  }

  SUBCASE("Fractals getBoard function") {
    const std::vector<double>& board = fractal.getBoard();
    //Tests that the getBoard function works properly
    CHECK(board.size() == dim * dim);
  }
}



// Function to read PPM file as binary data, needed for test

std::vector<uint8_t> readPPM(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Cannot open file: " + filename);
    }

    std::stringstream buffer;
    buffer << file.rdbuf();

    std::string content = buffer.str();
    std::vector<uint8_t> data(content.begin(), content.end());

    return data;
}


TEST_CASE("mandelbrot_generator test") {
  int dim = 400;
  Mandelbrot test_mandelbrot_generation(dim);
  //image with scaling_factor 1 centered in 0, 0
  double scaling_factor = 1.0;
  double center_real = 0.0;
  double center_im = 0.0;
  test_mandelbrot_generation.mandelbrot_generator(scaling_factor, center_real, center_im);

  const std::string generatedImageFile = "./MANDELBROT/1.000000.ppm";
  const std::string referenceImageFile = "./TEST_IMG/1.000000.ppm";

    // Read binary data from generated and reference images
    std::vector<uint8_t> generatedImageData = readPPM(generatedImageFile);
    std::vector<uint8_t> referenceImageData = readPPM(referenceImageFile);

    // Compare the sizes of the images
    CHECK(generatedImageData.size() == referenceImageData.size());

    // Compare the content of the images byte by byte
    for (size_t i = 0; i < generatedImageData.size(); ++i) {
        CHECK(generatedImageData[i] == referenceImageData[i]);
    }
}
