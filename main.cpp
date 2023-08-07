#include "fractals.h"


int main() {
     int image_dimension = 300; // Set the desired image dimension here

    // Create an instance of the Mandelbrot class
    Mandelbrot mandelbrot(image_dimension);

    // Create an instance of the Julia class
    Julia julia(image_dimension);

    // Customization and Rendering of Fractals
    // =======================================

    // Example 1: Generate a Mandelbrot set
    double scaling_factor = 2.0; // Set the desired scaling factor for the Mandelbrot set
    double center_real = 0.0; // Set the desired center point on the real axis
    double center_im = 0.0; // Set the desired center point on the imaginary axis
    mandelbrot.mandelbrot_generator(scaling_factor, center_real, center_im);

    // Example 2: Generate multiple Mandelbrot sets with different scaling factors
    int end_scaling_factor = 0.3; // Set the last scaling factor before stopping zoom
    double step = 0.1; // Set the step size for changing the scaling factor
    double zoom_center_real = -0.8; // Set the desired center point on the real axis for zooming
    double zoom_center_im = 0.156; // Set the desired center point on the imaginary axis for zooming
    mandelbrot.mandelbrot_multiple_images(end_scaling_factor, step, zoom_center_real, zoom_center_im);

    // Example 3: Generate a Julia set with a specific complex constant 'c'
    std::complex<double> c(0.355, 0.355); // Set the desired complex constant 'c'
    julia.julia_generator(c);

    // Example 4: Generate multiple Julia sets with different complex constants 'c'
    int num_points = 9; // Set the number of Julia sets to generate
    double step_julia = 0.05; // Set the step size for changing the complex constant 'c'
    julia.julia_multiple_images(num_points, step_julia);

    return 0;
}

