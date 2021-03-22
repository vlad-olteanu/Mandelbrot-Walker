#ifndef MANDELBROT_COLORS_H
#define MANDELBROT_COLORS_H
typedef union _COLOR
{
	unsigned int uint;
	struct
	{
		unsigned char b,g,r;
	};
}COLOR;
void get_color(COLOR*color,int escape_time);
#endif //MANDELBROT_COLORS_H
