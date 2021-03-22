#include "openCL_driver.h"
size_t read_kernel_file(char**output,const char*name)
{
	FILE*fp=fopen(name,"rb");
	if(!fp)
	{
		fprintf(stderr,"Fatal error: kernel file not found\n");
		exit(-1);
	}
	fseek(fp,0,SEEK_END);
	size_t size=ftell(fp);
	fseek(fp,0,SEEK_SET);
	*output=(char*)calloc(size,sizeof(char));
	if(!*output)
	{
		fclose(fp);
		fprintf(stderr,"Fatal error: Memory allocation failure in read_kernel_file\n");
		exit(-1);
	}
	fread(*output,size,1,fp);
	fclose(fp);
	return size;
}
void populate_complex_matrix(cl_double center_re,cl_double center_im,cl_double*re,cl_double*im,
							 size_t num_elem,size_t height,size_t width,cl_double magnification)
{
	for(int i=0;i<num_elem;i++)
	{
		int x=i%width;
		int y=i/width;
		re[i]=center_re-((int)width/2-x)*magnification/width;
		im[i]=center_im-((int)height/2-y)*magnification/width;
	}
}
//3 Inputs, 1 output
void run_kernel_3i_1o(size_t num_elems,void*in1,void*in2,void*in3,void*out,
					  size_t in1_size,size_t in2_size,size_t in3_size,size_t out_size,
					  char*kernel_path,char*kernel_name)
{
	cl_int err;
	cl_platform_id platform;
	err=clGetPlatformIDs(1,&platform,NULL);
	cl_device_id device;
	err=clGetDeviceIDs(platform,CL_DEVICE_TYPE_ALL,1,&device,NULL);
	const cl_context_properties prop[]={
			CL_CONTEXT_PLATFORM,(cl_context_properties)platform,
			0
	};
	cl_context ctx=clCreateContext(prop,1,&device,NULL,NULL,&err);

	char*program_file;
	size_t program_size=0;
	program_size=read_kernel_file(&program_file,kernel_path);

	cl_program program=clCreateProgramWithSource(ctx,1,(const char**)&program_file,
									  &program_size,&err);
	err=clBuildProgram(program,1,&device,NULL,NULL,NULL);
	free(program_file);

	cl_mem a=clCreateBuffer(ctx,CL_MEM_READ_ONLY,in1_size,NULL,&err);
	cl_mem b=clCreateBuffer(ctx,CL_MEM_READ_ONLY,in2_size,NULL,&err);
	cl_mem c=clCreateBuffer(ctx,CL_MEM_READ_ONLY,in3_size,NULL,&err);
	cl_mem z=clCreateBuffer(ctx,CL_MEM_WRITE_ONLY,out_size,NULL,&err);

	cl_command_queue queue=clCreateCommandQueue(ctx,device,0,NULL);
	cl_event wb_events[3];
	err=clEnqueueWriteBuffer(queue,a,CL_FALSE,0,in1_size,in1,0,
							 NULL,&wb_events[0]);
	err=clEnqueueWriteBuffer(queue,b,CL_FALSE,0,in2_size,in2,0,
							 NULL,&wb_events[1]);
	err=clEnqueueWriteBuffer(queue,c,CL_FALSE,0,in3_size,in3,0,
							 NULL,&wb_events[2]);

	cl_kernel kernel=clCreateKernel(program,kernel_name,&err);
	err=clSetKernelArg(kernel,0,sizeof(cl_mem),&z);
	err=clSetKernelArg(kernel,1,sizeof(cl_mem),&a);
	err=clSetKernelArg(kernel,2,sizeof(cl_mem),&b);
	err=clSetKernelArg(kernel,3,sizeof(cl_mem),&c);
	const size_t global_offset=0;
	cl_event kernel_event;
	err=clEnqueueNDRangeKernel(queue,kernel,1,&global_offset,
							   &num_elems,NULL,2,wb_events,
							   &kernel_event);
	err=clEnqueueReadBuffer(queue,z,CL_TRUE,0,out_size,out,1,
							&kernel_event,NULL);
	err=clFinish(queue);
	clReleaseMemObject(a);
	clReleaseMemObject(b);
	clReleaseMemObject(c);
	clReleaseMemObject(z);
	clReleaseKernel(kernel);
	clReleaseProgram(program);
	clReleaseCommandQueue(queue);
	clReleaseContext(ctx);
	clReleaseDevice(device);
}