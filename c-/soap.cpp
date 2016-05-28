// soap.cpp : 定义控制台应用程序的入口点。
/*******************************************************************/
/*******************************************************************/

//只能处理class部分，需要手动删掉*.owl里的其它部分，包括注释
//删除之后需要将文件命名为*.txt
//注意数组大小，若是class较多，则需要把mcc的数组开大一点
//authored by nklyp

/*******************************************************************/
/*******************************************************************/


#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

struct MyChemistryClass
{
	string name;
	int sonIndex[1000];
	string sequence;
	int sonC;//son的个数
	int fatherIndex;
	MyChemistryClass()
	{
		name = "";
		sequence = "6";
		sonC = 0;
		fatherIndex = -1;
		for(int i = 0; i < 30; i++)
		{
			sonIndex[i] = -1;
		}
	}
}mcc[10000];

//有些individual属于不止一个category，
//与家威学长沟通后，目前只保存一个
//可能概念模型设计的有问题，目前先这样进行，有问题再改
//先不设计新的结构体，还用上面的结构体


string chemistry_class[1000];

const string strType[5] = {
	"<owl:ObjectProperty",
	"<owl:DatatypeProperty",
	"<owl:Class",
	"<owl:NamedIndividual",
	"END"
};

int typeJudgement(string line)
{
	//0表示ObjProp,1表示DataProp,2表示Class,3表示Individual,4是一个flag，一般不会返回，
	//-1表示没找到，-2表示有问题
	int i = 0;
	int flag = -1;
	for(;i < 5;i++)
	{
		flag = line.find(strType[i]);
		if(flag != -1)
		{
			return i;
		}
	}
	if( i == 5 )
	{
		return -1;
	}  
	return -2;
}

