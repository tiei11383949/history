#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#define BITMAPFILEHEADERLENGTH 14   // 24bit文件头长度为14
#define BM 19778                    // BM的ASCII码为19778，BM为位图的标识符

using namespace std;
unsigned int OffSet=0;    // 从标题部分到数据部分的偏移量
long width ;          // 宽的像素值
long height ;         // 高的像素值
unsigned char gray[5000][5000];
unsigned char r[5000][5000];
unsigned char g[5000][5000];
unsigned char b[5000][5000];
unsigned char x[5000][5000];
unsigned char y[5000][5000];
unsigned char z[5000][5000];
unsigned char u[5000][5000];
unsigned char v[5000][5000];
unsigned char w[5000][5000];

void bmpFileTest(FILE* fpbmp)//头到数据部分的偏移量
{
    unsigned short bfType = 0;
    fseek(fpbmp, 0L, SEEK_SET);// 定义从文件开始处
    fread(&bfType, sizeof(char), 2, fpbmp);//把2个char大小的字符拷贝进bftyoe的地址处
    if (BM != bfType)//判断图片信息的前两个字节是否是位图文件的标识符
    {
        printf("not bmp\n");
        exit(1);
    }
}
void bmpLength(FILE* fpbmp)//获取bmp图像的高和宽
{
    fseek(fpbmp, 10L, SEEK_SET);//定位至文件中的第10个字节 ，第10~13字节为位图数据位置的偏移地址
    fread(&OffSet, sizeof(char), 4, fpbmp);//读取fpbmp文件中的4个字节放入offset中
    printf("The Header Part is of length %d.\n", OffSet);
}
void BmpWidthHeight(FILE* fpbmp) //获取rgb的数据
{
    fseek(fpbmp, 18L, SEEK_SET);//定位至文件的第18个字节，第18~21字节记录位图的宽度
    fread(&width, sizeof(char), 4, fpbmp);//将位图四个字节存储至width中
    fseek(fpbmp, 22L, SEEK_SET);//定位至文件的第22个字节，第22~25字节记录位图的高度
    fread(&height, sizeof(char), 4, fpbmp);
}

