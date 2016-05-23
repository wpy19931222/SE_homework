#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define STEP_MIN 0.000000000000001//


double map[1000][3]={0};

double getstep (double r)
{
	double n = 1;
	while(r<1)
	{
		r*=10;
		n/=10;
	}
	if(r<2)
		n/=3;
	return n/10;
}

int findcentre (double r,int n)
{
    double cut = sqrt(2)/2;
	double step = getstep (r);
	double i = 0,j = 0;
	int k = 0,tem = 0;
	for(i = 1-r;i>0;i -= step)
	{
		if(tem)
			break;
		if(i<=cut)
				break;
		for(j = 1-r;j>0;j -= step)
		{
			if(tem)
				break;
			if(j<=cut)
				break;
			for(k = 0;k<n;k++)
			{
                tem = 1;
				if(((i-map[k][0])*(i-map[k][0])+(j-map[k][1])*(j-map[k][1]))<((r+map[k][2])*(r+map[k][2])))
				{
                    //printf("%lf    %lf    %d\n",i,j,k);
                    //printf("%.15lf\n",r);
                    //system("pause");
					tem  = 0;
					break;
				}
			}
		}
	}
        return tem;
}

int getcentre (double r,int n)
{
    double cut = sqrt(2)/2;
	double step = getstep (r);
	double i = 0,j = 0;
	int k = 0,tem = 0,flag = 0;
	for(i = 1-r;i>0;i -= step)
	{
		if(i<=cut)
				break;
		for(j = 1-r;j>0;j -= step)
		{
            flag = 0;
			if(j<=cut)
				break;
			for(k = 0;k<n+tem;k++)
			{
                flag = 1;
				if(((i-map[k][0])*(i-map[k][0])+(j-map[k][1])*(j-map[k][1]))<((r+map[k][2])*(r+map[k][2])))
				{
                    flag = 0;
					break;
				}
			}
            if(flag)
		    {
                map[n+tem][0] = i;
		  	    map[n+tem][1] = j;
                map[n+tem][2] = r;
			    tem++;
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
		return findr(n,half,max);
	}
	return findr(n,min,half);
}

int main (int argc,char* argv[])
{
	map[0][0] = 0;
	map[0][1] = 0;
	map[0][2] = 1;
	int m = 0,n = 1,num = 0,t = 0,i = 0;
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
		if(num*4>t)
		{
			sum+=r*r*t;
			break;
		}
		sum+=r*r*num*4;
		t-=num*4;
		n+=num;
	}
	printf("%.15lf\n",sum);
	system("pause");
	return 0;
}
