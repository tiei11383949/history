#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#define BITMAPFILEHEADERLENGTH 14   // 24bit�ļ�ͷ����Ϊ14
#define BM 19778                    // BM��ASCII��Ϊ19778��BMΪλͼ�ı�ʶ��

using namespace std;
unsigned int OffSet=0;    // �ӱ��ⲿ�ֵ����ݲ��ֵ�ƫ����
long width ;          // �������ֵ
long height ;         // �ߵ�����ֵ
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

void bmpFileTest(FILE* fpbmp)//ͷ�����ݲ��ֵ�ƫ����
{
    unsigned short bfType = 0;
    fseek(fpbmp, 0L, SEEK_SET);// ������ļ���ʼ��
    fread(&bfType, sizeof(char), 2, fpbmp);//��2��char��С���ַ�������bftyoe�ĵ�ַ��
    if (BM != bfType)//�ж�ͼƬ��Ϣ��ǰ�����ֽ��Ƿ���λͼ�ļ��ı�ʶ��
    {
        printf("not bmp\n");
        exit(1);
    }
}
void bmpLength(FILE* fpbmp)//��ȡbmpͼ��ĸߺͿ�
{
    fseek(fpbmp, 10L, SEEK_SET);//��λ���ļ��еĵ�10���ֽ� ����10~13�ֽ�Ϊλͼ����λ�õ�ƫ�Ƶ�ַ
    fread(&OffSet, sizeof(char), 4, fpbmp);//��ȡfpbmp�ļ��е�4���ֽڷ���offset��
    printf("The Header Part is of length %d.\n", OffSet);
}
void BmpWidthHeight(FILE* fpbmp) //��ȡrgb������
{
    fseek(fpbmp, 18L, SEEK_SET);//��λ���ļ��ĵ�18���ֽڣ���18~21�ֽڼ�¼λͼ�Ŀ��
    fread(&width, sizeof(char), 4, fpbmp);//��λͼ�ĸ��ֽڴ洢��width��
    fseek(fpbmp, 22L, SEEK_SET);//��λ���ļ��ĵ�22���ֽڣ���22~25�ֽڼ�¼λͼ�ĸ߶�
    fread(&height, sizeof(char), 4, fpbmp);
}

void bmpDataPart(FILE* fpbmp)
{
    int i, j=0;
    int stride;
    unsigned char* pix=NULL;
    fseek(fpbmp, OffSet, SEEK_SET);//�������ļ���ƫ�Ƶ�ַ��
    stride=(24*width+31)/8;
    stride=stride/4*4;//�����ص�ˮƽ�ߵ��ֽ�������4�ı�����λ4�ı���
    pix=(unsigned char*)malloc(stride);//����stride���ڴ�ռ�
    for(j=0;j<height;j++)
    {
        fread(pix, 1, stride, fpbmp);//ÿ�ζ�һ���ֽڣ�����stride�Σ���fpbmp��ȡ������pix��
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
    fseek(fpbmp, OffSet, SEEK_SET);//�������ļ���ƫ�Ƶ�ַ��
    stride=(24*width+31)/8;
    stride=stride/4*4;//�����ص�ˮƽ�ߵ��ֽ�������4�ı�����λ4�ı���
    pix=(unsigned char*)malloc(stride);//����stride���ڴ�ռ�
    for(j=0;j<height;j++)
    {
        fread(pix, 1, stride, fpbmp);//ÿ�ζ�һ���ֽڣ�����stride�Σ���fpbmp��ȡ������pix��
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
    fseek(fpbmp, OffSet, SEEK_SET);//�������ļ���ƫ�Ƶ�ַ��
    stride=(24*width+31)/8;
    stride=stride/4*4;//�����ص�ˮƽ�ߵ��ֽ�������4�ı�����λ4�ı���
    pix=(unsigned char*)malloc(stride);//����stride���ڴ�ռ�
    for(j=0;j<height;j++)
    {
        fread(pix, 1, stride, fpbmp);//ÿ�ζ�һ���ֽڣ�����stride�Σ���fpbmp��ȡ������pix��
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
    fseek(fpbmp, OffSet, SEEK_SET);//�������ļ���ƫ�Ƶ�ַ��
    stride=(24*width+31)/8;
    stride=stride/4*4;//�����ص�ˮƽ�ߵ��ֽ�������4�ı�����λ4�ı���
    pix=(unsigned char*)malloc(stride);//����stride���ڴ�ռ�
    for(j=0;j<height;j++)
    {
        fread(pix, 1, stride, fpbmp);//ÿ�ζ�һ���ֽڣ�����stride�Σ���fpbmp��ȡ������pix��
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
    int n0=0,n1=0; //��ֵ���¸��� 
	float w0=0,w1=0; // ��ֵ���±��� 
    float u0=0,u1=0;//��ֵ���»Ҷ�ƽ��ֵ 
    int div,div0=0;//��ֵ
	float giv,g0=0;//��䷽�� 
	
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
            pixout[i*3+2]=r[height-1-j][i];//��rgb������ֵ��pixout�������ͼ��
            pixout[i*3+1]=g[height-1-j][i];
            pixout[i*3]=b[height-1-j][i];
        }
        fwrite(pixout, 1, stride, fpout);//��pixout�е�������ÿ��һ���ֽڣ���stride��д��fpout��
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
	fpbmp= fopen("C:\\Users\\Administrator\\Desktop\\ed3.bmp", "rb");//�Զ��ķ�ʽ�򿪶������ļ�
    if (fpbmp == NULL)
    {
        return 1;
    }
    fpout= fopen("C:\\Users\\Administrator\\Desktop\\rb.bmp", "wb+");//��д�ķ�ʽ�½�һ���������ļ�
    if (fpout == NULL)
    {
        return 1;
    }
    bmpFileTest(fpbmp);                
    bmpLength(fpbmp);                  //��ȡͼ��ĸߺͿ�
    BmpWidthHeight(fpbmp);             //���ͼ���rgbֵ
    fseek(fpbmp, 0L, SEEK_SET);//��λ��fpbmp�ļ���ʼ��
    fseek(fpout, 0L, SEEK_SET);//��λ��fpout�ļ���ʼ��
    fp_temp=(unsigned char*)malloc(OffSet);//�����ڴ�ռ�
    fread(fp_temp, 1, OffSet, fpbmp);//��fpbmp��ȡ���ݵ�fp��������
    fwrite(fp_temp,1,OffSet,fpout);//��fpoutд���ݵ�fp��
    if(a==1||b==6)bmpDataPart(fpbmp); //���������뵽ָ����text�ļ���
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
    if(b==1)bmpoutput(fpout);//���޸ĵ����ص����
    if(b==2)bmpoutputAverageFilter(fpout);
    if(b==3)bmpoutputGaussianFilter(fpout);
    if(b==4)bmpoutputEdgeDetectionScharr(fpout);
    if(b==5)bmpoutputEdgeDetectionSobel(fpout);
    if(b==6)bmpoutputCode(fpout);
    fclose(fpout);
    fclose(fpbmp);
    return 0;
}

