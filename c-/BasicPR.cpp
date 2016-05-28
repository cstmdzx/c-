// BasicPR.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <time.h>
using namespace std;

const int N = 103689;

const double threshold = 1e-5; 

const double B = 0.85;

const double nodeNum = 6110;

struct MyEdge
{
	int src;
	int dgr;
	int dest;
	MyEdge()
	{
		src = 0;
		dest = 0;
		dgr = 1;
	}
}myEdge[103700];


double AbsSum(double* a,double* b,int n )
{
	double sum = 0;
	for (int i =0;i<n;i++)
	{
		sum += fabs(a[i]-b[i]); 
	}
	return sum;
}

bool cmp (double a ,double b)
{
	return a>b;
}


int _tmain(int argc, _TCHAR* argv[])
{
	int start = clock();

	double rNew[10000]={0.0};
	double rOld[10000]={0.0};
	ifstream fin("OrgzData.txt");
	
//	double distance;
	
	for (int i = 0; i < 10000; i++)
	{
		rOld[i] = 1.0/nodeNum;
	}
	int numOfLines = 0;
	while(!fin.eof())
	{
		fin>>myEdge[numOfLines].src>>myEdge[numOfLines].dgr>>myEdge[numOfLines].dest;
		numOfLines++;
	}
	cout<<"读取完成"<<endl;
	const double add = (1 - B) * 1.0/nodeNum;
	double distance = 0.0;
	while(true)
	{

		for (int i = 0; i < 10000; i++)
		{
			rNew[i] = 0.0;
		}
		for (int i = 0; i < numOfLines; i++)
		{
			int src = myEdge[i].src;
			int dest = myEdge[i].dest;
			int dgr = myEdge[i].dgr;
			rNew[dest] += B * rOld[src] / dgr + add;
		}
		for (int i = 0;i < 10000;i++)
		{
			distance += fabs(rNew[i]-rOld[i]); 
		}
		//计算距离，判断distance是否小于阀值
		if (distance < threshold)break;
		cout<<distance<<endl;
		for(int i = 0; i < 10000; i++)
		{
			rOld[i] = rNew[i];
		}
		distance = 0.0;
	}

	sort(rOld,rOld+10000,cmp);
	ofstream result("result.txt");
	for(int i = 0; i < 100; i++)
	{
		result<<rOld[i]<<endl;
	}
	fin.close();

	int finish = clock();
	int time = finish - start;
	cout<<"运行时间： "<<time<<" ms"<<endl;
	system("pause");
	return 0;
}

