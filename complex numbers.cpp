#include <iostream>
using namespace std;

class ComplexNumber
{
private:
	int real;
	int imaginary;
public:
	ComplexNumber(int, int); //with default arguments
	~ComplexNumber();
	void Input();
	void Output();
	bool IsEqual(ComplexNumber);
	ComplexNumber Conjugate();
	ComplexNumber Add(ComplexNumber);
	ComplexNumber Subtract(ComplexNumber);
	ComplexNumber Multiplication(ComplexNumber);
	float Magnitude();
};

ComplexNumber::ComplexNumber(int r = 0, int i = 0)
{
	real = r;
	imaginary = i;
}
ComplexNumber::~ComplexNumber(){}

void ComplexNumber::Input()
{
	cout << "Input Real Number:\t";
	cin >> real;
	cout << "Input Imaginary:\t";
	cin >> imaginary;
}

void ComplexNumber::Output()
{
	cout << real;
	if(imaginary>=0)
		cout<<"+" << imaginary << "i\n\n";
	else
		cout << imaginary << "i\n\n";
}

bool ComplexNumber::IsEqual(ComplexNumber i)
{
	if (imaginary == i.imaginary)
		if (real == i.real)
			return true;
		else
			return false;
	else
		return false;
}

ComplexNumber ComplexNumber::Conjugate()
{
	ComplexNumber conjugate(real, imaginary);
	conjugate.imaginary = imaginary * -1;

	return conjugate;
}

ComplexNumber ComplexNumber::Add(ComplexNumber i) 
{
	ComplexNumber add;
	add.real = real + i.real;
	add.imaginary = imaginary + i.imaginary;
	return add;
}

ComplexNumber ComplexNumber::Subtract(ComplexNumber i)
{
	ComplexNumber Subtract;
	Subtract.real = real - i.real;
	Subtract.imaginary = imaginary - i.imaginary;
	return Subtract;
}

ComplexNumber ComplexNumber::Multiplication(ComplexNumber i)
{
	ComplexNumber multiply;
	multiply.real = real * i.real - imaginary * i.imaginary;
	multiply.imaginary = real * i.imaginary + imaginary * i.real;
	return multiply;
}

float ComplexNumber::Magnitude()
{
	float result = 0;
	result = sqrt((real * real) + (imaginary * imaginary));
	return result;
}

int main()
{
	ComplexNumber c1, c2;
	cout << "Enter c1: \n";
	c1.Input();
	cout << "\n\nEnter c2: \n";
	c2.Input();
	

	cout << "\nc1 =  ";
	c1.Output();
	cout << "c2 =  ";
	c2.Output();


	if (c1.IsEqual(c2))
		cout << "c1 is Equal to c2.\n";
	else
		cout << "c1 is NOT Equal to c2.\n\n";

	ComplexNumber conjugateC1 = c1.Conjugate();
	ComplexNumber conjugateC2 = c2.Conjugate();
	cout << "Conjugate of c1:\t";
	conjugateC1.Output();
	cout << "Conjugate of c2:\t";
	conjugateC2.Output();

	ComplexNumber Add = c1.Add(c2);
	ComplexNumber Sub = c1.Subtract(c2);
	ComplexNumber Multi = c1.Multiplication(c2);
	cout << "c1 + c2:\t";
	Add.Output();
	cout << "c1 - c2:\t";
	Sub.Output();
	cout << "c1 * c2:\t";
	Multi.Output();

	float magnitudeOfc1 = c1.Magnitude();
	float magnitudeOfc2 = c2.Magnitude();
	cout << "Magnitude of c1 = " << magnitudeOfc1 << endl << endl;
	cout << "Magnitude of c2 = " << magnitudeOfc2 << endl << endl;

}