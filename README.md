# Mandelbrot and Julia fractals

This project aims at creating a tool to visualize the madelbrot set and julia fractals.
Mandelbrot and Julia fractals are one of the most intresting visual representations of complex number's dynamics in mathematics. Both fractals are generated through the same recursive equation known as the "Julia Set" equation, making them closely related yet visually distinct.


## Installation

To use the Fractal Generator, you need to have a C++ compiler and the necessary libraries installed. Here are the steps to set up the project:

1. Clone or download the repository.
2. Compile the C++ code using your preferred C++ compiler.

## User Section

### C++ Code

To use the Fractal Generator and customize the fractals rendered, follow these steps:

1. Open the `main.cpp` file in your preferred text editor or IDE.

2. Either compile it and run it right away or change some of the params first:

#### Examples

Here are some examples of generation that can also be found in the main. By changing the parameters in the following examples one can generate all sorts of fractals

- Generate a single Mandelbrot set:

```
Mandelbrot mandelbrot(image_dimension);
double scaling_factor = 2.0;
double center_real = 0.0;
double center_im = 0.0;
mandelbrot.mandelbrot_generator(scaling_factor, center_real, center_im);
```

- Generate multiple Mandelbrot sets with different scaling factors:

```
Mandelbrot mandelbrot(image_dimension);
int end_scaling_factor = 0;
double step = 0.1;
double zoom_center_real = -0.8;
double zoom_center_im = 0.156;
mandelbrot.mandelbrot_multiple_images(end_scaling_factor, step, zoom_center_real, zoom_center_im);
```

- Generate a single Julia set:

```
Julia julia(image_dimension);
std::complex<double> c(0.355, 0.355);
julia.julia_generator(c);
```

- Generate multiple Julia sets with different complex constants 'c':

```
Julia julia(image_dimension);
int num_points = 5;
double step_julia = 0.1;
julia.julia_multiple_images(num_points, step_julia);
```

### Python gifs

To generate gifs with the python code follow the following steps:

- make sure that the main contains exclusively a call on multiple_image functions

- run the bash script `pygif.sh` which does the following things:
  - remove directories with previous images
  - compile and run the cpp code in the main
  - execute the python code

## Julia Set equation

The mathematical basis of both Mandelbrot and Julia fractals lies in the iteration of a simple recursive equation involving complex numbers. Let's consider the equation in its basic form:

$$z_{n+1} = z_{n^{2}} + c$$

In this equation, $z_{n}$ is a complex number at iteration n, $z_{n+1}$ is the resulting complex number at iteration n+1, and c is a constant complex number. The idea is to start with a specific initial value for $z_{0}$ and repeatedly apply the equation to generate a sequence of complex numbers.

## Difference between generating Mandelbrot and Julia

