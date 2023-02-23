#pragma once
#include "common.h"

enum { eKorean, eEnglish, eMath, eArt, eMusic, eHistory, eClassSubjectMax};

struct StudentInfo
{
	std::string subject[eClassSubjectMax];
	int scores[eClassSubjectMax];
};
class Student
{
public:
	Student();
	~Student();

	std::string SetstudentName(string student_name);
	std::string Setsubject(string subject, int score, int index);
	int DoCalc();

private:
	StudentInfo studentinfo;
	int Getsum(const int* const pData, int n);
	float GetAvg(const int* const pData, int n);
	int GetMin(const int* const pData, int n);
	int GetMax(const int* const pData, int n);
};

