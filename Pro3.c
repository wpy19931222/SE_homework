#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <pthread.h>

#define EQUAL 0.000000000000002
#define POINT 100
#define ACCURACY 100000

double map[1000][3] = {0};
int balloon = 0;
double tempmap[1000][3] = {0};
double blocks[1000][2] = {0};
int block = 0;
double finalr;


void getrmax (void)
{
	double i = 0,j = 0,r = 0;
	int k = 0;
	for(i = 1;i > -1;i += ACCURACY)
		for(j = 1;j > -1;j += ACCURACY)
		{
			r = 1;
			if(r > 1 - i)
				r = 1 - i;
			if(r > 1 + i)
				r = 1 + i;
			if(r > 1 - j)
				r = 1 - j;
			if(r > 1 + j)
				r = 1 + j;
			k = 0;
			for(k = 0;k < balloon;k ++)
			{
				if(r > sqrt((map[k][0] - i) * (map[k][0] - i) + (map[k][1] - j) * (map[k][1] - j)) - map[k][2])
					r = sqrt((map[k][0] - i) * (map[k][0] - i) + (map[k][1] - j) * (map[k][1] - j)) - map[k][2];
			}
			if(r > finalr)
				finalr = r;
		}
}

int believe (int n,double r)//r为无blocks时最大r
{
	if((double)(rand() % 100)/100 < tempmap[n][2] / r)//置信函数
	{
		return n;
	}
	return believe(n + 1,r);
}

double getr (int n)
{
	double r = 1;
	if(r > 1 - tempmap[n][0])
		r = 1 - tempmap[n][0];
	if(r > 1 + tempmap[n][0])
		r = 1 + tempmap[n][0];
	if(r > 1 - tempmap[n][1])
		r = 1 - tempmap[n][1];
	if(r > 1 + tempmap[n][1])
		r = 1 + tempmap[n][1];
	int i = 0;
	for(i = 0;i < block;i ++)
	{
		if(r > sqrt((blocks[i][0] - tempmap[n][0]) * (blocks[i][0] - tempmap[n][0]) + (blocks[i][1] - tempmap[n][1]) * (blocks[i][1] - tempmap[n][1])))
			r = sqrt((blocks[i][0] - tempmap[n][0]) * (blocks[i][0] - tempmap[n][0]) + (blocks[i][1] - tempmap[n][1]) * (blocks[i][1] - tempmap[n][1]));
	}
	for(i = 0;i < balloon;i ++)
	{
		if(r > sqrt((map[i][0] - tempmap[n][0]) * (map[i][0] - tempmap[n][0]) + (map[i][1] - tempmap[n][1]) * (map[i][1] - tempmap[n][1])) - map[i][2])
			r = sqrt((map[i][0] - tempmap[n][0]) * (map[i][0] - tempmap[n][0]) + (map[i][1] - tempmap[n][1]) * (map[i][1] - tempmap[n][1])) - map[i][2];
	}
}

int iscoincided (int n)
{
	/*if(tempmap[n][0] == 1||tempmap[n][0] == -1||tempmap[n][1] == 1||tempmap[n][1] == -1)
		return 1;//*/
	int i = 0;
	for(i = 0;i < block;i ++)
		if((tempmap[n][0] - blocks[i][0]) < EQUAL && (tempmap[n][1] - blocks[i][1]) < EQUAL)
			return 1;
	for(i = 0;i < balloon;i ++)
		if(sqrt((map[i][0] - tempmap[n][0]) * (map[i][0] - tempmap[n][0]) + (map[i][1] - tempmap[n][1]) * (map[i][1] - tempmap[n][1])) < map[i][2])
			return 1;
	return 0;
}

int randpoint (double rmax)
{
	int i = 0;
	for(i = 0;i < POINT;i ++)
	{
		tempmap[i][0] = ((double)(rand() % (2 * ACCURACY) - ACCURACY)) / ACCURACY;
		tempmap[i][1] = ((double)(rand() % (2 * ACCURACY) - ACCURACY)) / ACCURACY;
		if(iscoincided(i))
		{
			i --;
			continue;
		}
		tempmap[i][2] = getr(i);
		if(believe(i,rmax))
		{
			map[balloon][0] = tempmap[i][0];
			map[balloon][1] = tempmap[i][1];
			map[balloon][2] = tempmap[i][2];
			return 1;
		}
	}
	return 0;
}

int deleteblocks (double * x)
{
	int i = 0,j = 0,k = 0;
	for(i = 0;i < block;i ++)
		if((sqrt((blocks[i][0] - *x) * (blocks[i][0] - *x) + (blocks[i][1] - *(x+1)) * (blocks[i][1] - *(x+1))) - *(x+2)) < EQUAL)
		{
			block --;
			for(k = i;k < block - 1;k ++)
			{
				blocks[k][0] = blocks[k+1][0];
				blocks[k][1] = blocks[k+1][1];
			}
			return 0;
		}
}

void pth_creat(int x)
{
	pthread_t t1,t2;
	pthread_create(&t1,NULL,getrmax,NULL);
	pthread_create(&t2,NULL,deleteblocks,map[x]);
	pthread_join(t1,NULL);
	pthread_join(t2,NULL);
}

int main (int argc,char* argv[])
{
    srand((unsigned)time(NULL));
	int m = 0,i = 0;
	printf("请输入气球个数m和blocks个数n\n");
	scanf("%d%d",&m,&block);
	if(block != 0)
	{
		printf("请依次输入每个blocks的坐标，最大精度为10^-15\n");
		for(i = 0;i < block;i ++)
			scanf("%lf%lf",&blocks[i][0],&blocks[i][1]);
	}
	getrmax();
	for(i = 0;i < m; i ++)
	{
		if(randpoint(finalr))
		{
			pth_creat(balloon);
			balloon ++;
			continue;
		}
		else
		{
			i --;
			continue;
		}
	}
	system("pause");
	return 0;
}
