// soap.cpp : �������̨Ӧ�ó������ڵ㡣
/*******************************************************************/
/*******************************************************************/

//ֻ�ܴ���class���֣���Ҫ�ֶ�ɾ��*.owl����������֣�����ע��
//ɾ��֮����Ҫ���ļ�����Ϊ*.txt
//ע�������С������class�϶࣬����Ҫ��mcc�����鿪��һ��
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
	int sonC;//son�ĸ���
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

//��Щindividual���ڲ�ֹһ��category��
//�����ѧ����ͨ��Ŀǰֻ����һ��
//���ܸ���ģ����Ƶ������⣬Ŀǰ���������У��������ٸ�
//�Ȳ�����µĽṹ�壬��������Ľṹ��


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
	//0��ʾObjProp,1��ʾDataProp,2��ʾClass,3��ʾIndividual,4��һ��flag��һ�㲻�᷵�أ�
	//-1��ʾû�ҵ���-2��ʾ������
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
	
	if(mcc[index].sonC == 0)//�ݹ��������
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
	ofstream foutDataProp("DataProp.txt");//����dataprop
	ofstream foutObjProp("ObjProp.txt");//����objectprop
	ofstream foutClass("Class.txt");//����class��������һ����Individual����Ҳ��class�Ĳ��֣��������ļ���ʵû��ʵ�ʵ���;��������������
	ofstream foutIndiv("Individual.txt");//����Individual


	int classCount = 0;//ͳ��һ�����ٸ�Ŀ¼��
	int indivCount = 0;//ͳ��һ�����ٸ�Individual��
	if(!fin)
	{
		cout<<"File not found"<<endl;
		system("pause");
		return -1;
	}	

	string line;
	string sub;	
	

	//���Ȱ����е����ֶ�������
	while(!fin.eof())
	{

		getline(fin,line);


		if(line.length() < 3)
		{
			continue;
		}

		int flag = typeJudgement(line);

		//0��ʾObjProp,1��ʾDataProp,2��ʾClass,3��ʾIndividual,4��һ��flag��һ�㲻�᷵�أ�
		//-1��ʾû�ҵ���-2��ʾ������
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



	//����������ÿ����subclass ofȷ�������ְּ�һ�����ӵ�ָ��

	while(!fin.eof())
	{
		getline(fin,line);
		if( line.find("// Classes") != -1)break;
	}

	while(!fin.eof())
	{

		getline(fin,line);

		if(line.find("// Individuals") != -1)break;//֤���Ѿ�������class����

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
	//�����Ѿ�������class�����νṹ������������Individual
	
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

