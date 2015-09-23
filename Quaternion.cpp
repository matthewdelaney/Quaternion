// TITLE: Quaternion implementation and test program
// AUTHOR: Matthew Delaney
// DATE: 14/2/2004
#include "Quaternion.h"

int main(void)
{
	double theta; //= 45 * (6.286/360);
	double radTheta;

	// Rotation around the Z-axis
	// Obviously, the final result could be achieved with just one iteration but
	// the intent here is to test with several different angles. The rotations in the
	// following loop are therefore not cumulative
	for(theta = 0; theta < 30; theta++)
	{
		radTheta = theta * (6.286/360); // Convert angle from degrees to radians

		Quaternion* qRotation = new Quaternion(cos(radTheta/2),0,0,sin(radTheta/2)); // Trignometric co-efficients * Z-axis unit vector
		Quaternion* qInvRotation = qRotation->inv();

		Quaternion* qPoint = new Quaternion(0, 2,2,0); // x=2, y=2, z=0

		Quaternion* qResult = *qRotation * *qPoint;
		Quaternion* qFinalResult = *qResult * *qInvRotation;

		qFinalResult->display();
		delete qFinalResult;
		delete qResult;
		delete qPoint;
		delete qInvRotation;
		delete qRotation;
	}

	return 0;
}


Quaternion::Quaternion(void)
{
}

Quaternion::Quaternion(complex<double> complexMatrix[2][2])
{
	for(int x=0; x<2; x++)
	{
		for(int y=0; y<2; y++)
		{
			Quaternion::H[x][y] = new complex<double>(complexMatrix[x][y]);
		}
	}
}


Quaternion::Quaternion(double a, double b, double c, double d)
{
	Quaternion::H[0][0] = new complex<double>(a, b);
	Quaternion::H[0][1] = new complex<double>(c, d);
	Quaternion::H[1][0] = new complex<double>(-c, d);
	Quaternion::H[1][1] = new complex<double>(a, -b);
}

Quaternion* Quaternion::operator*(Quaternion &qRightOperand)
{
	complex<double> temp[2][2];

	temp[0][0] = (*H[0][0] * *qRightOperand.H[0][0]) + (*H[0][1] * *qRightOperand.H[1][0]);
	temp[0][1] = (*H[0][0] * *qRightOperand.H[0][1]) + (*H[0][1] * *qRightOperand.H[1][1]);

	temp[1][0] = (*H[1][0] * *qRightOperand.H[0][0]) + (*H[1][1] * *qRightOperand.H[1][0]);
	temp[1][1] = (*H[1][0] * *qRightOperand.H[0][1]) + (*H[1][1] * *qRightOperand.H[1][1]);

	return new Quaternion(temp);
}


Quaternion* Quaternion::operator*(double fRightOperand)
{
	complex<double> temp[2][2];

	temp[0][0] = *H[0][0] * fRightOperand;
	temp[0][1] = *H[0][1] * fRightOperand;

	temp[1][0] = *H[1][0] * fRightOperand;
	temp[1][1] = *H[1][1] * fRightOperand;

	return new Quaternion(temp);
}


Quaternion* Quaternion::conjugate()
{
	return new Quaternion(H[0][0]->real(), H[0][0]->imag()*-1.0, H[0][1]->real()*-1.0, H[0][1]->imag()*-1.0);
}

double Quaternion::mod(void)
{
	return sqrt(pow(H[0][0]->real(), 2) + pow(H[0][0]->imag(), 2) + pow(H[0][1]->real(), 2) + pow(H[0][1]->imag(), 2));
}

Quaternion* Quaternion::inv(void)
{
	return (*(this->conjugate()) * pow(this->mod(), -2));
}



void Quaternion::display()
{
	printf("(%f, [%f %f %f])\n", H[0][0]->real(), H[0][0]->imag(), H[0][1]->real(), H[0][1]->imag());
}



Quaternion::~Quaternion(void)
{
}
