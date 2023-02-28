#include "Calc.h"

Calc calc_global; // 전역변수..프로그램 시작/종료시  calc 생성,소멸 

int main()
{
	if (true)
	{
		Calc calc;
		calc.Clear();
		//calc.SetValue(1, 2, '+');
		int data[3] = { 1,2,3 };
		calc.sum(data, 3);
		cout << "합은 " << calc.GetResult() << endl;
		calc.Clear();
		calc.SetValue(1, 2, '+');
		calc.DoSum();
		cout << "합은 " << calc.GetResult() << endl;
	}

	if (false)
	{
		Calc* pCalc = new Calc();

		int data[3] = { 1,2,3 };
		pCalc->sum(data, 3);
		cout << "합은 " << pCalc->GetResult() << endl;
		pCalc->Clear();
		pCalc->SetValue(1, 2, '+');
		pCalc->DoSum();
		cout << "합은 " << pCalc->GetResult() << endl;

		//return 1;

		if (pCalc != nullptr)
		{
			delete pCalc;
			pCalc = nullptr;
		}
	}

	{
		//smart pointer
		//Calc* pCalc = new Calc();
		std::shared_ptr<Calc> pCalc = std::make_shared<Calc>(1, 1, '+');

		int data[3] = { 1,2,3 };
		pCalc->sum(data, 3);
		cout << "합은 " << pCalc->GetResult() << endl;
		pCalc->Clear();
		pCalc->SetValue(1, 2, '+');
		pCalc->DoSum();
		cout << "합은 " << pCalc->GetResult() << endl;

	}

	return 1;
}
