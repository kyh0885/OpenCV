#pragma once

#include "StudentScore.h"

Student::Student()
{
	cout << "StudentScore::Ctor" << endl;
}

Student::~Student()
{
	cout << "StudentScore::Dtor" << endl;
}

std::string Student::SetstudentName(string student_name)
{
	cout << student_name <<"의 성적은 " << endl;
	return std::string();
}


std::string Student::Setsubject(string subject, int score, int index)
{
	studentinfo.subject[index] = subject;
	studentinfo.scores[index] = score;
	cout << studentinfo.subject[index] << ":" << studentinfo.scores[index] << " 이며" << endl;
	return std::string();

}


int Student::DoCalc()
{	
	cout << "총합은" << Getsum(studentinfo.scores, eClassSubjectMax) << "입니다" << endl;
	cout << "평균은" << GetAvg(studentinfo.scores, eClassSubjectMax) << "입니다" << endl;
	cout << "최소는" << GetMin(studentinfo.scores, eClassSubjectMax) << "입니다" << endl;
	cout << "최대는" << GetMax(studentinfo.scores, eClassSubjectMax) << "입니다" << endl;

	return 0;
}

//함수
int Student::Getsum(const int* const pData, int n) {
	int sum = 0;
	for (size_t i = 0; i < n; i++)
	{
		sum += pData[i];
	}
	return sum;
}

float Student::GetAvg(const int* const pData, int n)
{
	return Getsum(pData, n) / n;
}

int Student::GetMin(const int* const pData, int n) {
	int min = pData[0];
	for (size_t i = 0; i < n; i++) {
		if (min > pData[i]) min = pData[i];
	}
	return min;
}
int Student::GetMax(const int* const pData, int n) {
	int max = pData[0];
	for (size_t i = 0; i < n; i++) {
		if (max < pData[i]) max = pData[i];
	}
	return max;
}
