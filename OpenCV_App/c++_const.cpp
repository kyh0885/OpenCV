#include<iostream>
#include<memory>

using namespace std;


int sum(const int* const pData, int size) //const 를 사용하면 외부에대한 데이터를 안정적으로 사용 할 수 있다.
									   	// 적극적으로 활용하는 것이 메모리 관리에 효율적
{
	int sum = 0;
	for (size_t i = 0; i < size; i++)
	{
		sum += pData[i];
		return sum;
	}
}

int sum(const int* const pData, int length, int start_index, int finish_index) {
	
	if (finish_index >= length) return -1;
	int sum = 0;
	for (size_t i = start_index; i <= finish_index; i++)
	{
		sum += pData[i];
		return sum;
	}
}



int sum(const int* const pData, 
		int height, int width, 
		int start_row, int start_col,
		int finish_row, int finish_col) {

	int sum = 0;
	for (size_t row = start_row; row <= finish_row; row++)
	{
		for (size_t col = start_col; col <= finish_col; col++)
		{
			int index = row * width + col;
			sum += pData[index];
		}
	}
	return sum;
}

int main()
{
	
	int* pImg = new int[5]{ 1,2,3,4,5 };
	std::cout << "buffer sum result : " << sum(pImg, 5) << std::endl;
	
	int width = 5;
	int height = 5;
	int* pImg = new int[width * height] {
		3, 4, 5, 6, 2,
		6, 4, 8, 3, 4,
		1, 2, 5, 4, 4,
		7, 8, 5, 4, 1,
		4, 2, 5, 1, 2,

	};

	int start_index = 6; int finish_index = 13;
	cout << "image data sum" << sum(pImg,width*height) << endl;
	cout << "image data sum" << sum(pImg, width * height, start_index, finish_index);
	//partial 함수
	

	if (pImg != nullptr)delete[]pImg;
	return 0;
}

