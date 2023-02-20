#include<string>
#include <iostream>
#include<vector>
#include <opencv2/opencv.hpp> //추가포함 디렉토리 설정해주기 
#ifdef _DEBUG
#pragma comment(lib, "opencv_world470d.lib")
#else 
#pragma comment(lib, "opencv_world470.lib")
#endif
using namespace std; //여기에서 namespace 선언해주면 된다
using namespace cv;
int main()
{
	const bool bComp = false;
	const int const_int = 100;
	const short const_short = 0xfff;
	const std::string const_str = "abcd"; //std name space 
	//string 은 std안에 속해있기때문에 넣어준다.
	string str_a = "a";
	string str_b = "b";
	string str_c = "c";
	string str_d = "d";
	string str_e = "e";

	std::cout << "Hello World!\n";
	std::string fileName = "jetson.bmp";
	cv::Mat img = cv::imread(fileName, IMREAD_COLOR);
	int sz_int = sizeof(int);
	int width = img.cols;
	int height = img.rows;
	unsigned char* rData = img.data;
	unsigned char* gData = img.data;
	unsigned char* bData = img.data;
	unsigned char* pData = img.data;

	/*int arrimg[25] = {0,}; //배열
	arrimg[5] = 5;

	std::vector<int> vimg(5); //백터

	float f_data = 1.23; //타입 변환 (요것은 c언어)
	int n_data = (int)f_data; //암묵적으로 int형으로 바꿈 이때에는
	//임시적으로 객체로 저장이된다.

	n_data = static_cast<int>(f_data);//타입변환(c++용)
	const char const_string[] = "ABC";
	std::cout << const_string << std::endl;
	char* msg = const_cast<char*>(const_string);
	msg[0] = 'D';
	std::cout << const_string << std::endl;
	std::cout << msg << std::endl;

	//static_cast
	char cNum = 'a';
	int* pNum = nullptr;
	pNum = (int*)(&cNum); //c 스타일
	//pNum = static_cast<int*>(&cNum); //c++ 스타일- 형변환 불가
	*pNum = 5;*/

	//mask processing
	//GRAY
	int mask_width = 3; int mask_height = 3;
	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			int index = row * width + col;
			if (row >= 0 && row < mask_height) { //좌상
				if (col >= 0 && col < mask_width) {
					pData[index] = 255;
				}
			}
			if (row >= 0 && row < mask_height) { //우상
				if (col >= 0 && col >= (width - mask_width)) {
					pData[index] = 255;
				}
			}
			if (row >= 0 && row >= height - mask_height) { //좌하
				if (col >= 0 && col < mask_width) {
					pData[index] = 255;
				}
			}
			if (row >= 0 && row >= height - mask_height) { //우하
				if (col >= 0 && col >= (width - mask_width)) {
					pData[index] = 255;
				}
			}
			
		}
	}
			

			
	//Color    
	/*int mask_width = 3; int mask_height = 3;
	for (int row = 0; row < mask_width; row++) {
		for (int col = 0; col < width; col++) {
			int index = row * width + col;
			index *= 3;
			if (row >= 0 && row < mask_height) {
				if (col >= 0 && col < mask_width) {
					rData[index] = 255;
					gData[index + 1] = 255;
					bData[index + 2] = 255;
				}
			}
		}
	}*/
	
	//threshold processing 
	int threshold = 100;
	//for문을 이용한 변화

	/*for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			int index = row * width + col;
			if (pData[index] > threshold) {
				pData[index] = 255;
			}
			else {
				pData[index] = 0;
			}
		}
	}
	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			int index = row * width + col;
			(pData[index] >= threshold) ? pData[index] = 255 : pData[index] = 0;
		}
	}*/
	//threshold를 이용하여 값변화
	/*Mat thrImg;
	cv::threshold(img, thrImg, threshold, 255, THRESH_BINARY);*/
	return 0;
}

