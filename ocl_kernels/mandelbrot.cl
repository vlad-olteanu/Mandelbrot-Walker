__kernel void mandelbrot(__global int *out,
                      __global const double *in1,
                      __global const double *in2,
                      __global const int *in3
                      )
{
  int i = get_global_id(0);
  int max_iterations=in3[i];
  double re_C=in1[i],im_C=in2[i];
  double re_Z=0,im_Z=0;
  double re_new_Z,im_new_Z;
  int result=-1;
  for(int j=0;j<max_iterations;j++)
  {
    re_new_Z=re_Z*re_Z-im_Z*im_Z;
    im_new_Z=2*(re_Z*im_Z);
    re_new_Z+=re_C;
    im_new_Z+=im_C;
    if(re_new_Z*re_new_Z+im_new_Z*im_new_Z>4)
    {
        result=j;
        break;
    }
    re_Z=re_new_Z;
    im_Z=im_new_Z;
  }
  out[i]=result;
}