void bmpDataPart(FILE* fpbmp)
{
    int i, j=0;
    int stride;
    unsigned char* pix=NULL;
    fseek(fpbmp, OffSet, SEEK_SET);//定义至文件的偏移地址处
    stride=(24*width+31)/8;
    stride=stride/4*4;//若像素的水平线的字节数不是4的倍数则补位4的倍数
    pix=(unsigned char*)malloc(stride);//开辟stride的内存空间
    for(j=0;j<height;j++)
    {
        fread(pix, 1, stride, fpbmp);//每次读一个字节，共读stride次，从fpbmp中取出放入pix中
        for(i=0;i<width;i++)
        {
            r[height-1-j][i]=pix[i*3+2];
            g[height-1-j][i]=pix[i*3+1];
            b[height-1-j][i]=pix[i*3];
        }
    }
}
void bmpDataPartQuarter(FILE* fpbmp)
{
    int i, j=0;
    int stride;
    unsigned char* pix=NULL;
    fseek(fpbmp, OffSet, SEEK_SET);//定义至文件的偏移地址处
    stride=(24*width+31)/8;
    stride=stride/4*4;//若像素的水平线的字节数不是4的倍数则补位4的倍数
    pix=(unsigned char*)malloc(stride);//开辟stride的内存空间
    for(j=0;j<height;j++)
    {
        fread(pix, 1, stride, fpbmp);//每次读一个字节，共读stride次，从fpbmp中取出放入pix中
        for(i=0;i<width;i++)
        {
            r[height-1-j][i]=pix[i*3+2];
            g[height-1-j][i]=pix[i*3+1];
            b[height-1-j][i]=pix[i*3];
        }
    }
    for(j=height/2;j<height;j++)
    {
        for(i=0;i<width/2;i++)
        {
            r[height-1-j][i]=0;
            g[height-1-j][i]=0;
            b[height-1-j][i]=255;
        }
    }
}
void bmpDataPartQuarterHi(FILE* fpbmp)
{
    int i, j=0;
    int stride;
    unsigned char* pix=NULL;
    fseek(fpbmp, OffSet, SEEK_SET);//定义至文件的偏移地址处
    stride=(24*width+31)/8;
    stride=stride/4*4;//若像素的水平线的字节数不是4的倍数则补位4的倍数
    pix=(unsigned char*)malloc(stride);//开辟stride的内存空间
    for(j=0;j<height;j++)
    {
        fread(pix, 1, stride, fpbmp);//每次读一个字节，共读stride次，从fpbmp中取出放入pix中
        for(i=0;i<width;i++)
        {
            r[height-1-j][i]=pix[i*3+2];
            g[height-1-j][i]=pix[i*3+1];
            b[height-1-j][i]=pix[i*3];
        }
    }
    for(j=height/2;j<height;j++)
    {
        for(i=0;i<width/2;i++)
        {
            r[height-1-j][i]=0;
            g[height-1-j][i]=0;
            b[height-1-j][i]=255;
        }
    }
    for(j=0;j<400;j++)
    {
        for(i=0;i<80;i++)
        {
            r[height-1-j][i]=0;
            g[height-1-j][i]=255;
            b[height-1-j][i]=0;
        }
		for(i=300;i<380;i++)
        {
            r[height-1-j][i]=0;
            g[height-1-j][i]=255;
            b[height-1-j][i]=0;
        }
		for(i=440;i<520;i++)
        {
            r[height-1-j][i]=0;
            g[height-1-j][i]=255;
            b[height-1-j][i]=0;
        }
    }
    for(i=700;i<780;i++)
    {
        for(j=0;j<80;j++)
        {
            r[height-1-j][i]=0;
            g[height-1-j][i]=255;
            b[height-1-j][i]=0;
        }
        for(j=150;j<400;j++)
        {
            r[height-1-j][i]=0;
            g[height-1-j][i]=255;
            b[height-1-j][i]=0;
        }
    }
    for(j=160;j<240;j++)
    {
        for(i=0;i<380;i++)
        {
            r[height-1-j][i]=0;
            g[height-1-j][i]=255;
            b[height-1-j][i]=0;
        }
    }
}
void bmpDataPartGray(FILE* fpbmp)
{
    int i, j=0;
    int stride;
    unsigned char* pix=NULL;
    fseek(fpbmp, OffSet, SEEK_SET);//定义至文件的偏移地址处
    stride=(24*width+31)/8;
    stride=stride/4*4;//若像素的水平线的字节数不是4的倍数则补位4的倍数
    pix=(unsigned char*)malloc(stride);//开辟stride的内存空间
    for(j=0;j<height;j++)
    {
        fread(pix, 1, stride, fpbmp);//每次读一个字节，共读stride次，从fpbmp中取出放入pix中
        for(i=0;i<width;i++)
        {
            x[height-1-j][i]=pix[i*3+2];
            y[height-1-j][i]=pix[i*3+1];
            z[height-1-j][i]=pix[i*3];
            gray[height-1-j][i]=(x[height-1-j][i]+y[height-1-j][i]+z[height-1-j][i])/3;
            r[height-1-j][i]=gray[height-1-j][i];
            g[height-1-j][i]=gray[height-1-j][i];
            b[height-1-j][i]=gray[height-1-j][i];
        }
    }
}
void bmpDataPartBin(FILE* fpbmp,int div)
{
    int i, j=0;
    int stride;
    unsigned char* pix=NULL;
    fseek(fpbmp, OffSet, SEEK_SET);
    stride=(24*width+31)/8;
    stride=stride/4*4;
    pix=(unsigned char*)malloc(stride);
    for(j=0;j<height;j++)
    {
        fread(pix, 1, stride, fpbmp);
        for(i=0;i<width;i++)
        {
            x[height-1-j][i]=pix[i*3+2];
            y[height-1-j][i]=pix[i*3+1];
            z[height-1-j][i]=pix[i*3];
            gray[height-1-j][i]=(x[height-1-j][i]+y[height-1-j][i]+z[height-1-j][i])/3;
            r[height-1-j][i]=gray[height-1-j][i]/div*255;
            g[height-1-j][i]=gray[height-1-j][i]/div*255;
            b[height-1-j][i]=gray[height-1-j][i]/div*255;
        }
    }
}
void bmpDataPartBinOtsu(FILE* fpbmp)
{
    int i, j=0;
    int stride;
    int n0=0,n1=0; //阈值上下个数 
	float w0=0,w1=0; // 阈值上下比例 
    float u0=0,u1=0;//阈值上下灰度平均值 
    int div,div0=0;//阈值
	float giv,g0=0;//类间方差 
	
    unsigned char* pix=NULL;
    fseek(fpbmp, OffSet, SEEK_SET);
    stride=(24*width+31)/8;
    stride=stride/4*4;
    pix=(unsigned char*)malloc(stride);
    for(j=0;j<height;j++)
    {
        fread(pix, 1, stride, fpbmp);
        for(i=0;i<width;i++)
        {
            x[height-1-j][i]=pix[i*3+2];
            y[height-1-j][i]=pix[i*3+1];
            z[height-1-j][i]=pix[i*3];
            gray[height-1-j][i]=(x[height-1-j][i]+y[height-1-j][i]+z[height-1-j][i])/3;
        }
    }

    for(div=0;div<256;div++)
    {
    	for(j=0;j<height;j++)
        {
		     for(i=0;i<width;i++)
             {
			      if(gray[height-1-j][i]<div)
				  {
				  	 n0++;
				  	 u0=u0+gray[height-1-j][i];
				  }  
			      if(gray[height-1-j][i]>=div)
				  {
				     n1++;
				     u1=u1+gray[height-1-j][i];
				  } 
             }
        }
        w0=(float)n0/(height*width);
        w1=(float)n1/(height*width);
        u0=(float)u0/(height*width);
        u1=(float)u1/(height*width);
        giv=(float)w0*(float)w1*(float)(u0-u1)*(u0-u1);
        if(giv>g0)
        {
        	g0=giv;
        	div0=div;
		}
		printf("div=%d n0=%d n1=%d w0=%f w1=%f u0=%f u1=%f giv=%f\n",div,n0,n1,w0,w1,u0,u1,giv);
        giv=u0=u1=w0=w1=n0=n1=0;
	}
	printf("RESULT:div0=%d g0=%f",div0,g0);
	for(j=0;j<height;j++)
    {
        for(i=0;i<width;i++)
        {
            r[height-1-j][i]=gray[height-1-j][i]/div0*255;
            g[height-1-j][i]=gray[height-1-j][i]/div0*255;
            b[height-1-j][i]=gray[height-1-j][i]/div0*255;
        }
    }
}

