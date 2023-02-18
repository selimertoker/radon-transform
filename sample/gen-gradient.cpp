// simple program that generates a colorful gradient image
#include<iostream>
#include<fstream>
#include "ppm-lib.h"

int main(int argc,char** argv){
	if (argc==1) {std::cout<<"simple program that generates a colorful 512x512 pixel gradient image\nusage: gen-gradient outfile\n";return 0;}
	image img(512,512,255);
	for(int y=0;y<512;y++)
	{
		for(int x=0;x<512;x++)
		{
			int color[4]={x/2,128,y/2,0};
			img.setpxl(x,y,color);
		}
	}
	img.savefile(argv[1]);
	return 0;
}

