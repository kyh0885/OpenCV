#include <iostream>
#include <stdio.h>
#include<vector>
#include<string>

typedef unsigned char uchar; //사용자 타입 재지정
typedef unsigned int init;
//struct 기본
/*struct _stData //서로 다른 타입을 묶음
{
	int score;
	double ratio;
	int dated[100];
	int* pPredate = nullptr;
	int* pPostData = nullptr;
	std::vector<int> vLines;

	//함수
	void sum(int& a, int& b)(return a + b;)
		//클래스
	MyClass _myClass;
};

int a;
_stData stData = { 10,0.1,"hello",nullptr ,nullptr };
_stData* pstData = new _stData;//동적으로 만들 수 있다*/
enum {eEnglish, eMath, eKorean, eClassMax}ECLASS; 

//eClassMax 의 장점 - 
struct _stStudentInfo
{
	std::string name[3];
	int scores2[3];


	int scores[eClassMax];
	int sum, average, min, max; //average 만 float
	
	//성적의 합,차,나누기, 곱하기 구하기
	/*int sum1() {

		int sum_score = 0;
		for (size_t i = 0; i < eClassMax; i++) {
			sum_score += scores[i];
	    }return sum_score;

	}

	float average1() {

		int sum_score2 = 0;
		for (size_t i = 0; i < eClassMax; i++)
		{
			sum_score2 += scores[i];
		}
		float average_score = sum_score2 / 3;
		return average_score;
	}

	int min1() {
		int min = scores[0];
		for (size_t i = 0; i < eClassMax; i++)
		{
			if (scores[i] < min) min = scores[i];
		}return min;
	}

	int max1() {
		for (size_t i = 0; i < eClassMax; i++)
		{
			if (scores[i] > max) max = scores[i];
		}return max;
	}*/
	// 교수님 코드 (포인터 이용함)
	/*int sum(const int* const pData, size_t length)
	{
		int sum = 0;
		for (size_t i = 0; i < length; i++)
		{
			sum += pData[i];
		}
		return sum;
	}

	float avg(const int* const pData, size_t length)
	{
		return sum(pData, length) / length;
	}
	int min(const int* const pData, size_t length) {
		int min = pData[0];
		for (size_t i = 0; i < length; i++) {
			if (min > pData[i]) min = pData[i];
		}
		return min;
	}
	int max(const int* const pData, size_t length) {
		int max = pData[0];
		for (size_t i = 0; i < length; i++) {
			if (max < pData[i]) max = pData[i];
		}
		return max;*/
};

int main()
{
	_stStudentInfo student;
	/*student.scores[eEnglish] = 90;
	student.scores[eMath] = 95;
	student.scores[eKorean] = 92;

	std::cout << "English : " << student.scores[0] << std::endl;
	std::cout << "Math : " << student.scores[1] << std::endl;
	std::cout << "Korean : " << student.scores[2] << std::endl;

	std::cout << "Sum : " << student.sum1() << std::endl;
	std::cout << "Average : " << student.average1() << std::endl;
	std::cout << "Min : " << student.min1() << std::endl;
	std::cout << "Max : " << student.max1() << std::endl;*/
	while (1) {
		
		for (size_t i = 0; i < 3; i++)
		{
			std::cin >> student.name[i];
		}

		for (size_t j = 0; j < 3; j++)
		{
			std::cin >> student.scores2[j];
		}

		for (size_t k = 0; k < 3; k++)
		{
			std::cout << student.name[k] << "의 점수는" << student.scores2[k] << "입니다" << std::endl;
		}

		char op;
		std::cin >> op;
		if (op == 'Q') break;
	}
	//교수님 코드
	/*std::vector<_stStudentInfo> vStudent;
	while (true)
	{
		std::cin >> student.name;
		if (student.name == "Q")break;
		std::cin >> student.scores[eEnglish];
		std::cin >> student.scores[eMath];
		std::cin >> student.scores[eKorean];


		vStudent.push_back(student);
	}


	for (size_t i = 0; i < vStudent.size(); i++)
	{
		_stStudentInfo* pStudent = &vStudent[i];

		std::cout << sum(pStudent->scores, eClassMax);
		std::cout << avg(pStudent->scores, eClassMax);
		std::cout << min(pStudent->scores, eClassMax);
		std::cout << max(pStudent->scores, eClassMax);

	}*/
	return 0;
}