void bmpoutput(FILE* fpout)
{
    int i, j=0;
    int stride;
    unsigned char* pixout=NULL;
    stride=(24*width+31)/8;
    stride=stride/4*4;
    pixout=(unsigned char*)malloc(stride);
    fseek(fpout, OffSet, SEEK_SET);
    for(j=0;j<height;j++)
    {
        for(i=0;i<width;i++)
        {
            pixout[i*3+2]=r[height-1-j][i];//将rgb的像素值给pixout用于输出图像
            pixout[i*3+1]=g[height-1-j][i];
            pixout[i*3]=b[height-1-j][i];
        }
        fwrite(pixout, 1, stride, fpout);//将pixout中的像素以每次一个字节，共stride次写入fpout中
    }
}
void bmpoutputAverageFilter(FILE* fpout) 
{
    int i, j=0;
    int stride;
    unsigned char* pixout=NULL;
    stride=(24*width+31)/8;
    stride=stride/4*4;
    pixout=(unsigned char*)malloc(stride);
    fseek(fpout, OffSet, SEEK_SET);
    for(j=0;j<height;j++)
    {
        for(i=0;i<width;i++)
        {   
            x[height-1-j][i]=(r[height-2-j][i-1]+r[height-2-j][i]+r[height-2-j][i+1]+r[height-1-j][i-1]+r[height-1-j][i]+r[height-1-j][i+1]+r[height-j][i-1]+r[height-j][i]+r[height-j][i+1])/9;
            y[height-1-j][i]=(g[height-2-j][i-1]+g[height-2-j][i]+g[height-2-j][i+1]+g[height-1-j][i-1]+g[height-1-j][i]+g[height-1-j][i+1]+g[height-j][i-1]+g[height-j][i]+g[height-j][i+1])/9;
            z[height-1-j][i]=(b[height-2-j][i-1]+b[height-2-j][i]+b[height-2-j][i+1]+b[height-1-j][i-1]+b[height-1-j][i]+b[height-1-j][i+1]+b[height-j][i-1]+b[height-j][i]+b[height-j][i+1])/9;
            pixout[i*3+2]=x[height-1-j][i];
            pixout[i*3+1]=y[height-1-j][i];
            pixout[i*3]=z[height-1-j][i];
        }
        fwrite(pixout, 1, stride, fpout);
    }
}
void bmpoutputGaussianFilter(FILE* fpout) 
{
    int i, j=0;
    int stride;
    unsigned char* pixout=NULL;
    stride=(24*width+31)/8;
    stride=stride/4*4;
    pixout=(unsigned char*)malloc(stride);
    fseek(fpout, OffSet, SEEK_SET);
    for(j=0;j<height;j++)
    {
        for(i=0;i<width;i++)
        {   
            x[height-1-j][i]=0.0947416*r[height-2-j][i-1]+0.118318*r[height-2-j][i]+0.0947416*r[height-2-j][i+1]+0.118318*r[height-1-j][i-1]+0.147761*r[height-1-j][i]+0.118318*r[height-1-j][i+1]+0.0947416*r[height-j][i-1]+0.118318*r[height-j][i]+0.0947416*r[height-j][i+1];
            y[height-1-j][i]=0.0947416*g[height-2-j][i-1]+0.118318*g[height-2-j][i]+0.0947416*g[height-2-j][i+1]+0.118318*g[height-1-j][i-1]+0.147761*g[height-1-j][i]+0.118318*g[height-1-j][i+1]+0.0947416*g[height-j][i-1]+0.118318*g[height-j][i]+0.0947416*g[height-j][i+1];
            z[height-1-j][i]=0.0947416*b[height-2-j][i-1]+0.118318*b[height-2-j][i]+0.0947416*b[height-2-j][i+1]+0.118318*b[height-1-j][i-1]+0.147761*b[height-1-j][i]+0.118318*b[height-1-j][i+1]+0.0947416*b[height-j][i-1]+0.118318*b[height-j][i]+0.0947416*b[height-j][i+1];
            pixout[i*3+2]=x[height-1-j][i];
            pixout[i*3+1]=y[height-1-j][i];
            pixout[i*3]=z[height-1-j][i];
        }
        fwrite(pixout, 1, stride, fpout);
    }
}
void bmpoutputEdgeDetectionScharr(FILE* fpout)
{
    int i, j=0;
    int stride;
    unsigned char* pixout=NULL;
    stride=(24*width+31)/8;
    stride=stride/4*4;
    pixout=(unsigned char*)malloc(stride);
    fseek(fpout, OffSet, SEEK_SET);
    for(j=0;j<height;j++)
    {
        for(i=0;i<width;i++)
        {   
            u[height-1-j][i]=-3*r[height-2-j][i-1]-10*r[height-2-j][i]-3*r[height-2-j][i+1]+3*r[height-j][i-1]+10*r[height-j][i]+3*r[height-j][i+1];
            v[height-1-j][i]=-3*g[height-2-j][i-1]-10*g[height-2-j][i]-3*g[height-2-j][i+1]+3*g[height-j][i-1]+10*g[height-j][i]+3*g[height-j][i+1];
            w[height-1-j][i]=-3*b[height-2-j][i-1]-10*b[height-2-j][i]-3*b[height-2-j][i+1]+3*b[height-j][i-1]+10*b[height-j][i]+3*b[height-j][i+1];
            
			x[height-1-j][i]=-3*r[height-2-j][i-1]+3*r[height-2-j][i+1]-10*r[height-1-j][i-1]+10*r[height-1-j][i+1]-3*r[height-j][i-1]+3*r[height-j][i+1];
            y[height-1-j][i]=-3*g[height-2-j][i-1]+3*g[height-2-j][i+1]-10*g[height-1-j][i-1]+10*g[height-1-j][i+1]-3*g[height-j][i-1]+3*g[height-j][i+1];
            z[height-1-j][i]=-3*b[height-2-j][i-1]+3*b[height-2-j][i+1]-10*b[height-1-j][i-1]+10*b[height-1-j][i+1]-3*b[height-j][i-1]+3*b[height-j][i+1];
			
			pixout[i*3+2]=(x[height-1-j][i]+u[height-1-j][i])/2;
            pixout[i*3+1]=(y[height-1-j][i]+v[height-1-j][i])/2;
            pixout[i*3]=(z[height-1-j][i]+w[height-1-j][i])/2;
        }
        fwrite(pixout, 1, stride, fpout);
    }
}
void bmpoutputEdgeDetectionSobel(FILE* fpout)
{
    int i, j=0;
    int stride;
    unsigned char* pixout=NULL;
    stride=(24*width+31)/8;
    stride=stride/4*4;
    pixout=(unsigned char*)malloc(stride);
    fseek(fpout, OffSet, SEEK_SET);
    for(j=0;j<height;j++)
    {
        for(i=0;i<width;i++)
        {   
            u[height-1-j][i]=-1*r[height-2-j][i-1]-2*r[height-2-j][i]-1*r[height-2-j][i+1]+1*r[height-j][i-1]+2*r[height-j][i]+1*r[height-j][i+1];
            v[height-1-j][i]=-1*g[height-2-j][i-1]-2*g[height-2-j][i]-1*g[height-2-j][i+1]+1*g[height-j][i-1]+2*g[height-j][i]+1*g[height-j][i+1];
            w[height-1-j][i]=-1*b[height-2-j][i-1]-2*b[height-2-j][i]-1*b[height-2-j][i+1]+1*b[height-j][i-1]+2*b[height-j][i]+1*b[height-j][i+1];
            
			x[height-1-j][i]=-1*r[height-2-j][i-1]+1*r[height-2-j][i+1]-2*r[height-1-j][i-1]+2*r[height-1-j][i+1]-1*r[height-j][i-1]+1*r[height-j][i+1];
            y[height-1-j][i]=-1*g[height-2-j][i-1]+1*g[height-2-j][i+1]-2*g[height-1-j][i-1]+2*g[height-1-j][i+1]-1*g[height-j][i-1]+1*g[height-j][i+1];
            z[height-1-j][i]=-1*b[height-2-j][i-1]+1*b[height-2-j][i+1]-2*b[height-1-j][i-1]+2*b[height-1-j][i+1]-1*b[height-j][i-1]+1*b[height-j][i+1];
			
			pixout[i*3+2]=sqrt(x[height-1-j][i]*x[height-1-j][i]+u[height-1-j][i]*u[height-1-j][i]);
            pixout[i*3+1]=sqrt(y[height-1-j][i]*y[height-1-j][i]+v[height-1-j][i]*v[height-1-j][i]);
            pixout[i*3]=sqrt(z[height-1-j][i]*z[height-1-j][i]+w[height-1-j][i]*w[height-1-j][i]);
        }
        fwrite(pixout, 1, stride, fpout);
    }
}
void bmpoutputCode(FILE* fpout)//resoure:t-x-m.com etc
{
    int i=0,j=0,k=0,l=0;//count for
    int m0=0,m1=0,n0,n1,line[5000];//one line's result 
    int start=0,dot;//one dot's length
    int trigger[5000];//detect up and down
    int more[5000],less[5000];//check where is less or more
    int simp[95];//simplfied
    int EAN13[3][10]={   1101,  11001,  10011, 111101, 100011, 110001, 101111, 111011, 110111,   1011,
	                   100111, 110011,  11011, 100001,  11101, 111001,    101,  10001,   1001,  10111,
					  1110010,1100110,1101100,1000010,1011100,1001110,1010000,1000100,1001000,1110100};//decode
    int odd[10]={0,1011,1101,1110,10011,11001,11100,10101,10110,11010};//decode
    int final[13];//final result
    
	//Binarization
    for(j=0;j<height;j++)
    {
        for(i=0;i<width;i++)
        {
            gray[height-1-j][i]=(r[height-1-j][i]+g[height-1-j][i]+b[height-1-j][i])/3;
            gray[height-1-j][i]=1-gray[height-1-j][i]/128;
        }
    }
    //group line after counting
	for(i=0;i<width;i++)
    {
        for(j=0;j<height;j++)
        {
            if(gray[height-1-j][i]==0) m0++;
            if(gray[height-1-j][i]==1) m1++;
        }
        if(m1>=m0) line[i]=1;
        if(m1<m0) line[i]=0;
        m1=m0=0;
    }
    //count the length of one dot
	i=0;  
	while(line[i]!=1) i++;
	start=i;
	while(line[i]!=0) i++;
	dot=i-start;
	//detect up and down
    j=0;
	for(i=0;i<width;i++)
    {
       if(line[i]!=line[i+1]) 
       {
       	trigger[j]=i;
       	j++;
	   }
    }
	printf("\nTRIGGER:");
	for(i=0;trigger[i]!=0;i++)
        printf("%d ",trigger[i]);
    //check where is less or more
	j=k=0;
	for(i=0;i<width;i++)
    {
        if((trigger[i+1]-trigger[i])%dot==dot-1)
        {
        	less[j]=trigger[i];
        	j++;
		}
        if((trigger[i+1]-trigger[i])%dot==1)
        {
        	more[k]=trigger[i];
        	k++;
		}
    }
    printf("\nMORE:");
	for(i=0;more[i]!=0;i++)
        printf("%d ",more[i]);
    printf("\nLESS:");
	for(i=0;less[i]!=0;i++)
        printf("%d ",less[i]);
    //repairing
   for(i=width;i>=0;i--)
    {
        for(j=0;more[j]!=0;j++)
        {
        	if(i==more[j])
        	{
        		for(l=i+1;l<width;l++) line[l]=line[l+1];
			}
		}
        for(k=0;less[k]!=0;k++)
        {
        	if(i==less[k])
        	{
        		for(l=width;l>i+1;l--)  line[l+1]=line[l];
                line[i+1]=line[i+2];
			}
		}
    }
    //recheck
    j=0;
	for(i=0;i<width;i++)
    {
       if(line[i]!=line[i+1]) 
       {
       	trigger[j]=i;
       	j++;
	   }
    }
	printf("\nRECHECK:");
	for(i=0;trigger[i]!=0;i++)
        printf("%d ",trigger[i]);
    //simplfied
    j=0;
    for(i=start;i<width;i=i+dot)
    {
       simp[j]=line[i];
       j++;
    }
    printf("\nSIMPLFIED:");
	for(i=0;i<95;i++)
       printf("%d ",simp[i]);
    //decode
    k=1;
	for(i=3;i<45;i=i+7)
    {
    	for(j=0;j<7;j++)
    		final[k]=10*final[k]+simp[i+j];
    	k++;
	}
	for(i=50;i<92;i=i+7)
    {
    	for(j=0;j<7;j++)
    		final[k]=10*final[k]+simp[i+j];
    	k++;
	}
	for(k=1;k<13;k++)
	{
		for(i=0;i<3;i++)
		{
			for(j=0;j<10;j++)
			{
				if(final[k]==EAN13[i][j])
				{
					final[k]=j;
					if(k>0&&k<7)final[0]=10*final[0]+i;
				}
			}
		}
	}
	for(k=0;k<10;k++)
	{
		if(final[0]==odd[k]) final[0]=k;
	}
    printf("\nRESULT:");
	for(i=0;i<13;i++)
    {
    	if(i==1||i==7) printf("-");
		printf("%d",final[i]);
	}   	   
}

