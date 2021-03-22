//
// Created by user on 12/18/20.
//

#ifndef MANDELBROT_OPENCL_DRIVER_H
#define MANDELBROT_OPENCL_DRIVER_H
#include <CL/cl.h>
#include <stdio.h>
#include <stdlib.h>
void run_kernel_3i_1o(size_t num_elems,void*in1,void*in2,void*in3,void*out,
					  size_t in1_size,size_t in2_size,size_t in3_size,size_t out_size,
					  char*kernel_path,char*kernel_name);
void populate_complex_matrix(double center_re,double center_im,double*re,double*im,
							 size_t num_elem,size_t height,size_t width,double magnification);
#endif //MANDELBROT_OPENCL_DRIVER_H
