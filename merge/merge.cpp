// image sequence adder, adds by arithmetic mean
#include <iostream>
#include<fstream>
#include "ppm-lib.h"

int main(int argc,char** argv){
	if(argc==1){
		std::cout<<"radon image merge program, merges by aarithmetic mean\nUsage: merge out_file in(min) in(max)\n";
		return 0;
	}
	image buf(512,512,255);
//	buf.reset();
	int radius=256;
	int color[3];
	int colour[3];
	int min=0;
	for(int i=0;i<4;i++){if((int)argv[2][i]==0){break;}min=(min*10)+((int)argv[2][i]-48);}
	int max=0;
	for(int i=0;i<4;i++){if((int)argv[3][i]==0){break;}max=(max*10)+((int)argv[3][i]-48);}
	int range=max-min;

	for(int i=min;i<=max;i++){
		std::cout<<i<<'\r';
		image img(2*radius,2*radius,255);
		char fname[7]={0,0,0,0,0,0,0};
		int j;
		for(j=0;j<sizeint(i);j++){int theint=i;while(sizeint(theint)>(j+1)){theint/=10;}fname[j]=theint%10+48;}
		fname[j++]='.';fname[j++]='p';fname[j++]='p';fname[j++]='m';
		img.readfile(fname);
		for(int y=0;y<buf.height;y++){
			for(int x=0;x<buf.width;x++){
				buf.getpxl(x,y,color);
				img.getpxl(x,y,colour);
				for(int i=0;i<3;i++){color[i]+=colour[i];}
				buf.setpxl(x,y,color);
			}
		}
		free(img.buf);
	}
	for(int y=0;y<buf.height;y++){
		for(int x=0;x<buf.width;x++){
			buf.getpxl(x,y,color);
			for(int i=0;i<3;i++){color[i]/=range;}
			buf.setpxl(x,y,color);
		}
		std::cout<<y<<"\r";
	}
	buf.savefile(argv[1]);
	return 0;
}
