// OrSum.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
using namespace std;



int _tmain(int argc, _TCHAR* argv[])
{
	int bx[32] = {0};
	int by[32] = {0};
	int bk[32] = {0};
	int bres[32] = {0};
	int x,k,kk;

	cin>>x>>k;
	int num;
	int numk;
	for(int i = 0; i < 32; i++)
	{
		bx[i] = x % 2;
		x = x/2;
		if(x == 0)
		{
			num = i;
			break;
		}
	}
	for(int i = num; i > -1; i--)
	{
		if ( bx[i] == 0 )
			by[i] = 1;
		if ( bx[i] == 1 )
			by[i] = 0;
	}
	for(int i = 0; i < 32; i++)
	{
		bk[i] = k % 2;
		k = k/2;
		if(k == 0)
		{
			numk = i;
			break;
		}
	}
	for(int i = 0,j=0; i < numk+1; j++)
	{
		if (bx[j] == 0)
		{
			bres[j] = bk[i];
			i++;
		}
	}
	int flag = num + numk +1;
	int sum = 0;
	for(int i = 31;i > -1;i--)
	{
		sum = sum * 2 + bres[i];
	}

	cout<<sum<<endl;
	
	system("pause");
		
	
	return 0;
}
