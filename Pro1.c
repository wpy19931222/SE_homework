#include <stdio.h>
#include <math.h>

double map[1000][3]={0};
double tempcentre[100][2]={0};

int findcentre (double r,int n)
{
	double step = getstep (r);
	double i=0,j=0;
	int k=0,tem=0;
	for(i = 1-step;i>-1+step;i -= step)
	{
		if(tem)
			break;
		if(i<=sqrt(2)/2&&i>=-sqrt(2)/2)
				continue;
		for(j = 1-step;j>-1+step;j -= step)
		{
			if(tem)
				break;
			if(j<=sqrt(2)/2&&j>=-sqrt(2)/2)
				continue;
			for(k = 0;k<n;k++)
			{
				/*if(((i-map[k][0])*(i-map[k][0])+(j-map[k][1])*(j-map[k][1])>(((r-map[k][3])*(r-map[k][3]))))
				{
					tempcentre[tem][0]=i;
					tempcentre[tem][1]=j;
					tem++;
				}*/
				//用作getcentre，先判断存在，且找好精确R之后再get
				if(((i-map[k][0])*(i-map[k][0])+(j-map[k][1])*(j-map[k][1])>(((r-map[k][3])*(r-map[k][3]))))
				{
					tem = 1;
					break;
				}
			}
		}
	}
	if(tem)
		return 1;
	return 0;
}

//void getcentre (double r,int n)

double getstep (double r)
{
	;
}

double findr (int n,double min,double max)
{
	/*double half = (max+min)/2;
	while(!findcentre(half,n))
	{
		half = (half+min)/2;
	}
	if((half-min)<0.0000001)//........
		return min;
	findr(n,half,max);*/
	if((max-min)<0.0000001)//.....
		return min;
	double half = (max+min)/2;
	if(findcentre(half,n))
	{
		find(n,half,max);
	}
	find(n,min,half);
}

int main (int argc,char* argv[])
{
	map[0][0] = 0;
	map[0][1] = 0;
	map[0][2] = 1;
	int num = 1;
}
