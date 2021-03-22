#include <string.h>
#include "mandelbrot.h"
#include "openCL_driver/openCL_driver.h"
#include "colors/colors.h"
#include "config.h"

int get_escape_times(double*re,double*im,int*escape_time,const size_t num_elem,int*it_count_v)
{
	run_kernel_3i_1o(num_elem,re,im,it_count_v,escape_time,
					 num_elem*sizeof(double),num_elem*sizeof(double),
					 num_elem*sizeof(int),num_elem*sizeof(int),
					 "./ocl_kernels/mandelbrot.cl","mandelbrot");
}
COLOR* get_mandelbrot_image(double center_re,double center_im,double magnification,int iteration_count)
{
	size_t n=window_height*window_width;

	double*re=(double*)calloc(n,sizeof(double));
	double*im=(double*)calloc(n,sizeof(double));
	int*it_count_v=(int*)calloc(n,sizeof(int));
	int*escape_time=(int*)calloc(n,sizeof(int));
	COLOR*image=(COLOR*)calloc(n,sizeof(COLOR));

	if(!re||!im||!escape_time||!it_count_v||!image)
	{
		fprintf(stderr,"Fatal error: Memory allocation failure in get_mandelbrot_image\n");
		exit(-1);
	}
	populate_complex_matrix(center_re,center_im,re,im,n,window_height,window_width,magnification);
	for(int i=0;i<n;i++)
	{
		it_count_v[i]=iteration_count;
	}
	get_escape_times(re,im,escape_time,n,it_count_v);
	for(int i=0;i<n;i++)
	{
		get_color(image+i,escape_time[i]);
	}
	free(re);
	free(im);
	free(escape_time);
	return image;
}