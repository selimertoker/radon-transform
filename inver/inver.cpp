
#include<iostream>
#include<fstream>
#include<math.h>
#include "ppm-lib.h"

bool debug = 0;

int main(int argc,char** argv){

	if(argc==1){std::cout<<"inverse radon transform program\nUsage: inver in_radon_file out_file\n";return 0;}

	int color[3];
	int color_sinogram[3];
	int cord[2];
	int rad = 256;

	image radimg(180,2*rad,255);
	image outimg(2*rad,2*rad,255);
	radimg.readfile(argv[1]);
	outimg.reset();

	int count_buf[2*rad*2*rad*3];
	for (int i=0;i<2*rad*2*rad*3;i++){count_buf[i]=0;}

	for (int degree=0; degree<180; degree++){
		std::cerr<<degree<<"\r";
		double sin=std::sin(degree*M_PI/180);
		double cos=std::cos(degree*M_PI/180);
		for (int rac=-rad; rac<rad; rac++){
			radimg.getpxl(degree,rac+rad,color_sinogram);
			for (int rof=-rad; rof<rad; rof++){
				cord[0]=(int)(rad-(rac*cos+rof*sin));
				cord[1]=(int)(rad-(rac*sin-rof*cos));
				if((cord[0]<0) || (cord[0]>=2*rad) || (cord[1]<0) || (cord[1]>=2*rad)){continue;}
				outimg.getpxl(cord[0],cord[1],color);
				for(int i=0;i<3;i++){color[i]+=color_sinogram[i];}
				outimg.setpxl(cord[0],cord[1],color);
				for(int i=0;i<3;i++){count_buf[3*(2*rad*cord[1]+cord[0])+i]++;}

				if (debug) {std::cerr<<"degree:"<<degree<<" rac:"<<rac<<" rof:"<<rof<<" cord0:"<<cord[0]<<" cord1:"<<cord[1]<<" c0:"<<color[0]<<" c1:"<<color[1]<<" c2:"<<color[2]<<"\n";}
			}
		}
	}

	for (int y=0;y<2*rad;y++){
		for (int x=0;x<2*rad;x++){
			outimg.getpxl(x,y,color);
			for(int i=0;i<3;i++){if(count_buf[3*(2*rad*y+x)+i]==0){count_buf[3*(2*rad*y+x)+i]=1;}}
			for(int i=0;i<3;i++){color[i] = (int)((float)color[i] / count_buf[3*(2*rad*y+x)+i]);}
			outimg.setpxl(x,y,color);
		}
	}

	outimg.savefile(argv[2]);
	return 0;
}

