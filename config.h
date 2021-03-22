//
// Created by user on 3/10/21.
//

#ifndef MANDELBROT_CONFIG_H
#define MANDELBROT_CONFIG_H
#include <CL/cl.h>
int window_width;
int window_height;
cl_double initial_center_re;
cl_double initial_center_im;
int iteration_count;
cl_double initial_magnification;
cl_double zoom_per_click;
#endif //MANDELBROT_CONFIG_H
