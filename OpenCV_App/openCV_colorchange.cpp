#include<string>
#include <iostream>
#include<vector>
#include <opencv2/opencv.hpp> //추가포함 디렉토리 설정해주기 
#ifdef _DEBUG
#pragma comment(lib, "opencv_world470d.lib")
#else 
#pragma comment(lib, "opencv_world470.lib")
#endif
using namespace std;
using namespace cv;


int sum(const unsigned char* const pData, int height, int width, int start_row, int start_col, int finish_row, int finish_col) {

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


	std::cout << "Hello World!\n";
	std::string fileName = "jetson.bmp";
	cv::Mat src = cv::imread(fileName, IMREAD_COLOR);
	if (src.empty())
	{
		return -1;
	}
	
	Mat gray = Mat(src.rows, src.cols, CV_8UC1);
	
	for (size_t row = 0; row < src.rows; row++)
	{
		for (size_t col = 0; col < src.cols; col++)
		{
			int index = row * src.cols + col;
			index *= 3;
			int b = src.data[index + 0]; //color에 접근을 하려면 3칸씩 이동해야한다.
			int g = src.data[index + 1];
			int r = src.data[index + 2];

			float yGray;
			yGray = 0.299 * b + 0.587 * g + 0.114 * b;

			
			gray.data[index/3] = yGray;
			gray.data[index/3 + 1] = yGray;
			gray.data[index/3 + 2] = yGray; //암시적 형변환


		}
	}
	//int sum(const int* const pData, int height, int width, int start_row, int start_col, int finish_row, int finish_col)
	cout << "image data sum" << sum(gray.data, gray.cols, gray.rows, 1, 1, 3, 3) << endl;

	//partial 함수
	
	return 0;
}

