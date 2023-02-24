#pragma once
#include "common.h"

class CDate //가장 작은 단위의 class
{
public : 
	CDate() { year = month = day = 0; };
	CDate(int _year, int _month, int _day )
	{
		year = _year, month = _month, day = _day; //초기화 
	};
	~CDate() {}
	int GetYear() { return year; } //외부로 나갈 수 있는 애들
	int GetMonth() { return month; }
	int GetDay() { return day; }


private: 
	int year, month, day;

};
class Employee
{
public:
	Employee();
	Employee(string name,string address, string phoneNum,CDate joinDate);
	void displayEmployee();
	void doWork();
	~Employee();
	
protected: //자신을 상속하는 클래스까지만 접근 가능(접근지정자가 하는 역할)	
private:
	string name,address, phoneNum; 
	CDate joinDate; //입사일
};



class RegularEmployee : public Employee //Regular는 Employee로부터 상속받았다
{
public:
	RegularEmployee();
	RegularEmployee(string name, string address, string phoneNum, CDate joinDate, int salary);
	~RegularEmployee();
	void doWork();
private:
	int salary; //사실상 자식은 이거 하나 가지고있음
};

