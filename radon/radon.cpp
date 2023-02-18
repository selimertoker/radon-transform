
#include<iostream>
#include<fstream>
#include<math.h>
#include "ppm-lib.h"

bool generate_degree_images;


int main(int argc,char** argv){

	if(argc<3){std::cout<<"radon ray sender program\nUsage: Radon in_file radon_file <degree_min> <degree_max>\nif no degree given, 0-360 is calculated and the radon sinogram is generated but individual files are not generated\n";return 0;}
	int radius = 256;
	int min = 0;
	int max = 360;

	image radon_image(360,512,255); //radon transform image
	image reference_image(0,0,0); //referance image

	reference_image.readfile(argv[1]);
	radon_image.readfile(argv[2]);

	if (argc>=5){
		max = 0;
		for(int i=0;i<4;i++){if((int)argv[3][i]==0){break;} min=(min*10)+((int)argv[3][i]-48);} //read option min degree (char* to int)
		for(int i=0;i<4;i++){if((int)argv[4][i]==0){break;} max=(max*10)+((int)argv[4][i]-48);} //read option max degree (char* to int)
		if((max<min)||(max<0)||(max>360)||(min<0)||(min>360)){std::cout<<"ANGLE WRONG\n"; return 1;}
		generate_degree_images = true;
	}//will create many image files

	else {generate_degree_images = false;}//wont create many image files

	for(int degree=min;degree<=max;degree++){

		char fname[7];
		std::cerr<<degree<<"\r";
		if (generate_degree_images){
			int i=0;
			for(i=0;i<sizeint(degree);i++){int j=degree; while(sizeint(j)>(i+1)){j/=10;} fname[i]=j%10+48;} // generate filename
			fname[i++]='.';fname[i++]='p';fname[i++]='p';fname[i++]='m';
		}

		image degree_image(2*radius,2*radius,255);
		degree_image.reset();

		float sin=std::sin(degree*M_PI/180);
		float cos=std::cos(degree*M_PI/180);
		int cord[2];
		int color[3];
		int colour[4];

		for(int rof=-radius;rof<radius;rof++){
			int pxlonline=1;
			for(int rac=-radius;rac<radius;rac++){
				cord[0]=(int)(radius-(rac*sin+rof*cos));
				cord[1]=(int)((rac*cos-rof*sin)+radius);
				reference_image.getpxl(cord[0],cord[1],colour);
				if (colour[3]!=1){
					for (int i=0;i<3;i++){color[i]+=colour[i];}//sum of colors in a line
					pxlonline++;
				}
			}
			for (int i=0;i<3;i++){color[i]/=pxlonline;}//average color in the line

			radon_image.setpxl(degree,rof+radius,color);//put the average color in the radon sinogram

			if (generate_degree_images){//apply the average color on the whole line in the degree images
				for(int rac=-radius;rac<radius;rac++){
					cord[0]=(int)(radius-(rac*sin+rof*cos));
					cord[1]=(int)((rac*cos-rof*sin)+radius);
					degree_image.setpxl(cord[0],cord[1],color);
				}
			}
		}

		if (generate_degree_images){//save and cleanup
			degree_image.savefile(fname);
			free(degree_image.buf);
		}
	}

	radon_image.savefile(argv[2]);
	return 0;
}

