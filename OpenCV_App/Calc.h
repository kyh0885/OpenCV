#pragma once
#include "common.h"

class Calc
{
public:
	//持失切
	Calc();//Ctor...default Ctor
	//Calc(int a=1, int b=2, char sym=' ');
	Calc(int a, int b, char sym);
	//社瑚切
	~Calc();//Dtor

	void Clear();
	void SetValue(int num1, int num2, char sym);
	int GetResult();
	int DoSum();
	int DoMul();
	int DoSub();
	int DoDiv();

	int sum(const int* const pData, size_t length);
	float avg(const int* const pData, size_t length);
	int min(const int* const pData, size_t length);
	int max(const int* const pData, size_t length);

private:
	int number1 = 0;
	int number2 = 0;
	char symbol;
	int result;
};