int OutFunction(int index,ofstream &fout,int level)
{	
	stringstream ss;
	ss << level;
	string s;
	ss >> s;
	int father = mcc[index].fatherIndex;
	if(father == -1)
	{
		//mcc[index].sequence = mcc[index].sequence + "." + s;
	}
	else
	{
		mcc[index].sequence = mcc[father].sequence + "." + s;
	}

	
	fout<<mcc[index].sequence<<"	";
	fout<<mcc[index].name<<endl;
	
	if(mcc[index].sonC == 0)//递归结束条件
	{
		return 0;
	}
	
	for(int i = 0; i < mcc[index].sonC ; i++)
	{
		OutFunction(mcc[index].sonIndex[i], fout, i + 1);
	}

	return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{

	ifstream fin("chemistry - test5.owl");
	ofstream foutDataProp("DataProp.txt");//保存dataprop
	ofstream foutObjProp("ObjProp.txt");//保存objectprop
	ofstream foutClass("Class.txt");//保存class，由于下一步的Individual里面也有class的部分，因此这个文件其实没有实际的用途，个人用来调试
	ofstream foutIndiv("Individual.txt");//保存Individual


	int classCount = 0;//统计一共多少个目录项
	int indivCount = 0;//统计一共多少个Individual项
	if(!fin)
	{
		cout<<"File not found"<<endl;
		system("pause");
		return -1;
	}	

	string line;
	string sub;	
	

	//首先把所有的名字都读进来
	while(!fin.eof())
	{

		getline(fin,line);


		if(line.length() < 3)
		{
			continue;
		}

		int flag = typeJudgement(line);

		//0表示ObjProp,1表示DataProp,2表示Class,3表示Individual,4是一个flag，一般不会返回，
		//-1表示没找到，-2表示有问题
		if (flag == -2) {cout<<"ERROR"<<endl; continue;}
		if (flag == -1) continue;
		int start = line.find('#');
		int end = line.find("/>");
		if (start == -1)continue;
		if (end == -1)
		{
			end = line.find(">");
		}
		sub = line.substr(start+1,end-2-start);
		switch(flag)
		{	
		case 0://ObjProp
			foutObjProp<<sub<<endl;
			break;
		case 1://DataProp
			foutDataProp<<sub<<endl;
			break;
		case 2://Class
			foutClass<<sub<<endl;
			mcc[classCount].name = sub;
			classCount++;
			indivCount = classCount;
			break;
		case 3://Individual
			foutIndiv<<sub<<endl;
			mcc[indivCount].name = sub;
			indivCount++;
			break;
		}

		
		
//		cout<<sub<<endl;
//		fout<<sub<<endl;

//		count++;
		
	}

	cout<<classCount<<endl;
	cout<<indivCount<<endl;
	fin.clear();
	fin.seekg(0,ios::beg);



	//接下来按照每个的subclass of确定给他爸爸加一个儿子的指针

	while(!fin.eof())
	{
		getline(fin,line);
		if( line.find("// Classes") != -1)break;
	}

	while(!fin.eof())
	{

		getline(fin,line);

		if(line.find("// Individuals") != -1)break;//证明已经处理完class部分

		int flagT = line.find('!');
		int flagS = line.find("subClassOf");
		if (flagT == -1 && flagS == -1)continue;
		if (flagT != -1)
		{
			int start = line.find('#');
			int end = line.find(" -");
			if (start == -1)continue;
			sub = line.substr(start+1,end-1-start);//son
//			fout<<sub<<endl;
		}
		if (flagS != -1)
		{			
			int start = line.find('#');
			int end = line.find("/>");
			string father = line.substr(start+1,end -2 - start);
//			fout<<father<<endl;
			int sonIndex = 0;
			for(;sonIndex < classCount; sonIndex++)
			{
				if(mcc[sonIndex].name == sub)
					break;
			}
			int fatherIndex = 0;
			for(;fatherIndex < classCount; fatherIndex++)
			{
				if(mcc[fatherIndex].name == father)
				{
					mcc[fatherIndex].sonIndex[ mcc[fatherIndex].sonC ] = sonIndex;
					mcc[fatherIndex].sonC++;
					mcc[sonIndex].fatherIndex = fatherIndex;
					break;
				}
			}
		}		
	}
	//至此已经处理完class的树形结构，接下来处理Individual
	
	while(!fin.eof())
	{
		getline(fin,line);

		int flagT = line.find('!');
		int flagS = line.find("<owl:NamedIndividual");
		if (flagT == -1 && flagS == -1)continue;
		if (flagT != -1)
		{
			int start = line.find('#');
			int end = line.find(" -");
			if (start == -1)continue;
			sub = line.substr(start+1,end-1-start);//son
//			fout<<sub<<endl;
		}
		if (flagS != -1)
		{
			getline(fin,line);
						

			int start = line.find('#');
			if(start == -1)continue;
			int end = line.find("/>");
			string father = line.substr(start+1,end -2 - start);
//			fout<<father<<endl;
			int sonIndex = classCount;
			for(;sonIndex < indivCount; sonIndex++)
			{

				if(sonIndex == 34)
				{
					cout<<"debug1"<<endl;
				}

				if(mcc[sonIndex].name == sub)
					break;
			}
			int fatherIndex = 0;
			for(;fatherIndex < classCount; fatherIndex++)
			{

				if(fatherIndex == 34)
				{
					cout<<"debug2"<<endl;
				}

				if(mcc[34].sequence != "6")
				{
					cout<<"signal1"<<endl;
					cout<<fatherIndex<<endl;
				}

				if(mcc[fatherIndex].name == father)
				{
					mcc[fatherIndex].sonIndex[ mcc[fatherIndex].sonC ] = sonIndex;
					mcc[fatherIndex].sonC++;
					mcc[sonIndex].fatherIndex = fatherIndex;
					break;
				}
				if(mcc[34].sequence != "6")
				{
					cout<<"signal2"<<endl;
					cout<<fatherIndex<<endl;
				}
			}
		}	
	}

	ofstream fout("result.txt");

	int rootNum = 1;
	for(int i = 0; i < indivCount; i++)
	{
		if(mcc[i].fatherIndex == -1)
		{

			OutFunction(i,fout,rootNum);
			rootNum++;
		}

	}

	fin.close();
	fout.close();
	foutDataProp.close();
	foutObjProp.close();
	foutClass.close();
	foutIndiv.close();
	system("pause");
	return 0;
}

