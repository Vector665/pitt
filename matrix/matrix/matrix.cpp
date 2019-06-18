// matrix.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
using namespace std;
#include <iostream>
#include <cstdlib>

class MyArray
{
private:

	double** ptr;
	int CountRow, CountCols;

public:

	int GetCountRow()
	{
		return CountRow;
	}

	int GetCountCols()
	{
		return CountCols;
	}

	double** GetPtr()
	{
		return ptr;
	}

	bool SetCountRow(int NewCountRow)
	{
		return (CountRow = NewCountRow);
	}

	bool SetCountCols(int NewCountCols)
	{
		return (CountCols = NewCountCols);
	}

	bool SetPtr(double** newptr, int NewCountRow, int NewCountCols)
	{
		for (int i = 0; i < CountRow; i++)
			delete ptr[i];
		delete ptr;
		return (ptr = newptr) && (CountRow = NewCountRow) && (CountCols = NewCountCols);
	}

	bool SetElement(int IndexRow, int IndexCols, double Value)
	{
		return ptr[IndexRow][IndexCols] = Value;
	}

	double GetElement(int IndexRow, int IndexCols)
	{
		return ptr[IndexRow][IndexCols];
	}

	MyArray()
	{
		ptr = new double*[1];
		if (ptr == NULL)
		{
			exit(0);
		}

		ptr[0] = new double[0];
		if (ptr[0] == NULL)
		{
			delete ptr;
			exit(0);
		}
		CountRow = 1;
		CountCols = 0;
	}

	MyArray(int NewCountRow, int NewCountCols)
	{
		ptr = new double*[NewCountRow];
		if (ptr == NULL)
		{
			exit(0);
		}
		for (int i = 0; i < NewCountRow; i++)
		{
			ptr[i] = new double[NewCountCols];
			if (ptr[i] == NULL)
			{
				for (int j = 0; j < i; j++)
					delete ptr[j];
				delete ptr;
				exit(0);
			}
			for (int j = 0; j < NewCountCols; j++)
				ptr[i][j] = 0;
		}
		CountRow = NewCountRow;
		CountCols = NewCountCols;
	}

	MyArray(int NewCountRow, int NewCountCols, double NewValue)
	{
		ptr = new double*[NewCountRow];
		if (ptr == NULL)
		{
			exit(0);
		}
		for (int i = 0; i < NewCountRow; i++)
		{
			ptr[i] = new double[NewCountCols];
			if (ptr[i] == NULL)
			{
				for (int j = 0; j < i; j++)
					delete ptr[j];
				delete ptr;
				exit(0);
			}
			for (int j = 0; j < NewCountCols; j++)
				ptr[i][j] = NewValue;
		}
		CountRow = NewCountRow;
		CountCols = NewCountCols;
	}


	~MyArray()
	{
		//		cout << "~\n";
	}

	friend MyArray& operator+ (MyArray a, MyArray b)
	{
		if (a.GetCountCols() != b.GetCountCols() || a.GetCountRow() != b.GetCountRow())
		{
			cout << "Can't do it :(\n";
			return a;
		}

		MyArray c;
		int cr = a.GetCountRow(), cc = a.GetCountCols();
		double** tmpC = new double*[cr], ** tmpA = a.GetPtr(), ** tmpB = b.GetPtr();
		for (int i = 0; i < cr; i++)
		{
			tmpC[i] = new double[cc];
			for (int j = 0; j < cc; j++)
				tmpC[i][j] = tmpA[i][j] + tmpB[i][j];
		}
		c.SetPtr(tmpC, cr, cc);
		return c;
	}

	friend MyArray& operator+ (MyArray a, double b)
	{
		MyArray c;
		int cr = a.GetCountRow(), cc = a.GetCountCols();
		double** tmpC = new double*[cr], ** tmpA = a.GetPtr();
		for (int i = 0; i < cr; i++)
		{
			tmpC[i] = new double[cc];
			for (int j = 0; j < cc; j++)
				tmpC[i][j] = tmpA[i][j] + b;
		}
		c.SetPtr(tmpC, cr, cc);
		return c;
	}

	friend MyArray& operator+ (double b, MyArray a)
	{
		return (a + b);
	}

	friend MyArray& operator- (MyArray a, MyArray b)
	{
		if (a.GetCountCols() != b.GetCountCols() || a.GetCountRow() != b.GetCountRow())
		{
			cout << "Can't do it :(\n";
			return a;
		}

		MyArray c;
		int cr = a.GetCountRow(), cc = a.GetCountCols();
		double** tmpC = new double*[cr], ** tmpA = a.GetPtr(), ** tmpB = b.GetPtr();
		for (int i = 0; i < cr; i++)
		{
			tmpC[i] = new double[cc];
			for (int j = 0; j < cc; j++)
				tmpC[i][j] = tmpA[i][j] - tmpB[i][j];
		}
		c.SetPtr(tmpC, cr, cc);
		return c;
	}

	friend MyArray& operator- (MyArray a)
	{
		MyArray c;
		int cr = a.GetCountRow(), cc = a.GetCountCols();
		double** tmpC = new double*[cr], ** tmpA = a.GetPtr();
		for (int i = 0; i < cr; i++)
		{
			tmpC[i] = new double[cc];
			for (int j = 0; j < cc; j++)
				tmpC[i][j] = -tmpA[i][j];
		}
		c.SetPtr(tmpC, cr, cc);
		return c;
	}

