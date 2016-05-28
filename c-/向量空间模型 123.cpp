#include "stdafx.h"
#include<iostream>
#include<fstream>
#include<string>
#include<algorithm>
#include<cmath>
using namespace std;
struct DictNode
{
	string word;
	float tf_idf[32];
	int tf[32];
	int idf;
	DictNode()
	{
		idf=0;
		for(int i=0;i<32;i++)
		{
			tf_idf[i]=0;
			tf[i]=1;
		}
	}
	DictNode(DictNode& a)
	{
		word=a.word;
		idf=a.idf;
		for(int i=0;i<32;i++)
		{
			tf_idf[i]=a.tf_idf[i];
		}
	}
}dWord[3000];
struct DocScore
{
	float score;
	int docId;
};
int biSearch(string word,int first,int last)
{
	int mid=(first+last)/2;
	if(first>=(last-1))return mid;
	if(word>dWord[mid].word)
	{mid=biSearch(word,mid+1,last); return mid;}
	if(word<dWord[mid].word)
	{mid=biSearch(word,first,mid); return mid;}
	if(word==dWord[mid].word)
		return mid;
}

DocScore Max(DocScore a,DocScore b,DocScore c)
{
	return (a.score>b.score? (a.score>c.score? a:c):(b.score>c.score? b:c));
}
void Swap(DocScore& a,DocScore& b)
{
	DocScore temp=a;
	a=b;
	b=temp;
}
int MaxHeapAdjust(DocScore a[],int mid,int last)
{
	if((mid*2+1)>last)return 0;
	if((mid*2+2)>last)
	{
		if(a[mid].score<a[mid*2+1].score)
		{
			Swap(a[mid],a[mid*2+1]);
		}
		return 0;
	}
	DocScore temp=Max(a[mid],a[mid*2+1],a[mid*2+2]);
	if(a[2*mid+1].score==temp.score)
	{
		Swap(a[mid],a[2*mid+1]);
		MaxHeapAdjust(a,2*mid+1,last);
		return 0;
	}
	if(a[2*mid+2].score==temp.score)
	{
		Swap(a[mid],a[2*mid+2]);
		MaxHeapAdjust(a,2*mid+2,last);
		return 0;
	}
	if(a[mid].score==temp.score)
	{
		return 0;
	}
	return 0;
}
int MaxHeap(DocScore a[],int first,int last)
{
	int mid=(first+last-1)/2;
	if((mid*2+2)>last)
	{
		if(a[mid].score<a[mid*2+1].score)
		{
			Swap(a[mid],a[mid*2+1]);
		}
		mid--;
	}
	while(mid>=first)
	{
		DocScore temp=Max(a[mid],a[2*mid+1],a[2*mid+2]);
		if(a[mid].score==temp.score)
		{
			mid--;
			continue;
		}
		if(a[2*mid+1].score==temp.score)
		{
			Swap(a[mid],a[2*mid+1]);
			MaxHeapAdjust(a,2*mid+1,last);
			mid--;
			continue;
		}
		if(a[2*mid+2].score==temp.score)
		{
			Swap(a[mid],a[2*mid+2]);
			MaxHeapAdjust(a,2*mid+2,last);
			mid--;
			continue;
		}
	}
	return 0;
}
int MaxHeapSort(DocScore a[],int first,int last)
{
	cout<<a[first].score<<"  "<<a[first].docId<<".txt"<<endl;
	if(last==first)return 0;
	Swap(a[first],a[last]);
	MaxHeapAdjust(a,first,last-1);
	return 0;
}

