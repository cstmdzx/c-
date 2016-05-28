// RecSys.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <string>
#include <algorithm>
using namespace std;


struct Top
{
	int id;
	float score;
};

//����item��score�Ľṹ��
struct IandS
{
	int item;
	int score;
};

struct User
{
	int id;
	int num;
	
	IandS* is;
	//ȡǰ10�������Ƶ�������������id�͵÷�
	Top top[10];
	float length;//��¼score������ģ����ÿ�μ����ֱ��ʹ��
	int mean;//�������Ԥ�����ֵΪ���Ļ�֮��ģ������Ҫ���Ͼ�ֵ
	User()
	{
		is = NULL;
		length = 0.0;
	}
}user[15];

bool cmpT(Top a ,Top b)
{
	return a.score > b.score;
}

bool cmpIS(IandS a, IandS b)
{
	return a.item < b.item;
}

int myMax(int a, int b)
{
	if(a > b)return a;
	else return b;
}

int mySwap(Top &a, Top &b)
{
	Top temp;
	temp.id = a.id;	temp.score = a.score;
	a.id = b.id; a.score = b.score;
	b.id = temp.id; b.score = temp.score;
	return 0;
	
}

float s[15][15]={1.1};

int _tmain(int argc, _TCHAR* argv[])
{
	fstream fin("train1.txt");
	if(!fin)cout<<"�򿪴���"<<endl;
	string raw;
	int numOfUser = 0;
	int maxNumOfItem = 0;

	while(!fin.eof())
	{

		getline(fin,raw);
		if(raw.empty())break;
		int pos = raw.find('|');
		int uid = atoi(raw.substr(0,pos).c_str());
		user[uid].id = uid;
        int num = atoi(raw.substr(pos+1).c_str());
		user[uid].num = num;
		user[uid].is = (IandS *)malloc(num * sizeof(IandS));

//		cout<<uid<<"	"<<num<<endl;
//		int item,rate;
		maxNumOfItem = myMax(num,maxNumOfItem);
		int mean = 0;//ͳ�ƾ�ֵ
		for (int i = 0;i < num; i++)
		{
			fin>>user[uid].is[i].item>>user[uid].is[i].score;
//			cout<<item<<"	"<<rate<<endl;
			mean += user[uid].is[i].score;
		}
		sort(user[uid].is, user[uid].is + num ,cmpIS);		

		//���Ļ�
		mean = mean / user[uid].num;
		for (int i = 0; i < num; i++)
		{
			user[uid].is[i].score -= mean;
			if(user[uid].is[i].score == 0)
				user[uid].is[i].score = 1;
			user[uid].length += user[uid].is[i].score * user[uid].is[i].score;
		}
		user[uid].mean = mean;
		//����ģ
		user[uid].length = sqrt(user[uid].length);
		numOfUser++;
		getline(fin,raw);
//		cout<<uid<<endl;

	}

	cout<<numOfUser<<"	"<<maxNumOfItem<<endl;

	//ѵ����������top10
	for (int i = 0; i < numOfUser; i++)
	{
		for (int j = 0; j < numOfUser; j++)
		{
			int flag1 = 0, flag2 = 0;
			int sum = 0;
			//������ƶ�֮�������������ټ���
			if(i > j)
			{
				if(j < 10)
				{
					user[i].top[j].id = j;
					user[i].top[j].score = s[i][j];
				}
				if(j == 9)//����С��ð�ݵ���β������б���С�Ĵ���һ�������С�Ķ���
				{
					for(int k = 0; k < 9; k++)
					{
						if(user[i].top[k].score < user[i].top[k + 1].score)
						{
							mySwap(user[i].top[k], user[i].top[k + 1]);
						}

					}
				}
				if(j > 9)
				{
					if(s[i][j] > user[i].top[9].score)//����滻������ð������
					{
						user[i].top[9].score = s[i][j];
						user[i].top[9].id = user[j].id;
						for(int k = 0; k < 9; k++)
						{
							if(user[i].top[k].score < user[i].top[k + 1].score)
							{
								mySwap(user[i].top[k], user[i].top[k + 1]);
							}
						}
					}
				}
				cout<<user[i].id<<"	"<<user[j].id<<"	"<<s[i][j]<<endl;
				continue;
			}
			//�����ڻ�
			while(flag1 < user[i].num && flag2 < user[j].num)
			{

				if (user[i].is[flag1].item == user[j].is[flag2].item)
				{
					sum += user[i].is[flag1].score * user[j].is[flag2].score;
					flag1++;flag2++;
					continue;
				}
				if (user[i].is[flag1].item > user[j].is[flag2].item)
				{
					flag2++;
					continue;
				}
				if (user[i].is[flag1].item < user[j].is[flag2].item)
				{
					flag1++;
					continue;
				}
			}
			s[i][j] = s[j][i] = sum /(user[i].length * user[j].length);
			if(j < 10)
			{
				user[i].top[j].id = j;
				user[i].top[j].score = s[i][j];
			}
			if(j == 9)//����С��ð�ݵ���β������б���С�Ĵ���һ�������С�Ķ���
			{
				for(int k = 0; k < 9; k++)
				{
					if(user[i].top[k].score < user[i].top[k + 1].score)
					{
						mySwap(user[i].top[k], user[i].top[k + 1]);
					}

				}
			}
			if(j > 9)
			{
				if(s[i][j] > user[i].top[9].score)//����滻������ð������
				{
					user[i].top[9].score = s[i][j];
					user[i].top[9].id = user[j].id;
					for(int k = 0; k < 9; k++)
					{
						if(user[i].top[k].score < user[i].top[k + 1].score)
						{
							mySwap(user[i].top[k], user[i].top[k + 1]);
						}
					}
				}
			}

			cout<<user[i].id<<"	"<<user[j].id<<"	"<<s[i][j]<<endl;
		}
	}

//	cout<<user[5846].id<<"	"<<user[5846].num<<"	"<<user[5846].item[user[5846].num-1]<<"	"<<user[5846].score[user[5846].num-1]<<endl;
	fin.close();

//��ȡ���Լ�
	ifstream fint("test1.txt");
	ofstream fout("result.txt");

	while(!fint.eof())
	{

		getline(fint,raw);
		if(raw.empty())break;
		int pos = raw.find('|');
		int uid = atoi(raw.substr(0,pos).c_str());
        int num = atoi(raw.substr(pos+1).c_str());
		int item;
		float recScore = 0.0;
		float totalScore = 0.0;
		fout<<uid<<'|'<<num<<endl;

		for (int i = 0;i < num; i++)
		{
			fint>>item;
			float recScore = 0.0;
			float totalScore = 0.0;
			for(int j = 0; j <10; j++)
			{
				int index = user[uid].top[j].id;//ȡ������ǰʮ��id
				if(index == uid)continue;
				int border = user[index].num;
				totalScore += user[uid].top[j].score;
				for(int k = 0; k < border; k++)
				{
					if(item == user[index].is[k].item)
					{
						recScore += user[uid].top[j].score * (user[index].is[k].score );
						break;
					}
					if(item < user[index].is[k].item )
					{
//						recScore += 0;
						break;
					}

				}
			}
			recScore = recScore / totalScore + user[uid].mean;
			fout<<item<<"	"<<recScore<<endl;
//			cout<<item<<"	"<<rate<<endl;

		}
		

		getline(fint,raw);

	}
	fint.close();
	fout.close();

	system("pause");
	return 0;
}

