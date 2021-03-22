#include "explorer.h"
#include <SDL2/SDL.h>
#include "config.h"
#include "colors/colors.h"
#include "mandelbrot/mandelbrot.h"

void recenter(double*center_re,double*center_im,double magnification,int mouse_x,int mouse_y)
{
	*center_re=*center_re+magnification/window_width*(mouse_x-window_width/2);
	*center_im=*center_im+magnification/window_width*(mouse_y-window_height/2);
}
void zoom_in(double*magnification,double percentage)
{
	*magnification*=1-percentage;
}
void zoom_out(double*magnification,double percentage)
{
	*magnification/=1-percentage;
}
void redraw(double center_re,double center_im,double magnification,
			int iteration_count,SDL_Renderer * renderer,SDL_Texture*texture)
{
	COLOR*mandelbrot=get_mandelbrot_image(center_re,center_im,magnification,iteration_count);
	SDL_UpdateTexture(texture, NULL, (unsigned int*)mandelbrot, window_width * sizeof(unsigned int));
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, texture, NULL, NULL);
	SDL_RenderPresent(renderer);
}
void explorer()
{
	if(SDL_Init(SDL_INIT_VIDEO))
	{
		fprintf(stderr,"Fatal error in explorer: Could not initialise SDL\n");
		exit(-1);
	}
	SDL_Event currentEvent;
	SDL_Window*window;
	SDL_Renderer * renderer;
	SDL_CreateWindowAndRenderer(window_width,window_height,0,&window,&renderer);
	SDL_Texture * texture = SDL_CreateTexture(
			renderer,SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_STATIC, window_width, window_height);
	if(!window||!renderer||!texture)
	{
		fprintf(stderr,"Fatal error in explorer: Could not initialise SDL\n");
		exit(-1);
	}
	double magnification=initial_magnification;
	double center_re=initial_center_re;
	double center_im=initial_center_im;
	redraw(center_re,center_im,magnification,iteration_count,renderer,texture);
	while(1)
	{
		SDL_WaitEvent(&currentEvent);
		if(currentEvent.type==SDL_QUIT)
		{
			break;
		}
		if(currentEvent.type==SDL_MOUSEBUTTONDOWN)
		{
			int mouse_x,mouse_y;
			SDL_GetMouseState(&mouse_x,&mouse_y);
			recenter(&center_re,&center_im,magnification,mouse_x,mouse_y);
			switch(currentEvent.button.button)
			{
				case SDL_BUTTON_LEFT:
					zoom_in(&magnification,zoom_per_click);
					break;
				case SDL_BUTTON_RIGHT:
					zoom_out(&magnification,zoom_per_click);
					break;
			}
			redraw(center_re,center_im,magnification,iteration_count,renderer,texture);
		}
	}
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
