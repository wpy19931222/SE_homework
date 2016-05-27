#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define EQUAL 0.000000000000002
#define POINT 100
#define ACCURACY idon`tknow

double map[1000][3] = {0};
int balloon = 0;
double tempmap[1000][3] = {0};
double blocks[1000][2] = {0};
int block = 0;

srand((unsigned)time(NULL));

int believe (int n,double r)//r为无blocks时最大r
{
	if(((double)rand() % 100)/100 < tempmap[n][2] / r)//置信函数
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

void randpoint (void)
{
	int i = 0;
	for(i = 0;i < POINT;i ++)
	{
		tempmap[i][0] = ((double)rand() % (2 * ACCURACY) - ACCURACY) / ACCURACY;
		tempmap[i][1] = ((double)rand() % (2 * ACCURACY) - ACCURACY) / ACCURACY;
		if(iscoincided(i))
		{
			i --;
			continue;
		}
		tempmap[i][2] = getr(i);
	}
}

int deleteblocks (double x,double y,double r)
{
	int i = 0,j = 0,k = 0;
	for(i = 0;i < block;i ++)
		for(j = 0;j < balloon;j ++)
			if((sqrt((blocks[i][0] - map[j][0]) * (blocks[i][0] - map[j][0]) + (blocks[i][1] - map[j][1]) * (blocks[i][1] - map[j][1])) - map[j][2]) < EQUAL)
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