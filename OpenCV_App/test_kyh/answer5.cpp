#include <iostream>
#include <string>
using namespace std;

class IShape
{
public:
	IShape() { cout << "IShape::Ctor" << endl; }
	virtual~IShape() { cout << "IShape::Dtor" << endl; }
	virtual int GetShape() = 0;

private:

};

class Circle : public IShape
{
public:
	Circle() { cout << "Circle::Ctor" << endl; }
	~Circle() { cout << "Circle::Dtor" << endl; }
	int GetShape() { return 1; }

private:

};
class Rect : public IShape
{
public:
	Rect() { cout << "Rect::Ctor" << endl; }
	~Rect() { cout << "Rect::Dtor" << endl; }
	int GetShape() { return 2; }
private:

};

int main()
{
	IShape* pIShape;

	pIShape = dynamic_cast<Circle*>(new Circle());
	cout << pIShape->GetShape() << endl;

	if (pIShape != nullptr)
	{
		delete pIShape; 
		pIShape = nullptr;
	}

	pIShape = dynamic_cast<Rect*>(new Rect());
	cout << pIShape->GetShape() << endl;

	if (pIShape != nullptr)
	{
		delete pIShape; 
		pIShape = nullptr;
	}

	return 1;
}