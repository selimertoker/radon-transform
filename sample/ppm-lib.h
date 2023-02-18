
int sizeint(int a){
	int i=1;
	while(a>=10){a/=10;i++;}
	return i;
}
class image {
	public:
		int* buf;
		int width; int height; int maxcolor;
		image(int x,int y,int c)
		{
			width=x+1; height=y+1; maxcolor=c;
			buf=(int*)malloc(height*width*3*sizeof(int));
		}
		void reset(){
			for(int i=0;i<(height)*(width)*3;i++){
				buf[i]=0;
			}
		}
		void getpxl(int x,int y,int* color)
		{
			if ((x<width) && (x>0) && (y<height) && (y>0))
			{
				color[0] = buf[3*(width*y+x)+0];
				color[1] = buf[3*(width*y+x)+1];
				color[2] = buf[3*(width*y+x)+2];
				color[3] = 0;
			}
			else{color[3]=1;}
		}
		void setpxl(int x,int y,int* color)
		{
			if ((x<width) && (x>=0) && (y<height) && (y>=0))
			{
				buf[3*(width*y+x)+0] = color[0];
				buf[3*(width*y+x)+1] = color[1];
				buf[3*(width*y+x)+2] = color[2];
				color[3] = 0;
			}
			else{color[3]=1;}
		}
		void readfile(char* fname)
		{
			std::ifstream fileh;
			fileh.open(fname,std::ios::binary|std::ios::in);
			if(fileh){
				char w;
				fileh.read(&w,1);
				if((char)w!='P'){std::cout<<"not a P6 file!\n";}
				fileh.read(&w,1);
				if((char)w!='6'){std::cout<<"not a P6 file!\n";}

				fileh.read(&w,1);
				int theint=0;
				while(1){
					fileh.read(&w,1);
					if((char)w==' '){width=theint;break;}
					theint=theint*10+(int)w-48;
				}
				theint=0;
				while(1){
					fileh.read(&w,1);
					if((char)w=='\n'){height=theint;break;}
					theint=theint*10+(int)w-48;
				}
				theint=0;
				while(1){
					fileh.read(&w,1);
					if((char)w=='\n'){maxcolor=theint;break;}
					theint=theint*10+(int)w-48;
				}
				free(buf);
				buf=(int*)malloc(height*width*3*sizeof(int));
				for(int i=0;i<width*height*3;i++)
				{
					fileh.read(&w, 1);
					if(w<0){buf[i]=(int)w+256;}
					else{buf[i]=(int)w;}
				}
			}
			else{std::cout<<"NO FILE\n";}

			fileh.close();
		}
		void savefile(char* fname)
		{
			std::ofstream fileh;
			fileh.open(fname,std::ios::binary|std::ios::out);
			fileh.write("P6",2);
			fileh.write("\n",1);

			for(int i=0;i<sizeint(width);i++){
				int theint=width;
				while(sizeint(theint)>(i+1)){theint/=10;}
				theint%=10;
				char ch=theint+48;
				fileh.write(&ch,1);}

			fileh.write(" ",1);

			for(int i=0;i<sizeint(height);i++){
				int theint=height;
				while(sizeint(theint)>(i+1)){theint/=10;}
				theint%=10;
				char ch=theint+48;
				fileh.write(&ch,1);}

			fileh.write("\n",1);

			for(int i=0;i<sizeint(maxcolor);i++){
				int theint=maxcolor;
				while(sizeint(theint)>(i+1)){theint/=10;}
				theint%=10;
				char ch=theint+48;
				fileh.write(&ch,1);}

			fileh.write("\n",1);

			for(int i=0;i<height*width*3;i++)
			{
				char ch;
				if(buf[i]>128){ch=buf[i]-256;}
				else{ch=buf[i];}
				fileh.write(&ch, 1);
			}
			fileh.write("\n",1);
			fileh.close();
		}
};
