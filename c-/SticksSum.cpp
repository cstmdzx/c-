// SticksSum.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <algorithm>
using namespace std;

int set[50010];//set按照升序排列
int sNum = 0;//记录当前最后元素的后一个

int SetInsert(int l)
{
	set[sNum] = l;
	sNum ++;
	sort(set,set + sNum);
	return 0;
}

int SetFind (int value)
{
	for(int i = 0; i < sNum; i++)
	{
		if(set[i] == value)
			return i;
	}
	return -1;
}

int SetRemove(int l)
{
	int index = SetFind(l);
	set[index] = set[sNum - 1];
	sNum --;
	sort(set,set+sNum);
	return 0;
}

bool Judger()
{
	int sum = 0;
	int last = sNum - 1;
	for(int i = 0; i < last; i++)
	{
		sum += set[i];
	}
	if(sum > set[last])
	{
		return true;
	}
	else
	{
		return false;
	}
}
int _tmain(int argc, _TCHAR* argv[])
{
	int n;
	cin>>n;
	for(int i = 0; i < n; i++)
	{
		int type;
		int length;
		cin>>type>>length;
		if(type == 1)
		{
			SetInsert(length);
		}
		if(type == 2)
		{
			SetRemove(length);
		}
		if( sNum < 3 )
		{
			cout << "No" <<endl;
			continue;
		}
		bool res = Judger();
		if( res == true )
		{
			cout << "Yes" <<endl;
		}
		if( res == false )
		{
			cout << "No" <<endl; 
		}
	}
	return 0;
}

