
#include <iostream>

int main()
{
    int a = 0; // 공간의 생성 후 초기화 왜냐하면 대입연산자가 있기 때문이다
    int b(0); // 생성 시점에 초기화  
    std::cout << "Hello World!\n";
    return 0; // int 의 반환
}
