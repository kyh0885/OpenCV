#include "Calc.h"

//Calc::Calc()
//	: number1(0)//member inintilizer
//	, number2(0)
//	, symbol(' ')
//	, result(0)
//{
//	cout << "Calc::Ctor" << endl;
//}
Calc::Calc()
	: Calc(1, 1, ' ')//위임생성자
{
	cout << "Calc::Ctor1" << endl;
}

Calc::Calc(int a, int b, char sym)
	: number1(a)//member inintilizer-> 생성과 동시에 초기화
	, number2(b)
	, symbol(sym)
	, result(0)
{
	cout << "Calc::Ctor2" << endl; //디스플레이하기전에 멤버초기화함
	this->a = a;
	this->b = b;
	this->sym;

	pData = new int[100];
}

Calc::~Calc()
{
	cout << "Calc::Dtor" << endl;

	if (pData != nullptr) 
	{
		delete[] pData;
		pData = nullptr;
	}
}
void Calc::Clear()
{
	number1 = 0;
	number2 = 0;
	symbol = ' ';
	result = 0;
}
void Calc::SetValue(int num1, int num2, char sym)
{
	number1 = num1;
	number2 = num2;
	symbol = sym;
}
int Calc::DoSum()
{
	result = number1 + number2;
	return result;
}
int Calc::DoMul()
{
	result = number1 * number2;
	return result;
}
int Calc::DoSub()
{
	result = number1 - number2;
	return result;
}
int Calc::DoDiv()
{
	result = number1 / number2;
	return result;
}

int Calc::GetResult()
{
	return result;
}
int Calc::sum(const int* const pData, size_t length)
{
	int sum = 0;
	for (size_t i = 0; i < length; i++) {
		sum += pData[i];
	}
	result = sum;
	return sum;
}

float Calc::avg(const int* const pData, size_t length) {
	result = sum(pData, length) / length;
	return result;
}
int Calc::min(const int* const pData, size_t length) {
	int min = pData[0];
	for (size_t i = 0; i < length; i++) {
		if (min > pData[i]) min = pData[i];
	}
	result = min;
	return min;
}
int Calc::max(const int* const pData, size_t length) {
	int max = pData[0];
	for (size_t i = 0; i < length; i++) {
		if (max < pData[i]) max = pData[i];
	}
	result = max;
	return max;
}