int main()
{
	const string name="name.txt";
	ifstream inName(name);	
	string txtName;
	string word[80];
	int docId=0;
	int docSum=0;
	int wordTotalSum=1;
	dWord[0].word="zzz";
	while(inName>>txtName)
	{
		docSum++;
		ifstream txt;
		int dWordFlag=0;
		txt.open(txtName);
		int wordSum=0;
		while(txt>>word[wordSum])wordSum++;
		sort(word,word+wordSum);

		for(int i=0;i<wordSum;i++)
		{
			int tf=1;
			while((i+1)<wordSum && word[i]==word[i+1]) 
			{
				i++;
				tf++;
			}
			while(dWord[dWordFlag].word<word[i])dWordFlag++;

			if(dWord[dWordFlag].word>word[i])
			{
				for(int j=wordTotalSum;j>dWordFlag;j--)
				{
					dWord[j]=dWord[j-1];
				}
				DictNode a;
				dWord[dWordFlag]=a;
				dWord[dWordFlag].word=word[i];
				dWord[dWordFlag].tf[docId]+=tf;//统计每篇文档中的词项频率
				dWord[dWordFlag].idf+=1;//统计文档频率，每当读入的一片文档中出现这个词自增1
				wordTotalSum++;
				continue;
			}
			if(dWord[dWordFlag].word == word[i])
			{
				dWord[dWordFlag].tf[docId]+=tf;			
				dWord[dWordFlag].idf++;
				continue;
			}
		}
		txt.close();
		docId++;
	}
	float docSIGdi[32];
	for(int i0=0;i0<docSum;i0++)
	{
		docSIGdi[i0]=0;
	}
	// 按照公式计算
	for(int j0=0;j0<wordTotalSum-1;j0++)
	{
		float temp=log10(double (docSum)/double(dWord[j0].idf))+1.0;
		for(int i1=0;i1<docSum;i1++)
		{
			float temp2=1.0+log10 (double(dWord[j0].tf[i1]));
			dWord[j0].tf_idf[i1]= temp2 * temp;
			docSIGdi[i1]+=dWord[j0].tf_idf[i1] * dWord[j0].tf_idf[i1];
		}
	}
	for(int i2=0;i2<docSum;i2++)
	{
		docSIGdi[i2]=sqrt(docSIGdi[i2]);
	}



	//读入query，同时将其作为一篇文档，计算tf*idf
	cout<<"请输入检索词项个数：（不超过15个词）"<<endl;
	int r_wordSum;
	cin>>r_wordSum;
	cout<<"请输入检索词项："<<endl;
	string r_word[15];
	int r_tf[15]={0};
	float r_tf_idf[15];	
	for(int i3=0;i3<r_wordSum;i3++)
		cin>>r_word[i3];
	sort(r_word,r_word+r_wordSum);
	int realNum=0;
	for(int i4=0;i4<r_wordSum;i4++,realNum++)
	{
		int r_tfTemp=1;
		while((i4+1)<r_wordSum && r_word[i4]==r_word[i4+1])
		{
			i4++;
			r_tfTemp++;
		}
		r_word[realNum]=r_word[i4];
		r_tf[realNum]=r_tfTemp;
	}



	//计算结果，评分排序
	DocScore scores[32];
	for(int j1=0;j1<docSum;j1++)
	{
		scores[j1].score=0.0;
		scores[j1].docId=j1+1;
	}
	for(int i5=0;i5<realNum;i5++)
	{
		int flag=biSearch(r_word[i5],0,wordTotalSum);
		if(dWord[flag].word!=r_word[i5]){cout<<"未找到"<<r_word[i5]<<endl; return 0;}
		r_tf_idf[i5]=(1.0+log10 (double (r_tf[i5]))) * (log10(double (docSum+1)/double(dWord[flag].idf+1))+1.0);
		for(int i6=0;i6<docSum;i6++)
		{
			scores[i6].score+=dWord[flag].tf_idf[i6]*r_tf_idf[i5];
		}
	}
	for(int i7=0;i7<docSum;i7++)
	{
		scores[i7].score=scores[i7].score/docSIGdi[i7];
	}



	//采用堆排序，根据输入的数字，决定输出多少
	MaxHeap(scores,0,docSum-1);
	cout<<"请输入输出前多少最佳排名？"<<endl;
	int lastTemp;
	cin>>lastTemp;
	for(int i=0;i<lastTemp;i++)
	{
		MaxHeapSort(scores,0,docSum-1-i);
	}
	system("pause");
	return 0;
}