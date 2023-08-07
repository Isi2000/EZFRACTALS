#include "fractals.h"

int main() {
    int dim = 400;
    double end_scaling_factor = 0.1;
    double scaling_factor_step = 0.1;
    const double center_real = -0.74001;
    const double center_im = 0.0;

    Mandelbrot test_M_m_i(dim);
    test_M_m_i.mandelbrot_multiple_images(end_scaling_factor, scaling_factor_step, center_real, center_im);

    int num_points = 5;
    double step = 0.1;
    Julia test_J_m_i(dim);
    test_J_m_i.julia_multiple_images(num_points, step);

}