	friend MyArray& operator- (MyArray a, double b)
	{
		MyArray c;
		int cr = a.GetCountRow(), cc = a.GetCountCols();
		double** tmpC = new double*[cr], ** tmpA = a.GetPtr();
		for (int i = 0; i < cr; i++)
		{
			tmpC[i] = new double[cc];
			for (int j = 0; j < cc; j++)
				tmpC[i][j] = tmpA[i][j] - b;
		}
		c.SetPtr(tmpC, cr, cc);
		return c;
	}

	friend MyArray& operator- (double b, MyArray a)
	{
		return (-a + b);
	}

	friend MyArray& operator* (MyArray a, double b)
	{
		MyArray c;
		int cr = a.GetCountRow(), cc = a.GetCountCols();
		double** tmpC = new double*[cr], ** tmpA = a.GetPtr();
		for (int i = 0; i < cr; i++)
		{
			tmpC[i] = new double[cc];
			for (int j = 0; j < cc; j++)
				tmpC[i][j] = tmpA[i][j] * b;
		}
		c.SetPtr(tmpC, cr, cc);
		return c;

	}

	friend MyArray& operator* (double b, MyArray a)
	{
		return (a * b);
	}

	friend MyArray& operator* (MyArray a, MyArray b)
	{
		if (a.GetCountCols() != b.GetCountRow())
		{
			cout << "Can't do it :(\n";
			return a;
		}

		MyArray c;
		int cr = a.GetCountRow(), cc = b.GetCountCols(), K = a.GetCountCols(), tmp;
		double** tmpC = new double*[cr], ** tmpA = a.GetPtr(), ** tmpB = b.GetPtr();
		for (int i = 0; i < cr; i++)
		{
			tmpC[i] = new double[cc];
			for (int j = 0; j < cc; j++)
			{
				tmp = 0;
				for (int k = 0; k < K; k++)
					tmp += tmpA[i][k] * tmpB[k][j];
				tmpC[i][j] = tmp;
			}

		}
		c.SetPtr(tmpC, cr, cc);
		return c;
	}

	friend MyArray& operator/ (MyArray a, double b)
	{
		return(a * (1 / b));
	}

	MyArray& operator= (MyArray a)
	{
		CountRow = a.GetCountRow();
		CountCols = a.GetCountCols();
		ptr = new double*[CountRow];
		double** tmp = a.GetPtr();
		for (int i = 0; i < CountRow; i++)
		{
			ptr[i] = new double[CountCols];
			for (int j = 0; j < CountCols; j++)
				ptr[i][j] = tmp[i][j];
		}
		return(*this);
	}

	friend bool operator== (MyArray a, MyArray b)
	{
		if (a.GetCountCols() != b.GetCountCols() || a.GetCountRow() != b.GetCountRow())
			return false;
		int cr = a.GetCountRow(), cc = a.GetCountCols();
		double** tmpA = a.GetPtr(), ** tmpB = b.GetPtr();
		for (int i = 0; i < cr; i++)
		for (int j = 0; j < cc; j++)
		if (tmpA[i][j] != tmpB[i][j])
			return false;
		return true;
	}

	friend ostream& operator<< (ostream& o, MyArray& a)
	{
		if (a.GetCountCols() < 1 || a.GetCountRow() < 1)
		{
			o << "NULL\n";
			return o;
		}

		int Row = a.GetCountRow(), Cols = a.GetCountCols() - 1;
		double** buf = a.GetPtr();
		for (int i = 0; i < Cols; i++)
			o << "---";
		o << "-\n";
		for (int i = 0; i < Row; i++)
		{
			for (int j = 0; j < Cols; j++)
				o << buf[i][j] << ", ";
			o << buf[i][Cols] << "\n";
		}
		for (int i = 0; i < Cols; i++)
			o << "---";
		o << "-\n";
		return o;
	}

	friend istream& operator>> (istream& o, MyArray& a)
	{
		int r, c;
		cout << "Enter the number of rows: ";
		o >> r;
		cout << "\nEnter the number of columns: ";
		o >> c;
		if (r < 1 || c < 1)
			exit(0);
		double** tmp = new double*[r];
		for (int i = 0; i < r; i++)
		{
			cout << "\n";
			tmp[i] = new double[c];
			for (int j = 0; j < c; j++)
				o >> tmp[i][j];
		}
		a.SetPtr(tmp, r, c);
		return o;
	}

	MyArray(MyArray& a) {
		int i, j;
		ptr = new double*[a.GetCountRow()];
		if (ptr == NULL)
		{
			exit(0);
		}
		for (i = 0; i < a.GetCountRow(); i++) {
			ptr[i] = new double[a.GetCountCols()];
			if (ptr[i] == NULL)
			{
				for (j = 0; j < i; j++)
					delete ptr[j];
				delete ptr;
				exit(0);
			}
		}
		CountRow = a.GetCountRow();
		CountCols = a.GetCountCols();
		for (i = 0; i < CountRow; i++)
		for (j = 0; j < CountCols; j++)
			ptr[i][j] = a.GetElement(i, j);
	}


};

int main()
{
	MyArray a(10, 4, 1), b(a), c, e(150, 100), d(100, 200);
	cout << a;
	cout << b;
	cout << c;
	cout << "\n";
	system("pause");
}


