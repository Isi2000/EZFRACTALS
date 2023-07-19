# EZFRACTALS


## Mandelbrot and Julia fractals

This project aims at creating a tool to visualize the madelbrot set and julia fractals.
Mandelbrot and Julia fractals are one of the most intresting visual representations of complex number's dynamics in mathematics. Both fractals are generated through the same recursive equation known as the "Julia Set" equation, making them closely related yet visually distinct.

## Julia Set equation

The mathematical basis of both Mandelbrot and Julia fractals lies in the iteration of a simple recursive equation involving complex numbers. Let's consider the equation in its basic form:

$$z_{n+1} = z_{n^{2}} + c$$

In this equation, $z_{n}$ is a complex number at iteration n, $z_{n+1}$ is the resulting complex number at iteration n+1, and c is a constant complex number. The idea is to start with a specific initial value for $z_{0}$ and repeatedly apply the equation to generate a sequence of complex numbers.

## Difference between generating Mandelbrot and Julia

For the Mandelbrot fractal, the initial value of $z_{0}$ remains constant for all iterations, typically set to zero. The constant c, however, varies across the complex plane. For each point in the complex plane, we determine the behavior of the sequence. If the magnitude of $z_{n}$ remains bounded (i.e., doesn't tend towards infinity) as the iterations continue indefinitely, the point is considered to be part of the Mandelbrot set. Otherwise, if the magnitude becomes unbounded, the point is not part of the set.

To generate the Julia fractal, both $z_{0}$ and c are specific values determined by the position on the complex plane. The initial value $z_{0}$ varies across the plane, while c remains fixed. Similar to the Mandelbrot set, points for which the sequence of $z_{n}$ values remain bounded are considered to be part of the Julia set.