#include "colors.h"
#include <stdlib.h>
#include <stdio.h>
COLOR* gradient=0;
int color_num;
//colors between two primary colors
const int intermediary_color_num=200;
COLOR* read_colors_from_file(int*color_num)
{
	FILE*f=fopen("./color_list","r");
	if(!f)
	{
		fprintf(stderr,"Fatal error: could not open colors file\n");
		exit(-1);
	}
	int n;
	fscanf(f,"%d",&n);
	COLOR* colors=(COLOR*)calloc(n,sizeof(COLOR));
	for(int i=0;i<n;i++)
	{
		int hex_code;
		if(!fscanf(f,"%X",&hex_code))
		{
			fprintf(stderr,"Fatal error: reached colors file EOF too soon\n");
			exit(-1);
		}
		colors[i].r=(hex_code&0xFF0000)>>16;
		colors[i].g=(hex_code&0xFF00)>>8;
		colors[i].b=hex_code&0xFF;
	}
	*color_num=n;
	return colors;
}
void build_gradient(COLOR*colors,int start,int finish)
{
	if(finish-start<2)
	{
		return;
	}
	int mid=finish-(finish-start)/2;
	colors[mid].r=colors[start].r/2.0+colors[finish].r/2.0;
	colors[mid].g=colors[start].g/2.0+colors[finish].g/2.0;
	colors[mid].b=colors[start].b/2.0+colors[finish].b/2.0;
	build_gradient(colors,start,mid);
	build_gradient(colors,mid,finish);
}
COLOR* get_color_gradient(int*n)
{
	int primary_colors_num;
	COLOR* primary_colors=read_colors_from_file(&primary_colors_num);
	int color_num=primary_colors_num*(intermediary_color_num+1)+1;
	COLOR* colors=(COLOR*)calloc(color_num,sizeof(COLOR));
	if(!colors)
	{
		fprintf(stderr,"Fatal error: Memory allocation failure in get_color_gradient\n");
		exit(-1);
	}
	for(int i=0;i<primary_colors_num;i++)
	{
		colors[i*(intermediary_color_num+1)]=primary_colors[i];
	}
	colors[primary_colors_num-1]=primary_colors[0];
	for(int i=0;i<primary_colors_num;i++)
	{
		build_gradient(colors,i*(intermediary_color_num+1),(i+1)*(intermediary_color_num+1));
	}
	*n=color_num;
	return colors;
}
void get_color(COLOR*color,int escape_time)
{
	if(escape_time<4)
	{
		color->uint=0;
	}
	else
	{
		if(!gradient)
		{
			gradient=get_color_gradient(&color_num);
		}
		*color=gradient[escape_time%color_num];
	}
}