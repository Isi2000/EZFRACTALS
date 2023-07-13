#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include"doctest.h"
#include"fractals.h"

TEST_CASE("num_iter") {
  // Test case for the num_iter function

  SUBCASE("Point within threshold") {
    std::complex<double> z0(0.5, 0.5);
    std::complex<double> c(0.1, 0.1);
    int max_iter = 50;
    double thresh = 4;

    int result = num_iter(z0, c, max_iter, thresh);

    CHECK(result == 50);
  }

  SUBCASE("Point outside threshold") {
    std::complex<double> z0(2.0, 2.0);
    std::complex<double> c(0.1, 0.1);
    int max_iter = 50;
    double thresh = 4;

    int result = num_iter(z0, c, max_iter, thresh);

    CHECK(result == 0);
  }
}


TEST_CASE("BoardConstructorTest - DefaultValues") {
    const int dim = 10;
    fractals board(dim);

    CHECK(board.getDimension() == dim);

    const std::vector<double>& boardData = board.getBoard();
    CHECK(boardData.size() == dim * dim);
    /*
    for (const auto& value : boardData) {
        CHECK(value == 1.0);
    }
    */
}

TEST_CASE("Test mandel_gen") {
  fractals f(100); // Create a fractals object with a dimension of 100
  f.mandel_gen(1); // Generate the Mandelbrot set with a scaling factor of 1

  // Get the generated board from the fractals object
  const std::vector<double>& board = f.getBoard();

  // Check if the dimensions of the generated board are correct
  CHECK(board.size() == 10000);

  // Check if the values in the board are within the expected range
  for (double value : board) {
    CHECK(value >= 0.0);
    CHECK(value <= 1.0);
  }
}


TEST_CASE("Test julia_gen") {
  fractals f(100);// Create a fractals object with a dimension of 100
  std::complex<double> z(0.2,0.2);

  f.julia_gen(z); // Generate the Mandelbrot set with a scaling factor of 1

  // Get the generated board from the fractals object
  std::vector<double>& board = f.getBoard();

  // Check if the dimensions of the generated board are correct
  CHECK(board.size() == 10000);

  // Check if the values in the board are within the expected range
  for (double value : board) {
    CHECK(value >= 0.0);
    CHECK(value <= 1.0);
  }
}


TEST_CASE("Testing smkdir") {
  fractals f(10);
  const std::string directoryName = "test_directory";

  // Check if the directory exists before running the test
  bool directoryExistsBefore = std::filesystem::exists(directoryName);

  // Call the smkdir function
  f.smkdir(directoryName);

  // Check if the directory was created
  bool directoryExistsAfter = std::filesystem::exists(directoryName);
  CHECK(directoryExistsAfter);

  // Clean up: Remove the directory created during the test
  std::filesystem::remove(directoryName);

  // Check if the directory was successfully removed
  bool directoryExistsAfterCleanup = std::filesystem::exists(directoryName);
  CHECK_FALSE(directoryExistsAfterCleanup);

  // Check if the directory existed before running the test
  CHECK_EQ(directoryExistsBefore, std::filesystem::exists(directoryName));
}



