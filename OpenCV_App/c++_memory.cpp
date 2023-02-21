#include<iostream>
#include<memory>

int sum(const int* const pData, int size)
{
	int sum = 0;
	for (size_t i = 0; i < size; i++)
	{
		sum += pData[i];
		return sum;
	}
}

int main()
{
	//memory
	/*int a; double b; char c;
	int* pA; double* pB; char* pC;
	//array
	int arry[100] = { 0. }; //100 이 정해졌을때
	//동적메모리 기능
	int* pData = nullptr;



	//Memory create
	int sz = 100; 
	pData = new int[sz] {0, }; 
								
	if (pData != nullptr) {
		delete[] pData; pData = nullptr;  //memory delete
	}
	
	//shared_ptr
	/*class int
	{
		~int() //destory 하는법
		for (size_t rc = 0; rc < reference count; rc++)
		{
			if (this memo != nullptr) {
				delete[] this memo; this memo = nullptr;
			}
		}

	// create
	int* new operator{
	reference count++
	}
	};

    //week ptr : 하나이상의 shared ptr 참조가 있는 객체에대한 접근을 제공,
	//           소유자의 수에는 포함이 되지 않는다.

	std::unique_ptr<int> pDatas = std::make_unique<int>(100);
	std::shared_ptr<int> pDatas = std::make_shared<int>(100);
	//pointer and reference
	int dA = 10;
	int* pdA = &dA; //dA의 주소를 가르치게됨*/
	/*
	1) int function_name(int a)// int a = int obj : copy //내부데이터 외부데이터 다름
	2) int function_name(int *pA) // int* pA = int *obj :pointer
	2) int function_name(int *pA)// int* pA = &int obj :pointer
	int function_name(int &A) //int & 

	void swap_A(int lhs, int rhs) //내부*외부는 완전히 다르기 때문에 swap해도 변경불가능
	{
		int tmp;
		tmp = 1hs;
		1hs = rhs;
		rhs = tmp;
	}
	void swap_B(int* lhs, int* rhs) //외부데이터 변경으로 값변경 가능
	{
		int tmp;
		tmp = *1hs;
		*1hs = *rhs;
		*rhs = tmp;
	}

	//3가지 상수 포인터
	int num = 10;
	int const numRef1 = &num;
	const int *numRef2 = &num;
	const int* const numRef3 = &num;
	return 0;

	int num = 10; int* pnum = &num; // 1) 값변경 불가능 하지만 다른애로 참조가능
	int anotherNum = 20;
	const int* ptr1 = &num;
	*ptr1 = 5;
	ptr1 = &anotherNum; 

	int* const ptr2 = nullptr; // 2) 값변경가능 하지만 다른애로 참조 못함 (주소고정)
	int* const ptr3 = &num;
	*ptr3 = 6; */
	

	//example
	int* pImg = new int[5]{ 1,2,3,4,5 };
	std::cout << "buffer sum result : " << sum(pImg, 5) << std::endl;


}
