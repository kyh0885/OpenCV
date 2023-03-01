#include <iostream>
#include <string>
using namespace std;

class Info
{
public:
	Info();
	~Info();

	string Name(string _name);
	int Age(int _age);
	string Url(string url);
private:

};

Info::Info()
{
	cout << "Info::Ctor" << endl;
}

Info::~Info()
{
	cout << "Info::Dtor" << endl;
}

string Info::Name(string _name)
{
	cout << "이름 : " << _name << endl;
	return string();
}

int Info::Age(int _age)
{
	cout << "나이 : " << _age << endl;
	return 0;
}

string Info::Url(string url)
{
	cout << "Link URL : " << url << endl;
	return string();
}

int main()
{
	Info  _info;
	string strName;
	int strAge;
	string strUrl;

	cin >> strName;
	cin >> strAge;
	cin >> strUrl;

	_info.Name(strName);
	_info.Age(strAge);
	_info.Url(strUrl);
	
	return 1;
}