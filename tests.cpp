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
TEST_CASE("Test smkdir function") {
  /*
    Tests the smart mkdir function in the following cases:
    creates a new directory that does not exist
    calls on a direcoty that already exist
  */
  SUBCASE("smkdir of non existing dir"){
    // Create a new directory
    std::string dirName1 = "test_directory_1";
    std::string result1 = smkdir(dirName1);
    REQUIRE(result1 == dirName1);
    std::filesystem::remove_all(dirName1); // Cleanup
  }
    SUBCASE("smkdir of a existing dir"){
    //calls smkdir on directory that already exists
    std::string dirName2 = "test_directory_2";
    smkdir(dirName2); // Creating the directory first
    std::string result2 = smkdir(dirName2);
    REQUIRE(result2 == dirName2);
    std::filesystem::remove_all(dirName2); // Cleanup
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
  /**
  Reads a PPM (Portable Pixmap) image file and returns its content as a vector of bytes.
 
 filename: The filename of the PPM image file to be read.
  A std::vector<uint8_t> containing the binary data of the PPM image.
 */
  
  //runtime error is somehow the file cannot be opened
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


TEST_CASE("generators test") {

  //test the generators with benchmark images stored in the TEST_IMAGES folder
  //to look at the benchmark images look at test_images.md in TEST_IMAGES
  // The size of the images choosen is 400

  int dim = 400;

  SUBCASE("mandelbrot_generator test") {
    /*
      tests the mandelbrot_generator function:
      The benchmark image params, which are the same passed to the generator, are the following:
      scaling_factor = 1.0
      center_real = 0.0
      center_im = 0.0
      
    checks that the images are the same size, then checks each pixel is the same
    */
      
  Mandelbrot test_mandelbrot_generation(dim);
  //image with scaling_factor 1 centered in 0, 0
  double scaling_factor = 1.0;
  double center_real = 0.0;
  double center_im = 0.0;
  test_mandelbrot_generation.mandelbrot_generator(scaling_factor, center_real, center_im);

  const std::string generatedImageFile = "./MANDELBROT/1.000000.ppm";
  const std::string referenceImageFile = "./TEST_IMAGES/1.000000.ppm";

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

  SUBCASE("julia_generator test") {
    /*
      tests the mandelbrot_generator function:
      The benchmark image params, which are the same passed to the generator, are the following:
      dim = 400
      complex constant (c) = 0.3, 0.45
      
    checks that the images are the same size, then checks each pixel is the same
    */
  Julia test_julia_generation(dim);
  //image with scaling_factor 1 centered in 0, 0
  std::complex<double> c(0.3, -0.45);
  
  test_julia_generation.julia_generator(c);

  const std::string generatedImageFile = "./JULIA/0.300000_-0.450000.ppm";
  const std::string referenceImageFile = "./TEST_IMAGES/0.300000_-0.450000.ppm";

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
}



TEST_CASE("mandelbrot_multiple_images test") {
    int dim = 400;
    double end_scaling_factor = 0.1;
    double scaling_factor_step = 0.1;
    const double center_real = -0.74001;
    const double center_im = 0.0;

    Mandelbrot test_M_m_i(dim);
    test_M_m_i.mandelbrot_multiple_images(end_scaling_factor, scaling_factor_step, center_real, center_im);

    SUBCASE("Test Generated Files Exist") {
        CHECK(std::filesystem::exists(std::filesystem::path("MANDELBROT") / "1.000000.ppm"));
        CHECK(std::filesystem::exists(std::filesystem::path("MANDELBROT") / "0.900000.ppm"));
        CHECK(std::filesystem::exists(std::filesystem::path("MANDELBROT") / "0.800000.ppm"));
        CHECK(std::filesystem::exists(std::filesystem::path("MANDELBROT") / "0.700000.ppm"));
    }
    /*
    SUBCASE("Benchmark image") {
      const std::string generatedImageFile = "./MANDELBROT/0.900000.ppm";
      const std::string referenceImageFile = "./TEST_IMAGES/0.900000.ppm";

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
    */
}

TEST_CASE("generate_julia_set test") {
    int num_points = 5;
    double step = 0.1;
    int dim = 400;

    Julia test_J_m_i(dim);
    test_J_m_i.julia_multiple_images(num_points, step);

    SUBCASE("Test Generated Files Exist") {
        CHECK(std::filesystem::exists(std::filesystem::path("JULIA") / "0.000000_0.000000.ppm"));
        CHECK(std::filesystem::exists(std::filesystem::path("JULIA") / "0.100000_-0.100000.ppm"));
        CHECK(std::filesystem::exists(std::filesystem::path("JULIA") / "0.200000_-0.200000.ppm"));
        CHECK(std::filesystem::exists(std::filesystem::path("JULIA") / "0.300000_-0.300000.ppm"));
        CHECK(std::filesystem::exists(std::filesystem::path("JULIA") / "0.400000_-0.400000.ppm"));
    }

    SUBCASE("Benchmark image") {      
  const std::string generatedImageFile = "./JULIA/0.300000_-0.300000.ppm";
  const std::string referenceImageFile = "./TEST_IMAGES/0.300000_-0.300000.ppm";

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
 }

