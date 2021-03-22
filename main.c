#include <stdio.h>
#include <stdlib.h>
#include <CL/cl.h>
#include "config.h"
#include "explorer.h"

void read_config_file()
{
	FILE*f=fopen("./config","r");
	if(!f)
	{
		fprintf(stderr,"Fatal error in read_config_file: Config file not found.\n");
		exit(-1);
	}
	if(fscanf(f,"%d %d %lf %lf %d %lf %lf",
			  &window_width,&window_height,&initial_center_re,&initial_center_im,
			  &iteration_count,&initial_magnification,&zoom_per_click)!=7)
	{
		fprintf(stderr,"Fatal error in read_config_file: Invalid config file contents\n");
		exit(-1);
	}
}

int main()
{
	if(sizeof(double)!=sizeof(cl_double))
	{
		fprintf(stderr,"Fatal error: double size mismatch, can't run on this machine.\n");
	}
	if(sizeof(int)!=sizeof(cl_int))
	{
		fprintf(stderr,"Fatal error: int size mismatch, can't run on this machine.\n");
	}
	read_config_file();
	explorer();

}