For the Mandelbrot fractal, the initial value of $z_{0}$ remains constant for all iterations, typically set to zero. The constant c, however, varies across the complex plane. For each point in the complex plane, we determine the behavior of the sequence. If the magnitude of $z_{n}$ remains bounded (i.e., doesn't tend towards infinity) as the iterations continue indefinitely, the point is considered to be part of the Mandelbrot set. Otherwise, if the magnitude becomes unbounded, the point is not part of the set.

To generate the Julia fractal, both $z_{0}$ and c are specific values determined by the position on the complex plane. The initial value $z_{0}$ varies across the plane, while c remains fixed. Similar to the Mandelbrot set, points for which the sequence of $z_{n}$ values remain bounded are considered to be part of the Julia set.

<p float="left">
   <img src="https://github.com/Isi2000/EZFRACTALS/blob/main/README_IMG/j.png" data-canonical-src="https://github.com/Isi2000/EZFRACTALS/blob/main/README_IMG/j.png" width="400" height="400" />

   <img src="https://github.com/Isi2000/EZFRACTALS/blob/main/README_IMG/m.png" data-canonical-src="https://github.com/Isi2000/EZFRACTALS/blob/main/README_IMG/m.png" width="400" height="400" />
</p>

# Code

This section will be dedicated to explaining extensively how each piece of the code works.

## fractals.h


Header file which does most of the work, it contains the function that calculates the fractal, the class that is the board where they are rendered and the functiions that save the renderings in given directories.

### Fractals Class

The `Fractals` class is a base class containing useful methods and attributes for fractals rendering.

#### Public Methods

- `Fractals(int dim)`: Constructor to initialize the fractal generator with the given image dimension.
- `int getDimension() const`: Get the dimension of the image.
- `const std::vector<double> &getBoard() const`: Get the vector of pixels representing the Argand Gauss plane.
- `void board_gen(const double &z_real_bound, const double &z_im_bound, const double &center_real, const double &center_im, std::complex<double> c = std::complex<double>(0.0, 0.0), bool mandel_or_julia = true)`: Modify the board vector by applying the recursive formula to assign a numerical value (color) to each coordinate in the complex plane.
- `void save_to_file(const std::string &filename, const std::string &dirname)`: Save the board (image) to a file in the specified directory with the given filename.

### Mandelbrot Class

The `Mandelbrot` class is derived from the `Fractals` class and is used to create and visualize the Mandelbrot set.

#### Public Methods

- `Mandelbrot(int dim)`: Constructor to initialize the Mandelbrot set generator with the given image dimension.
- `std::complex<double> boundries(const double &scaling_factor)`: Calculate the boundaries of an image of the Mandelbrot set for a given scaling factor.
- `void mandelbrot_generator(const double &scaling_factor, const double &center_real, const double &center_im)`: Create the Mandelbrot set and save it to a file.
- `void mandelbrot_multiple_images(const int &end_scaling_factor, const double &step, const double &zoom_center_real, const double &zoom_center_im)`: Generate multiple images of the Mandelbrot set by calling the `mandelbrot_generator` function.

### Julia Class

The `Julia` class is derived from the `Fractals` class and is used to create and visualize Julia sets.

#### Public Methods

- `Julia(int dim)`: Constructor to initialize the Julia set generator with the given image dimension.
- `void julia_generator(const std::complex<double> &c)`: Generate a single Julia set for a given complex constant `c`.
- `void julia_multiple_images(const int &num_points, const double &step)`: Generate multiple images of Julia sets by calling the `julia_generator` function.

## main.cpp

It's the file in which the user calls the function in order to actually generate the fractals.

When using the code in its main features one usually only calls file from here and only compiles this cpp file.

Some examples of how to use the `main.cpp` file can be found in the User section

## giffer.py

This file is useful to visualize the rendering in cool ways. The purpose of this file is that of creating gif from a directory full of images.

1. **`gif_maker` Function**:
   - creates a gif from images in a given directory
   - `path` is the path from which to get the images
   - `name` is the name of the gif

# Results

In this section on can find a few of the things the code can render:

## Julia Sets

<p align="center">
   <img src="https://github.com/Isi2000/EZFRACTALS/blob/main/README_IMG/julia_set.gif" data-canonical-src="https://github.com/Isi2000/EZFRACTALS/blob/main/README_IMG/julia_set.gif" width="400" height="400" />

   <img src="https://github.com/Isi2000/EZFRACTALS/blob/main/README_IMG/julia_set1.gif" data-canonical-src="https://github.com/Isi2000/EZFRACTALS/blob/main/README_IMG/julia_set1.gif" width="400" height="400" />
</p>

## Mandelbrot Zoom
<p align = "center">
   <img src="https://github.com/Isi2000/EZFRACTALS/blob/main/README_IMG//mandelbrot_set.gif" data-canonical-src="https://github.com/Isi2000/EZFRACTALS/blob/main/README_IMG//mandelbrot_set.gif" width="400" height="400" />
</p>



# Translation_of_cpp_code_to_python.ipynb

This code provides a Python implementation for generating and visualizing fractals using the Mandelbrot and Julia set algorithms. The original C++ code has been translated into Python to achieve the same functionalities. Below is an overview of the key components and functionalities of the translated Python code.

I hope that this section will help non cpp coders better understand its cpp-optimized counterpart :)

## Functions

### `num_iter(z0, c, max_iter, thresh=4)`
This function calculates the number of iterations required for a given point `z0` and complex constant `c` to either diverge or reach a maximum number of iterations (`max_iter`). It uses the recursive formula `z = z**2 + c` and returns the number of iterations.

### `smkdir(name)`
A utility function for creating directories. It creates a directory if it doesn't exist or if the provided name is not a directory.

## Classes

### `Fractals`
A base class that contains methods and attributes for rendering fractals. It initializes the image dimension and the board (image) data.

- `get_dimension()`: Returns the dimension of the image.
- `get_board()`: Returns the board data representing the coordinates of the complex plane.
- `board_gen(z_real_bound, z_im_bound, center_real, center_im, c=0j, mandel_or_julia=True)`: Modifies the board by applying the recursive formula to assign values (colors) to each coordinate in the complex plane.

### `Mandelbrot(Fractals)`
A class for creating and visualizing the Mandelbrot set. It inherits from the `Fractals` class and introduces specific methods for generating Mandelbrot sets.

- `boundries(scaling_factor)`: Calculates the boundaries of an image of the Mandelbrot set for a given scaling factor.
- `mandelbrot_generator(scaling_factor, center_real, center_im)`: Creates the Mandelbrot set and saves it to a file.
- `mandelbrot_multiple_images(end_scaling_factor, step, zoom_center_real, zoom_center_im)`: Generates multiple images of the Mandelbrot set by varying the scaling factor.

### `Julia(Fractals)`
A class for creating and visualizing Julia sets. Similar to the `Mandelbrot` class, it inherits from the `Fractals` class and introduces methods for generating Julia sets.

- `julia_generator(c)`: Generates a single Julia set for a given complex constant `c`.
- `julia_multiple_images(num_points, step)`: Generates multiple images of Julia sets by varying the complex constant `c`.

## Example Usage

The example usage section at the end of the code demonstrates how to create instances of the `Mandelbrot` and `Julia` classes and generate images of the corresponding fractals. The `Mandelbrot` object is used to generate a sequence of Mandelbrot images with varying scaling factors and zoom centers. The `Julia` object generates multiple images of Julia sets by varying the complex constant `c`.

## How to Use

1. Ensure you have Python installed on your system.
2. Copy and paste the code into a Python file (e.g., `fractal_renderer.py`).
3. Run the script using a Python interpreter.
4. The program will generate Mandelbrot and Julia images in the respective directories ("MANDELBROT" and "JULIA") within the working directory.

The code provides an illustrative example of fractal rendering in Python, and you can extend and modify it to explore different fractal sets and rendering techniques.
