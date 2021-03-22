# Mandelbrot Walker
## What does it do?
This piece of software allows you to zoom anywhere into the Mandelbrot set using the mouse buttons.
## Configuration
There are 2 config files: config and color_list.

### Config file format:

* window width
* window height
* starting point real coordinate
* starting point imaginary coordinate
* iteration count
* initial magnification (How many units on the real axis are visible on the screen when the program starts)
* zoom per click (The zoom percentage. 1 equals 100%)

### Color file format:

* n (The number of colors to be read from the file)
* color 1
* color 2
* ...
* color n

## External libraries
Compiling the source code requires the following libraries:

* SDL2
* OpenCL