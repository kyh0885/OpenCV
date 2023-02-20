#include<iostream>

using namespace std;

struct student {
	int id;
	string name;
	float percentage;

	void show() {
		cout << "아이디 : " << id << "이름 : " << name << "백분율" << percentage << endl;
	}
};
int main() {
	student s = { 1,"김철수",90.5 };

	s.show();
	return 0;
}
