// TITLE: Quaternion implementation and test program
// AUTHOR: Matthew Burley.
// DATE: 14/2/2004
#pragma once

#include <stdio.h>
#include <complex>

using namespace std;

class Quaternion
{
private:
	complex<double>* H[2][2];

public:
	Quaternion(void);
	Quaternion(double a, double b, double c, double d);
	Quaternion(complex<double> complexMatrix[2][2]);

	Quaternion* operator*(Quaternion &qRightOperand); // Dot product
	Quaternion* operator*(double fRightOperand); // Product with a scalar
	Quaternion* conjugate(void); // Quaternion conjugate
	double mod(void); // Modulus
	Quaternion* inv(void); // Inverse

	void display(void);

	~Quaternion(void);
};
