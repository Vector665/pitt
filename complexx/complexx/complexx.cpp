// complexx.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"


using namespace std;
#include <iostream>


class MyComplex
{
private:
	double Re, Im;
public:
	MyComplex(double InitRe = 0, double InitIm = 0)
	{
		Re = InitRe;
		Im = InitIm;
	};
	~MyComplex()
	{
		cout << "In Dectructor\n";
	}
	// +, - , *
	friend istream& operator>> (istream& o, MyComplex& b)
	{
		double a, d;
		o >> a >> d;
		b.SetRe(a);
		b.SetIm(d);
		return o;
	}
	friend ostream& operator<< (ostream& o, MyComplex& b)
	{
		o << "Re=" << b.GetRe() << ", Im=" << b.GetIm();
		return o;
	}
	friend MyComplex& operator+ (MyComplex a, MyComplex b)
	{
		MyComplex c;
		c.SetRe(a.GetRe() + b.GetRe()); // c.Re = a.Re + b.Re;
		c.SetIm(a.GetIm() + b.GetIm());
		//cout << c;
		return c;
	}
	friend MyComplex operator+ (MyComplex a, double b)
	{
		MyComplex c;
		c.SetRe(a.GetRe() + b);
		c.SetIm(a.GetIm());
		return c;
	}
	MyComplex& operator= (MyComplex b)
	{
		Re = b.GetRe();
		Im = b.GetIm();
		return(*this);
	}
	friend MyComplex operator+ (double a, MyComplex b)
	{
		return(b + a);
	}

	friend MyComplex operator- (MyComplex a, MyComplex b)
	{
		MyComplex c;
		c.SetRe(a.GetRe() - b.GetRe());
		c.SetIm(a.GetIm() - b.GetIm());
		return c;
	}

	friend MyComplex operator- (MyComplex a, double b)
	{
		MyComplex c;
		c.SetRe(a.GetRe() - b);
		c.SetIm(a.GetIm());
		return c;
	}

	friend MyComplex operator- (double a, MyComplex b)
	{
		MyComplex c;
		c.SetRe(a - b.GetRe());
		c.SetIm(0 - b.GetIm());
		return c;
	}

	friend MyComplex operator* (MyComplex a, MyComplex b)
	{
		MyComplex c;
		double x1 = a.GetRe();
		double x2 = b.GetRe();
		double y1 = a.GetIm();
		double y2 = b.GetIm();
		c.SetRe(x1 * x2 - y1 * y2);
		c.SetIm(x1 * y2 + y1 * x2);
		return c;
	}

	friend MyComplex operator* (MyComplex a, double b)
	{
		MyComplex c;
		c.SetRe(a.GetRe() * b);
		c.SetIm(a.GetIm() * b);
		return c;
	}

	friend MyComplex operator* (double a, MyComplex b)
	{

		return (b * a);
	}

	double GetRe()
	{
		return Re;
	};
	double GetIm()
	{
		return Im;
	};
	int SetRe(double newVal)
	{
		Re = newVal;
		return 1;
	};
	int SetIm(double newVal)
	{
		Im = newVal;
		return 1;
	};
};

int main()
{
	MyComplex A(1, 1), B(1), C(1), D(1, -6), E(6, 2);
	C = 2 * E;
	cout << C;
	C = A + 10.5;
	cout << C;
	cin >> B;
	C = B + A;
	cout << C;
	C = A + B + C + D;
	C = A = B = C;
	cin >> A >> B >> C;
}

