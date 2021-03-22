//
// Created by user on 12/18/20.
//

#ifndef MANDELBROT_MANDELBROT_H
#define MANDELBROT_MANDELBROT_H
#include <stdlib.h>
#include <CL/cl.h>
#include "../colors/colors.h"
COLOR* get_mandelbrot_image(double center_re,double center_im,double magnification,int iteration_count);
#endif //MANDELBROT_MANDELBROT_H
