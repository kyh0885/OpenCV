#include <iostream>
#include <string>
using namespace std;

class Base
{
public:
	Base() {};
	virtual ~Base() {};
	virtual void Show() = 0;

private:
	
};
class ChildA :public Base
{
public:
	ChildA() {};
	~ChildA() {};
	void  Show(){ cout << "ChildA" << endl; }
};
class ChildB :public Base
{
public:
	ChildB() {};
	~ChildB() {};
	void Show() { cout << "ChildB" << endl; }
};
int main()
{
	Base* pBase = new ChildA;
	Base* pBase = new ChildB;

	pBase->Show();
	
	if (pBase != nullptr)
	{
		delete pBase;
		pBase = nullptr;
	}

	/*pData->Show();

	if (pData != nullptr)
	{
		delete pData;
		pData = nullptr;
	}*/

	return 1;

}
