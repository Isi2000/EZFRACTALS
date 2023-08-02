#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "fractals.h"

TEST_CASE("num_iter") {

  // Test case for the num_iter function
  
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
    std::complex<double> z0(-1.9, 0.2);
    std::complex<double> c(0.1, 0.1);
    int max_iter = 100;
    double thresh = 10000.0;

    int result = num_iter(z0, c, max_iter, thresh);
    CHECK(result > 0);
    CHECK(result < max_iter);
  }
}
