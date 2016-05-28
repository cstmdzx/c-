// web1pr.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <algorithm>
#include <time.h>
using namespace std;

const double threshold = 1e-5; 

const double B = 0.85;

const double nodeNum = 6110;

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


	double rNew[1000]={0.0};
	double rOld[10000]={0.0};
	ifstream fin("OrgzData.txt");
	
//	double distance;
	
	for (int i = 0; i < 1000; i++)
	{
		rOld[i] = 1.0/nodeNum;
	}
	const double add = (1 - B) * 1.0/nodeNum;
	double distance = 0.0;
	while(true)
	{
		remove("rOld.txt");
		ofstream fout("rOld.txt",ios::app);
		fin.clear();
		fin.seekg(0,ios::beg);
		int src=0,dest=0,dgr=1;
		for (int i = 0; i < 9;i++)
		{
			for (int j = 0; j < 1000; j++)
			{
				rNew[j] = 0.0;
			}
			int flag = i * 1000;
			int border = (i + 1) * 1000;
			do
			{
				
				if(!(dest < border))break;
				rNew[dest - flag] += B*rOld[src]/dgr + add;
				
				fin>>src>>dgr>>dest;
			}
			while (!fin.eof());
			if (dest < flag)
			{
				rNew[dest - flag] += B*rOld[src]/dgr + add;
//				fout<<dest<<"	"<<rNew[dest - flag]<<endl;
			}
			for (int j = 0; j < 1000 ;j++)
			{
				fout<<(j+flag)<<"	"<<rNew[j]<<endl;
			}
			
			for (int j =0;j<1000;j++)
			{
				distance += fabs(rNew[j]-rOld[j+flag]); 
			}
		}
		fout.close();
		//计算距离，判断distance是否小于阀值
		if (distance < threshold)break;
		cout<<distance<<endl;
		distance = 0.0;
		ifstream finOld("rOld.txt");
		if(!finOld)cout<<"打开失败"<<endl;
		while(!finOld.eof())
		{
			int tempSrc;
			finOld>>tempSrc;
			finOld>>rOld[tempSrc];
		}
		finOld.close();
	}
	ifstream finOld2("rOld.txt");
	while(!finOld2.eof())
	{
		int tempSrc;
		finOld2>>tempSrc;
		finOld2>>rOld[tempSrc];
	}
	finOld2.close();
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


