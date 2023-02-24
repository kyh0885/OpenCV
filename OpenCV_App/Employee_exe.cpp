#pragma once
#include"Employee.h"

int main()
{
	//Employee e;
	CDate date(2023, 2, 24); 
	{
		Employee e("Parent", "Here", "010-0000-0000", date); 
		e.displayEmployee();
		e.doWork();
	}
	{
		RegularEmployee re("KCCI", "Here", "010-3910-1862", date, 10000000);
		re.displayEmployee();
		//re.doWork();
	}


	/*/e.displayEmployee();
	RegularEmployee re("KCCI", "Here", "010-3910-1862", date, 10000000);
	re.displayEmployee(); //여기안에 부모클래스의 정보가 다 담겨있다



	//pointer...class...derived class...pointerㅠㅠㅠㅠ

	Employee* pEmployee = &e; //int *pA = &a;
	RegularEmployee* pReEmployee = &re;
	//down-Casting -> 기본 클래스가 파생클래스를 가리킨다.
	pEmployee = &re;
	pEmployee->displayEmployee();
	
	e.doWork();
	re.doWork();*/

	return 1;
}