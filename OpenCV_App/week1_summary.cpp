#include <iostream>
//istream - ostream
//cin">>" - cout"<<"

//#include"abc.h" user defined header file 
//함수 형태
//[반환형][함수명][(매개변수)] {  }
int main() 
{
	return 0; //TRUE - 1, FALSE - 0
	std::cout << "Hello, World\r\n" << std::endl; //endl = \n과 같은 역할

	//C++의 숫자 출력
	std::cout << "Math - "<< 100 << std::endl; //%d 
	std::cout << "Pi - " << 3.14 << std::endl; //%lf
	std::cout << "Score - " << 'A' << std::endl; //%c


	//C++의 숫자 입력
	int i = 0;
	std::cout << "input -";
	std::cin >> i; // 타입에 대한 형태에대해서 언급하지 않는것이  c와 큰 차이점
	std::cout << i << "typed" <<std::endl;

	return 0; //TRUE - 1, FALSE - 0
}