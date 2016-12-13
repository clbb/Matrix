#pragma once
#include<iostream>
#include<vector>
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

//稀疏矩阵
//M*N
//分布无规律 有效数据个数 < 无效数据个数

template <class T>
struct  Triple
{
	int _col;
	int _row;
	T _value;
	Triple(int col = 0,int row = 0 ,T value = T())
		:_col(col)
		,_row(row)//行
		,_value(value)
	{}
};//三元组

template <class T>
class SparseMatrix
{
public:
	SparseMatrix(T* s = NULL,size_t m = 0,size_t n = 0,T invaled = T())
		:_n(n)
		,_m(m)
		,_invaled(invaled)
	{
		for(int i = 0;i<m;++i)
		{
			for(int j = 0;j<n;++j)
			{
				if( s[i*n+j] != invaled) 
				{
				 	Triple<T> t;
					t._col = i;
					t._row = j;
					t._value = s[i*n+j];
					_a.push_back(t);
				//	_a.push_back(new Triple<T>(i,j,s[i*m+j]));
					//_a[i*m+j] = new Triple<T>(i,j,*a);
				}
			}
		}
	}
	//SparseMatrix(SparseMatrix<T>& s)
	//{
	//	_n = s._m;
	//	_m = s._n;
	//	_invaled = s._invaled;
	//	for(int i = 0; i<_a.size();++i)
	//	{
	//		s._a.push_back(_a[i]);
	//	}
	//}
	void Print()
	{
		int index = 0;
		for(int i = 0;i<_m;i++)
		{	
			for(int j = 0; j<_n;++j)
			{
				if((index < _a.size() ) && (_a[index]._row == j  && _a[index]._col == i))
				{
						cout<<_a[index]._value<<" "; 
						index++;
				}
				else
					cout<<_invaled<<" ";
			}
			cout<<endl;
		}
		cout<<endl;
	}
	SparseMatrix<T> Transport()
	{
		SparseMatrix<T> tmp;
		tmp._n = _m;//6
		tmp._m = _n;//5 hang
		tmp._invaled = _invaled;
		tmp._a.reserve(_a.size());
		for(int col = 0; col < tmp._n;++col)//列优先
		{
			for(int index = 0;index<_a.size();++index)
			{
			 	//swap(_a[index]._row,_ a[inde x]._col);
				if(_a[index]._row == col)//列
				{
				 	Triple<T> encode(_a[index]._row,_a[index]._col,_a[index]._value);
					tmp._a.push_back(encode);
				}
			}
		}	
		return tmp;	
	}
	SparseMatrix<T> FastTransport()
	{
		int size = _a.size(); 
		int* RowCount = new int[size];
		memset(RowCount,0,sizeof(int)*_n);
		int* RowStart = new int[size];
		memset(RowStart,0,sizeof(int*)*_n);
		SparseMatrix<T> tmp;
		tmp._n = _m;//6
		tmp._m = _n;//5 hang
		tmp._invaled = _invaled;

		int index = 0;
		for(int i = 0; i<_n;++i)
		{
			while(index < size)
			{
				if(_a[index]._col == i)
					RowCount[_a[index]._col]++;
				++index;
			}

		}
		RowCount[0] = 0;
		for(int i = 1; i<_n;++i)
		{
			RowStart[i] = RowCount[i-1]+RowStart[i-1];
		}
		//
		int jndex = 0;
		tmp._a.reserve(size);
		while(jndex < size)
		{
			size_t begin = RowStart[_a[jndex]._col];
			Triple<T> t(_a[jndex]._row,_a[jndex]._col,_a[jndex]._value);
			tmp._a[begin] = t;
			++RowStart[_a[jndex]._col];
			++jndex;
		}
		delete []RowStart;
		delete []RowCount;
		return tmp;
	}
	void Test()
	{
		for(int i=0;i<_a.size();++i)
		{
			cout<<_a[i]._row<<"+";
			cout<<_a[i]._col<<"+";
			cout<<_a[i]._value<<" ";
		}
		cout<<endl;
		cout<<endl;
	}
protected:
	vector< Triple<T> > _a;
	T _invaled;
	size_t _m;//行
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
//	sm.Print();
	int b[6][5] = { {1,0,3,0,5},
					{0,0,0,0,0}, 
					{0,0,0,0,0},
					{2,0,4,0,6},
					{0,0,0,0,0},
					{0,0,0,0,0},
				  };
	SparseMatrix<int> sm1((int*)b,6,5,0);
	sm1.Print();
	sm1.Test();
	//SparseMatrix<int> sm2 = sm1.Transport();
	SparseMatrix<int> sm2 = sm1.FastTransport();
	sm2.Print();
	sm2.Test();
}
