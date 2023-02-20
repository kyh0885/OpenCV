#include <iostream>

int main()
{
	int data[5 * 5] = {
		1,2,3,4,5,
		1,0,2,0,4,
		2,3,0,2,3,
		3,1,2,3,2,
		1,2,3,0,2
	};
	//0~5:6
	int histo[6] = { 0, };
	//histo[0] = 4; // 0 0 0 0 from data[]
	//histo[3] = 6; //3 3 3 3 3 3 from data[]
	//histo[5] = 1; //5 from data[]



	for (size_t i = 0; i < 5 * 5; i++)
	{
		histo[data[i]]++; //후위증분 연산자
	}
	for (size_t j = 0; j < 6; j++)
	{
		std::cout << j <<"  의 갯수 : " << histo[j] << std::endl;
	}
	
	return 0;
}