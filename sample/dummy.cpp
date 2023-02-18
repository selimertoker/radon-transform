// dummy program that reads an image and writes it as is
#include<iostream>
#include<fstream>
#include"ppm-lib.h"

int main(int argc,char** argv){
if(argc==1){std::cout<<"dummy program that reads an image and writes it as is\nusage: dummy infile outfile\n"; return 0;}
image img(1,256,255);
std::cout<<"reading "<<argv[1]<<"\n";
std::cout<<img.height<<'x'<<img.width<<'\n';
img.readfile(argv[1]);
int color[4];
for(int i=0;i<img.height*img.width;i++){
	img.getpxl(i,0,color);
	img.setpxl(i,0,color);
	}
std::cout<<"writing "<<argv[2]<<"\n";
img.savefile(argv[2]);
}
