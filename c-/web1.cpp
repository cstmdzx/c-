// web1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include<fstream>
#include<string>
#include<algorithm>
#include<sstream>
using namespace std;

struct MyEdge
{
	int src;
	int dest;
	MyEdge()
	{
		src=0x0fffffff;
		dest=0x0fffffff;
	}
}myEdge[110000];

struct MyEdgeWithDegree
{
	int src;
	int dest;
	int dgr;
	MyEdgeWithDegree()
	{
		src=0x0fffffff;
		dest=0x0fffffff;
	}
}myEdgeWD[110000];

bool cmp(MyEdge e1,MyEdge e2)
{
	//按照src升序排列，src相同就按照dest升序排列
	if(e1.src != e2.src) return e1.src < e2.src;
	else return e1.dest < e2.dest;
}

bool cmp2(MyEdgeWithDegree e1,MyEdgeWithDegree e2)
{
	//按照dest升序排列，dest相同就按照src升序排列
	if(e1.dest != e2.dest) return e1.dest < e2.dest;
	else return e1.src < e2.src;
}

int myMax(int a ,int b )
{
	if(a>b)return a;
	else return b;
} 

int _tmain(int argc, _TCHAR* argv[])
{
	////ofstream fout0("wkdt0.txt",ios::app);ofstream fout1("wkdt1.txt",ios::app);ofstream fout2("wkdt2.txt",ios::app);ofstream fout3("wkdt3.txt",ios::app);ofstream fout4("wkdt4.txt",ios::app);
	////ofstream fout5("wkdt5.txt",ios::app);ofstream fout6("wkdt6.txt",ios::app);ofstream fout7("wkdt7.txt",ios::app);ofstream fout8("wkdt8.txt",ios::app);
	////ofstream* fout[9]={&fout0,&fout1,&fout2,&fout3,&fout4,&fout5,&fout6,&fout7,&fout8};
	////ifstream fin("count.txt");
	//ifstream fin("wkdt8.txt");
	//ofstream fout("wdt8.txt");
	int test = 0;
	int src;
	int dest;
	int maxSrc=0;
	int maxDest=0;
	int maxDest2=0;
	int flag=0;
	//ofstream fout("count.txt");
	//ofstream fout("count2.txt");
	
	int num=0;
	int count=1;
	int maxCount = 0;
	int numOfNode = 0;
	//MyEdgeWithDegree mEWD[1000];
	
	ifstream fin("wikidata.txt");
	ofstream fout("OrgzData.txt");
	ofstream fout2("Info.txt");
	while(!fin.eof() )
	{		
		fin>>myEdge[num].src>>myEdge[num].dest;
		maxSrc = myMax(maxSrc,myEdge[num].src);
		maxDest = myMax(maxDest,myEdge[num].dest);
		num++;
			//计算出度
		//fin>>mEWD[count].src;
		//fin>>mEWD[count].dgr;
		//fin>>mEWD[count].dest;
		//if(mEWD[count].src == flag)count++;
		//else
		//{
		//	if(count > 1)
		//		fout<<mEWD[1].src<<"	"<<mEWD[1].dgr<<"	"<<count-1;
		//	for(int i = 1;i<count;i++)
		//	{
		//		fout<<"	"<<mEWD[i].dest;
		//	}
		//	if(count > 1)
		//		fout<<endl;
		//	numOfNode++;
		//	flag = mEWD[count].src;
		//	if(count > maxCount)maxCount = count;
		//	mEWD[1].src=mEWD[count].src;
		//	mEWD[1].dgr=mEWD[count].dgr;
		//	mEWD[1].dest=mEWD[count].dest;
		//	count = 2;
		//}


//		//分块
//		fin>>myEdgeWD.src>>myEdgeWD.dgr>>myEdgeWD.dest;
//		//stringstream ss;
//		//string tmp;
//		int cutByDest = myEdgeWD.dest/1000;//按照dest，每1000分成一块
//		*fout[cutByDest]<<myEdgeWD.src<<"	"<<myEdgeWD.dgr<<"	"<<myEdgeWD.dest<<endl;
//		//if(myEdge.src > maxSrc) maxSrc = myEdge.src;
//		//if(myEdge.dest > maxDest) maxDest = myEdge.dest;
////		num++;
	}
	fout2<<num<<endl;
	fout2<<maxSrc<<"	"<<maxDest<<endl;
	sort(myEdge,myEdge+110000,cmp);

	int start = 0;
	//统计每个点的出度
	flag = myEdge[0].src;
	for(int i = 0;i < 110000;i++)
	{
		if(flag == myEdge[i].src)
		{
			count++;
			continue;
		}
		
		for(int j = start;j<start+count;j++)
		{
			myEdgeWD[j].src=myEdge[j].src;
			myEdgeWD[j].dest=myEdge[j].dest;
			myEdgeWD[j].dgr=count;
			maxDest2=myMax(maxDest2,myEdgeWD[j].dest);
			
		}
		count = 1;
		start = i;
		flag = myEdge[i].src;
		numOfNode++;
		
		//mEWD[count].src = myEdge[i].src;
		////fin>>mEWD[count].dgr;
		//mEWD[count].dest = myEdge[i].dest;
		//
		//if(count > 1)
		//	fout<<mEWD[1].src<<"	"<<mEWD[1].dgr<<"	"<<count-1;
		//for(int i = 1;i<count;i++)
		//{
		//	fout<<"	"<<mEWD[i].dest;
		//}
		//if(count > 1)
		//	fout<<endl;
		//for(int j=0;j<1000;j++)
		//{
		//	
		//	if(mEWD[count].src == flag)count++;
		//	else
		//	{
		//		
		//		numOfNode++;
		//		flag = mEWD[count].src;
		//		if(count > maxCount)maxCount = count;
		//		mEWD[1].src=mEWD[count].src;
		//		mEWD[1].dgr=mEWD[count].dgr;
		//		mEWD[1].dest=mEWD[count].dest;
		//		count = 2;
		//		break;
		//	}
		//}
	}
	sort(myEdgeWD,myEdgeWD+110000,cmp2);
	
	for(int i = 0;i < 110000;i++)
	{
		if(myEdgeWD[i].src == 0x0fffffff && myEdgeWD[i].dest == 0x0fffffff &&myEdgeWD[i].dgr == 0 )break;
		fout<<myEdgeWD[i].src<<"	"<<myEdgeWD[i].dgr<<"	"<<myEdgeWD[i].dest<<endl;
	}

	cout<<"共有"<<num<<"条边"<<endl;
	cout<<"最大的源"<<maxSrc<<endl;
	cout<<"最大的目的"<<maxDest<<"	"<<maxDest2<<endl;
	cout<<"结点的个数"<<numOfNode<<endl;
	fout2<<numOfNode<<endl;
	fin.close();
	fout.close();
	fout2.close();
//	cout<<numOfNode<<endl;
	//for(int i = 0;i<9;i++)
	//{
	//	(*fout[i]).close();
	//}

	system("pause");
	return 0;
}

