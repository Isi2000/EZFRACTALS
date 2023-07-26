# Mandelbrot and Julia fractals

This project aims at creating a tool to visualize the madelbrot set and julia fractals.
Mandelbrot and Julia fractals are one of the most intresting visual representations of complex number's dynamics in mathematics. Both fractals are generated through the same recursive equation known as the "Julia Set" equation, making them closely related yet visually distinct.

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

1. **`num_iter` Function**:
   - This function computes the number of iterations needed for a point on the complex plane, represented by `z0`, to escape the given threshold (`thresh`) or reach the maximum number of iterations (`max_iter`).
   - It takes two complex numbers `z0` and `c` as inputs and iterates the formula `z = z^2 + c` until the norm of `z` exceeds the threshold or the maximum number of iterations is reached.
   - The function returns the number of iterations taken to escape or reach the threshold.

2. **`fractals` Class**:
   - This class represents a grid of fractals with a specified dimension.
   - It contains a private data member `board`, which is a 1D vector representing the grid of fractal values.
   - The class provides a constructor that initializes the `board` vector with all values set to 1.0 (white).
   - It also has member functions like `mandel_gen` and `julia_gen`, which generate Mandelbrot and Julia fractals, respectively.

3. **`mandel_gen` Function**:
   - This function generates the Mandelbrot set and zooms into it based on a scaling factor.
   - It takes a scaling factor as input, which determines the extent of zoom into the Mandelbrot set.
   - The function calculates the complex coordinates for each point on the grid based on the scaling factor and the grid dimensions.
   - It then calls the `num_iter` function to compute the fractal value for each point and stores it in the `board` vector.

4. **`julia_gen` Function**:
   - This function generates the Julia set for a given complex variable `c`.
   - It takes a complex number `c` as input, representing the constant in the Julia set formula `z = z^2 + c`.
   - The function calculates the complex coordinates for each point on the grid, similar to `mandel_gen`.
   - It calls the `num_iter` function to compute the fractal value for each point and stores it in the `board` vector.

5. **`smkdir` Function**:
   - This function is a helper function that creates a directory with the provided name if it does not already exist.
   - It takes a directory name as input and checks whether the directory exists.
   - If the directory does not exist, it creates the directory using `std::filesystem::create_directory`.

6. **`save_to_file_j` Function**:
   - This function saves the board (grid of Julia fractals) to a file in the specified directory.
   - It takes a complex number `c` (used to generate the specific Julia fractal) and the directory name as input.
   - The function constructs the filename using the real and imaginary parts of `c` and the provided directory name.
   - It then opens an output file stream and writes the PPM file format headers and the pixel values for each point on the grid.

7. **`save_to_file_m` Function**:
   - This function is similar to `save_to_file_j`, but it saves the board (grid of Mandelbrot set) to a file.
   - It takes a scaling factor and the directory name as input and constructs the filename accordingly.

8. **`generate_scaled_outputs` Function**:
   - This function generates multiple Mandelbrot sets with different scaling factors.
   - It takes the grid dimension, start scaling factor, end scaling factor, scaling factor step, and the output directory name as input.
   - The function iterates through scaling factors in reverse order and generates the Mandelbrot set for each scaling factor using `mandel_gen`.
   - It saves each generated set to a separate PPM file using `save_to_file_m`.

9. **`generate_julia_set` Function**:
   - This function generates multiple Julia sets with different complex variables 'c'.
   - It takes the grid dimension, the number of points, the step size, and the output directory name as input.
   - The function iterates through the points and calculates the 'c' value based on the step and the loop index.
   - It then generates the Julia fractal for each 'c' value using `julia_gen` and saves it to a separate PPM file using `save_to_file_j`.



## main.cpp

It's the file in which the user calls the function in order to actually generate the fractals. When using the code in its main features one usually only calls file from here and only compiles this cpp file.

## giffer.py

This file is useful to visualize the rendering in cool ways. The purpose of this file is that of creating gif from a directory full of images.

1. **`gif_maker` Function**:
   - creates a gif from images in a given directory
   - `path` is the path from which to get the images
   - `name` is the name of the gif

# Results

In this section on can find a few of the things the code can render:

##Julia Sets

<p align="center">
   <img src="https://github.com/Isi2000/EZFRACTALS/blob/main/README_IMG/julia_set.gif" data-canonical-src="https://github.com/Isi2000/EZFRACTALS/blob/main/README_IMG/julia_set.gif" width="400" height="400" />

   <img src="https://github.com/Isi2000/EZFRACTALS/blob/main/README_IMG/julia_set1.gif" data-canonical-src="https://github.com/Isi2000/EZFRACTALS/blob/main/README_IMG/julia_set1.gif" width="400" height="400" />
</p>

## Mandelbrot Zoom
<p align = "center">
   <img src="https://github.com/Isi2000/EZFRACTALS/blob/main/README_IMG//mandelbrot_set.gif" data-canonical-src="https://github.com/Isi2000/EZFRACTALS/blob/main/README_IMG//mandelbrot_set.gif" width="400" height="400" />
</p>
