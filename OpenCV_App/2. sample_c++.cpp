#include<string>
#include <iostream>
#include<vector>
#include <opencv2/opencv.hpp> 
#ifdef _DEBUG
#pragma comment(lib, "opencv_world470d.lib")
#else 
#pragma comment(lib, "opencv_world470.lib")
#endif
using namespace std;
int main()
{
    //if 문 기초
    /*int sum = 10;
    if (sum > 10)
        cout << "sum >10" << endl;
    else if (sum > 5)
        cout << "sum>5" << endl;
    else
        cout << "no result" << endl;*/

    //if문 quiz - 학점문제
    /*int score;

    if (score>=100) std::cout << "A\n";
    else if ((score >= 90) && (score < 100)) std::cout << "B\n";
    else if ((score >= 80) && (score < 90)) std::cout << "C\n";
    else std::cout << "None\n";
    return 0; */

    //반복문
    /*int rows = 10;
    int cols = 10;
    for (int row = 0; row < rows ; row++)
    {
        cout << "row=" << row <<"\t";
        for (int col = 0; col < cols; col++)
        {
            cout << "col=" << col << "\t";
        }
        cout << endl;
    }*/

    //pointer, reference
    //메모리 주소를 의미하는 곳을 저장라는 형태의 변수
    //창 : 배열과 같은 연속 데이터에 접근+조작이 용이
    //메모리 동적 할당/해제 리소스 관리 기능*효율적
    //복잡한 자료 구조 효율적으로 접근 기능 및 처리
    //[int*] [pData] = nullptr;
    
    /*int Data = 100;
    int* pData = &Data; //pData = nullptr;

    int nArray[10] = {1,2,3,4,5,6,7,8,9,10};
    int* pArray = nArray; //&nArray[0] 시작주소를 저장 / int 타입의 포인터이고 그포인터변수의이름은  pArray이다.
    for (int i = 0; i < sizeof(nArray) / sizeof(nArray[0]); i++) // 40/4=10 -> 배열의 사이즈만으로도 구할 수 있다.
    {
        cout << *(pArray + i) << "\t";
        cout << pArray[i] << "\t"; //위치를 가져오는 것
        cout << *(pArray++) << "\t";
    }
    cout << endl;*/
    

}