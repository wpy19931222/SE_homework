#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define POINT 100
#define ACCURACY idon`tknow

double map[1000][3] = {0};

srand((unsigned)time(NULL));

int believe (int n,double r)
{
	if(((double)rand()%100)/100<map[n][2]/r)//置信函数
	{
		return n;
	}
	return believe(n+1,r);
}

double getr (int i)
{
	;
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
