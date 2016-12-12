#pragma once
#include<iostream>
using namespace std;

//对称矩阵 n*n
//关于对角线对称a[i][j] = a[j][i]，存储下三角
//条件：i>=j
//存成一维数组ar  a[i][j] = ar[i*(i+1)/2+j]

template <class T>
class Matrix
{
public:
	Matrix(T* a,int n)
		:_a(new T[n*(n+1)/2])
		,_n(n)
	{
		int index = 0;
		for(int i = 0; i<n; ++i)
		{
			for(int j = 0; j<n; ++j)
			{
				if(i >= j)
				{
					_a[index] = a[i*n+j];
					index++;
				}
				else
					continue;
			}
		}
	}

	T& Access(int i,int j)
	{
		if(i < j)
		{
			swap(i,j);
		}
		return _a[i*(i+1)/2+j];
	}
	void Print()
	{
		int index = 0;
		for(int i = 0; i<_n; ++i)
		{
			for(int j = 0; j<_n; ++j)
			{
				cout<<Access(i,j)<<" ";
			}
			cout<<endl;
		}
		cout<<endl;
	}
protected:
	T* _a;
	size_t _n;
};

void Testmatrix()
{
	int a[6][5] = { {0,1,2,4,7},
					{1,0,3,5,8},
					{2,3,0,6,9},
					{4,5,6,0,0},
					{7,8,9,0,0},
					{0,0,0,0,0},
				  };
	Matrix<int> sm((int*)a,5);
	sm.Print();
}