int main(int argc, char* argv[])
{
    unsigned char *fp_temp;
    int a,b,c;
	FILE *fpbmp;
    FILE *fpout;
    cout<<"bmpDataPart:\n1.BmpDataPart\n2.BmpDataPartQuarter\n3.BmpDataPartQuarterHi\n4.BmpDataPartGray\n5.BmpDataPartBin\n6.BmpDataPartBinOtsu\n";
    cout<<"choose a\n";
    cin>>a;
	cout<<"bmpoutput:\n1.bmpoutput\n2.bmpoutputAverageFilter\n3.bmpoutputGaussianFilter\n4.bmpoutputEdgeDetectionScharr\n5.bmpoutputEdgeDetectionSobel\n6.bmpoutputCode\n";
    cout<<"choose b\n";
    cin>>b;
	fpbmp= fopen("C:\\Users\\Administrator\\Desktop\\ed3.bmp", "rb");//以读的方式打开二进制文件
    if (fpbmp == NULL)
    {
        return 1;
    }
    fpout= fopen("C:\\Users\\Administrator\\Desktop\\rb.bmp", "wb+");//以写的方式新建一个二进制文件
    if (fpout == NULL)
    {
        return 1;
    }
    bmpFileTest(fpbmp);                
    bmpLength(fpbmp);                  //获取图像的高和宽
    BmpWidthHeight(fpbmp);             //获得图像的rgb值
    fseek(fpbmp, 0L, SEEK_SET);//定位至fpbmp文件开始处
    fseek(fpout, 0L, SEEK_SET);//定位至fpout文件开始处
    fp_temp=(unsigned char*)malloc(OffSet);//分配内存空间
    fread(fp_temp, 1, OffSet, fpbmp);//从fpbmp读取数据到fp的数据中
    fwrite(fp_temp,1,OffSet,fpout);//从fpout写数据到fp中
    if(a==1||b==6)bmpDataPart(fpbmp); //将数据输入到指定的text文件中
    if(a==2&&b!=6)bmpDataPartQuarter(fpbmp);
    if(a==3&&b!=6)bmpDataPartQuarterHi(fpbmp);
    if(a==4&&b!=6)bmpDataPartGray(fpbmp);
    if(a==5&&b!=6)
	{
		cout<<"threshold:\n";
		cin>>c;
		bmpDataPartBin(fpbmp,c);
	}
    if(a==6&&b!=6)bmpDataPartBinOtsu(fpbmp);
    if(b==1)bmpoutput(fpout);//将修改的像素点输出
    if(b==2)bmpoutputAverageFilter(fpout);
    if(b==3)bmpoutputGaussianFilter(fpout);
    if(b==4)bmpoutputEdgeDetectionScharr(fpout);
    if(b==5)bmpoutputEdgeDetectionSobel(fpout);
    if(b==6)bmpoutputCode(fpout);
    fclose(fpout);
    fclose(fpbmp);
    return 0;
}

