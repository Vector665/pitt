// vector.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"


// ConsoleApplication2.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"


using namespace std;
#include <iostream>
#include <sstream>
#include <cstdlib>
double StringToDouble(const string& s)
{
	istringstream i(s);
	double x;
	if (!(i >> x))
		return 0;
	return x;
}

bool StringToDoubleCheck(const string& s)
{
	istringstream i(s);
	double x;
	if (!(i >> x))
		return false;
	return true;
}

class vector
{
private:

	double* ptr;
	int cnt;

public:

	int GetCnt()
	{
		return cnt;
	}

	void SetCnt(int newCnt)
	{
		cnt = newCnt;
	}

	double* GetPtr()
	{
		return ptr;
	}

	void SetPtr(double* newptr)
	{
		ptr = newptr;
	}

	//		vector(vector& a);

	vector(int CountElem)
	{
		ptr = new double[CountElem];
		//			if (ptr == NULL)
		//				Exeption;
		cnt = CountElem;
	}

	vector()
	{
		ptr = new double[0];
		//			if (ptr == NULL)
		//				Exeption;
		cnt = 0;
	}

	friend ostream& operator<< (ostream& o, vector& a)
	{
		if (a.GetCnt() < 1)
		{
			o << "NULL";
			return o;
		}

		int n = a.GetCnt() - 1;
		double* buf = a.GetPtr();
		for (int i = 0; i < n; i++)
			o << buf[i] << ", ";
		o << buf[n];
		return o;
	}

	friend istream& operator>> (istream& o, vector& a)
	{
		double* p = new double[0];
		a.SetCnt(0);
		a.SetPtr(p);
		string b;

		for (o >> b; StringToDoubleCheck(b); o >> b)
			a.addElement(StringToDouble(b));

		return o;

	}

	friend vector& operator+ (vector a, vector b)
	{
		vector c;
		int n = b.GetCnt(), N = a.GetCnt();
		double* A = a.GetPtr(), *B = b.GetPtr();
		if (a.GetCnt() < b.GetCnt())
		{
			n = a.GetCnt();
			N = b.GetCnt();
			A = b.GetPtr();
			B = a.GetPtr();
		}

		for (int i = 0; i < n; i++)
			c.addElement(A[i] + B[i]);

		for (int i = n; i < N; i++)
			c.addElement(A[i]);

		c.SetCnt(N);
		return c;
	}

	friend vector& operator- (vector a, vector b)
	{
		vector c;
		double *tmp, *tmpC;
		int na = a.GetCnt(), nb = b.GetCnt();
		if (na < nb)
		{
			c = b;
			c.SetCnt(nb);
			tmp = a.GetPtr();
			tmpC = c.GetPtr();

			for (int i = 0; i < na; i++)
				tmpC[i] = tmp[i] - tmpC[i];

			for (int i = na; i < nb; i++)
				tmpC[i] = -tmpC[i];
		}
		else
		{
			c = a;
			c.SetCnt(na);
			tmp = b.GetPtr();
			tmpC = c.GetPtr();

			for (int i = 0; i < nb; i++)
				tmpC[i] -= tmp[i];

		}
		return c;
	}

	friend vector& operator* (vector& a, vector& b)
	{
		vector c;
		double* tmp, *tmpC;
		int na = a.GetCnt(), nb = b.GetCnt();
		if (na < nb)
		{
			c = a;
			c.SetCnt(na);
			tmp = b.GetPtr();
			tmpC = c.GetPtr();

			for (int i = 0; i < na; i++)
				tmpC[i] *= tmp[i];
		}
		else
		{
			c = b;
			c.SetCnt(nb);
			tmp = a.GetPtr();
			tmpC = c.GetPtr();

			for (int i = 0; i < nb; i++)
				tmpC[i] *= tmp[i];

		}
		return c;
	}

	friend vector& operator/ (vector& a, vector& b)
	{
		vector c;
		double* tmp, *tmpC;
		int na = a.GetCnt(), nb = b.GetCnt();
		if (na < nb)
		{
			c = a;
			c.SetCnt(na);
			tmp = b.GetPtr();
			tmpC = c.GetPtr();

			for (int i = 0; i < na; i++)
				tmpC[i] /= tmp[i];
		}
		else
		{
			c = b;
			c.SetCnt(nb);
			tmp = a.GetPtr();
			tmpC = c.GetPtr();

			for (int i = 0; i < nb; i++)
				tmpC[i] = tmp[i] / tmpC[i];

		}
		return c;
	}

	friend vector& operator+ (vector& a, double b)
	{
		int n = a.GetCnt();
		vector c = a;
		double* tmp = c.GetPtr();
		for (int i = 0; i < n; i++)
			tmp[i] += b;
		return c;
	}

	friend vector& operator+ (double b, vector& a)
	{
		return a + b;
	}

	friend vector& operator- (vector& a, int b)
	{
		vector c = a;
		c.delElement(b);
		return c;
	}

	friend vector& operator* (vector& a, double b)
	{
		int n = a.GetCnt();
		vector c = a;
		double* tmp = c.GetPtr();
		for (int i = 0; i < n; i++)
			tmp[i] *= b;
		return c;
	}

	friend vector& operator* (double b, vector& a)
	{
		return a * b;
	}

	vector& operator= (vector b)
	{
		cnt = b.GetCnt();
		ptr = new double[cnt];
		double* tmp = b.GetPtr();
		for (int i = 0; i < cnt; i++)
			ptr[i] = tmp[i];
		return(*this);
	}


	int addElement(double newElement)
	{

		double* tmp = new double[cnt + 1];
		if (tmp == NULL)
			return 0;
		for (int i = 0; i < cnt; i++)
			tmp[i] = ptr[i];
		tmp[cnt] = newElement;
		delete ptr;
		cnt++;
		ptr = tmp;
		return 1;
	}

	int delElement(int indexDelElement)
	{

		double* tmp;
		int i;
		tmp = new double[cnt - 1];
		if (tmp == NULL)
			return 0;
		for (i = 0; i < indexDelElement; i++)
			tmp[i] = ptr[i];
		for (i = indexDelElement + 1; i < cnt; i++)
			tmp[i - 1] = ptr[i];
		delete ptr;
		cnt--;
		ptr = tmp;
		return 1;
		system("pause");
	}

};

int main()
{
	vector g, h, p;
	g.addElement(22);
	g.addElement(5);
	h.addElement(12);
	h.addElement(8);
	h.addElement(3);
	h.addElement(12);
	p = g + h;
	p = 2 * p;
	cout << p;
	cout << '\n';
	cout << p.GetCnt();
	system("pause");
}




