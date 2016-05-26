#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define POINT 100
#define ACCURACY idon`tknow

double map[1000][3] = {0};
double blocks[1000][2] = {0};
int block = 0;

srand((unsigned)time(NULL));

int believe (int n,double r)//r为无blocks时最大r
{
	if(((double)rand()%100)/100<map[n][2]/r)//置信函数
	{
		return n;
	}
	return believe(n+1,r);
}

double getr (int n)
{
	double r = 1;
	if(r>1-map[n][0])
		r = 1-map[n][0];
	if(r>1+map[n][0])
		r = 1+map[n][0];
	if(r>1-map[n][1])
		r = 1-map[n][1];
	if(r>1+map[n][1])
		r = 1+map[n][1];
	int i = 0;
	for(i = 0;i<block;i++)
	{
		if(r>sqrt((blocks[i][0]-map[n][0])*(blocks[i][0]-map[n][0])+(blocks[i][1]-map[n][1])*(blocks[i][1]-map[n][1])))
			r = sqrt((blocks[i][0]-map[n][0])*(blocks[i][0]-map[n][0])+(blocks[i][1]-map[n][1])*(blocks[i][1]-map[n][1]));
	}
	for(i = 0;i<n-1;i++)
	{
		if(r>sqrt((map[i][0]-map[n][0])*(map[i][0]-map[n][0])+(map[i][1]-map[n][1])*(map[i][1]-map[n][1]))-map[i][2])
			r = sqrt((map[i][0]-map[n][0])*(map[i][0]-map[n][0])+(map[i][1]-map[n][1])*(map[i][1]-map[n][1]))-map[i][2];
	}
}

void randpoint (void)
{
	int i = 0;
	for(i = 0;i<POINT;i++)
	{
		map[i][0] = ((double)rand()%(2*ACCURACY)-ACCURACY)/ACCURACY;
		map[i][1] = ((double)rand()%(2*ACCURACY)-ACCURACY)/ACCURACY;
		map[i][2] = getr(i);
	}
}
