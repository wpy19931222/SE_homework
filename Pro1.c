#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define STEP_MIN 0.000000001//

double map[1000][3]={0};
double tempcentre[100][2]={0};

double getstep (double r)
{
	double n = 1;
	while(r<1)
	{
		r*=10;
		n/=10;
	}
	if(r<2)
		n/=10;
	return n;
}

int findcentre (double r,int n)
{
	double step = getstep (r);
	double i = 0,j = 0;
	int k = 0,tem = 0;
	for(i = 1-r;i>-1+r;i -= step)
	{
		if(tem)
			break;
		if(i<=sqrt(2)/2&&i>=-sqrt(2)/2)
				continue;
		for(j = 1-r;j>-1+r;j -= step)
		{
			if(tem)
				break;
			if(j<=sqrt(2)/2&&j>=-sqrt(2)/2)
				continue;
			for(k = 0;k<n;k++)
			{
				if(((i-map[k][0])*(i-map[k][0])+(j-map[k][1])*(j-map[k][1]))>((r+map[k][2])*(r+map[k][2])))
				{
					tem  = 1;
					break;
				}
			}
		}
	}
	if(tem)
		return 1;
	return 0;
}

int getcentre (double r,int n)
{
	double step = getstep (r);
	double i = 0,j = 0;
	int k = 0,tem = 0;
	for(i = 1-r;i>-1+r;i -= step)
	{
		if(tem)
			break;
		if(i<=sqrt(2)/2&&i>=-sqrt(2)/2)
				continue;
		for(j = 1-r;j>-1+r;j -= step)
		{
			if(tem)
				break;
			if(j<=sqrt(2)/2&&j>=-sqrt(2)/2)
				continue;
			for(k = 0;k<n;k++)
			{
				if(((i-map[k][0])*(i-map[k][0])+(j-map[k][1])*(j-map[k][1]))>((r+map[k][2])*(r+map[k][2])))
				{
					tempcentre[tem][0]=i;
					tempcentre[tem][1]=j;
					tem++;
				}
			}
		}
	}
	return tem;
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
	if((max-min)<STEP_MIN)
		return min;
	double half = (max+min)/2;
	if(findcentre(half,n))
	{
		findr(n,half,max);
	}
	findr(n,min,half);
}

int main (int argc,char* argv[])
{
	map[0][0] = 0;
	map[0][1] = 0;
	map[0][2] = 1;
	int m = 0,n = 1,num = 0,t = 0;
	scanf("%d",&m);
	t = m-1;
	double r = 0,sum = 1;
	while(t)
	{
		r = findr(n,0,map[n-1][2]);
		if(r<STEP_MIN)
		{
			printf("Exceed precision!");
			system("pause");
			return 0;
		}
		num = getcentre(r,n);
		if(num>t)
		{
			sum+=r*r*t;
			break;
		}
		sum+=r*r*num;
		t-=num;
	}
	printf("%f\n",sum);
	system("pause");
	return 0;
}
