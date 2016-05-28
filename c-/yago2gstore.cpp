// yago2gstore.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <string>
#include <time.h>
using namespace std;


int _tmain(int argc, _TCHAR* argv[])
{
	double tStart = clock();
	ifstream fin("yago2core.n3");
	ofstream fout("yagogstorecore2.txt");
	string line;
	
	for(int i = 0;i < 5;i++)
	{
		getline(fin,line);
	}

	while( !fin.eof() )
	{
		getline(fin,line);
		if(line == " ")continue;

		int start1 = line.find(" ");
		string subject = line.substr(0,start1);
//		cout<<subject<<endl;
		int start2 = line.find(" ",start1+1);
		string predicate = line.substr(start1+1,start2-start1-1);
//		cout<<predicate<<endl;
		int start3 = line.find(" .",start2);
		string object = line.substr(start2+1,start3-start2-1);
		if(object[0] != '<')
		{
			object = "<" + object + ">";
		}
//		cout<<object<<endl;
//		cout<<subject<<predicate<<object<<"test";
		string res = subject + "	" 
			+ "<" + predicate + ">" +"	"
			+ object +".";
//		cout<<res<<"fff"<<endl;
		fout<<res<<endl;
	}
	fin.close();
	fout.close();
	double tFinish = clock();
	cout << ( tFinish - tStart )/1000 <<endl;
	system("pause");
	return 0;
}

