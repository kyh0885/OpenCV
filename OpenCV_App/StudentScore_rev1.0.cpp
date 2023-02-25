#include "StudentScore_rev1.0.h"

StudentScore::StudentScore()
{
}

StudentScore::~StudentScore()
{
}

void StudentScore::SetStudentName(string Name)
{
	stStudentInfo.name = Name;
	stStudentInfo.mTable.clear();
	stStudentInfo.avg = 0.0;
	stStudentInfo.sum = 0;
	stStudentInfo.min = 0;
	stStudentInfo.max = 0;
}

void StudentScore::SetSubjectScore(string subject, int score)
{
	string str = subject;
	//c-style
	/*for (size_t i = 0; i < str.size(); i++) 
	{
		str[i] = std::toupper(str[i]);
	}*/
	//c++ lambda style
	std::transform(str.begin(), str.end(), str.begin(),
		[](unsigned char c) { return toupper(c); });
	//if (str == "KOR") stStudentInfo.kor = score;
	//else if (str == "ENG") stStudentInfo.eng = score;
	//else if (str == "MATH") stStudentInfo.math = score;
	//else
	//	cout << "Subject {Kor, Eng, Math} Only" << endl;

	if (stStudentInfo.mTable.find(subject) != stStudentInfo.mTable.end())
	{
		cout << "same subject found" << endl;
		return;
	}

	stStudentInfo.mTable.insert({ subject, score });
}

void StudentScore::DoCalc()
{
	//홍길동 = 국어:90, 영어 : 90, 수학 : 98, 미술 : 88, 음악 : 94, 역사 : 99총합 = ? ? , 평균 = ? ? , 최소 = ? ? , 최대 = ? ?

	cout << stStudentInfo.name << " => ";

	string strSubjectReport;
	for (auto iter = stStudentInfo.mTable.begin();iter != stStudentInfo.mTable.end();iter++) //end()가 아닐때까지 찾기 
	{
		strSubjectReport += iter->first;
		strSubjectReport += " : ";
		strSubjectReport += std::to_string(iter->second);
		strSubjectReport += " ";
	}
	cout << strSubjectReport << "\t"
	<< "| 총합 : " << GetSum() << "\t"
	<< "| 평균 : " << GetAvg() << "\t"
	<< "| 최소 : " << GetMin() << "\t"
	<< "| 최대 : " << GetMax()
	<< endl;


}

int StudentScore::GetSum()
{
	//return (stStudentInfo.kor+stStudentInfo.eng+stStudentInfo.math);
	int sum = 0;
	//using map {key, value}
	//values
	//vector<pair<int, int>> v;
	vector<int> vScores;
	for (auto iter = stStudentInfo.mTable.begin();
		iter != stStudentInfo.mTable.end();
		iter++)
	{
		iter->first;//key:string
		iter->second;//value:int
		//sum = sum + iter->second;
		vScores.push_back(iter->second); //value의 값을 요소에 추가(push back 을통하여서)
	}
	//*(addres++)
	//address[i++]
	//int a = 10;			auto b = 10;//int 
	//auto c = "abc";
	for (auto iter = vScores.begin(); iter != vScores.end(); iter++)
	{
		sum += (*iter);//value, iter::pointer address
	}

	return sum;
}

float StudentScore::GetAvg()
{
	//return GetSum()/3.0;
	return GetSum() / stStudentInfo.mTable.size();
}

int StudentScore::GetMin()
{
	//int score[3] = { stStudentInfo.kor,
	//stStudentInfo.eng,stStudentInfo.math };
	//std::sort(score, score + 3);
	//return score[0];
	vector<int> vScores;
	for (auto iter = stStudentInfo.mTable.begin();
		iter != stStudentInfo.mTable.end();
		iter++)
	{
		iter->first;//key:string
		iter->second;//value:int
		//sum = sum + iter->second;
		vScores.push_back(iter->second);
	}

	//int a[10];
	//a...array start address
	//int* pA = &a[0] = a;

	std::sort(
		vScores.begin(),
		vScores.end() /*vScores.begin() + vScores.size()*/
	);
	return vScores[0];

}

int StudentScore::GetMax()
{
	vector<int> vScores;
	for (auto iter = stStudentInfo.mTable.begin();
		iter != stStudentInfo.mTable.end();
		iter++)
	{
		iter->second;//value:int
		vScores.push_back(iter->second);
	}
	std::sort(vScores.begin(), vScores.end());

	return vScores[vScores.size() - 1];//<-max vs min - vScores[0];

}
