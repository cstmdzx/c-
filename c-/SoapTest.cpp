// soap.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;


int _tmain(int argc, _TCHAR* argv[])
{
	ifstream fin("chemistry-class.txt");
	ofstream fout("test.txt");
	int count = 0;
	if(!fin)
	{
		cout<<"error"<<endl;
		system("pause");
		return -1;
	}
	while(!fin.eof())
	{
		string line;
		getline(fin,line);
		string sub;
//		int count = 0;
		if(line.length() < 3)
		{
			continue;
		}
		int flag = line.find('!');
		if (flag == -1)continue;
		int start = line.find('#');
		int end = line.find(" -");
		if (start == -1)continue;
		sub = line.substr(start+1,end-start);
		cout<<sub<<endl;
		fout<<count<<" "<<sub<<endl;
		count++;
		
	}
	fin.close();
	fout.close();
	system("pause");
	return 0;
}

