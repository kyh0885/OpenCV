#include <iostream>
#include <string>
using namespace std;
class Calc
{
public:
	Calc();
	~Calc();
	int Getsum(const double* const pData, int n);
private:

};

Calc::Calc()
{
	cout << "Calc::Ctor" << endl;
}

Calc::~Calc()
{
	cout << "Calc::Dtor" << endl;
}

int Calc::Getsum(const double* const pData, int n)
{
	int sum = 0;
	for (size_t i = 0; i < n; i++)
	{
		sum += pData[i];
	}
	return sum;
}
int main()
{
	Calc* calc = new Calc();
	double* data = new double[20]{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
	
	cout << "รัวี : " << calc->Getsum(data, 20) << endl;

	if (calc != nullptr)
	{
		delete calc;
		calc = nullptr;

	}

	return 1;
}
