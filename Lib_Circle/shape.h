#pragma once
//#include "common.h"
#include <iostream>
#include <stdio.h>
#include<vector>
#include<string>
#include<memory> 
#include<algorithm>

using namespace std;


class Shape
{
public:
	Shape();
	virtual ~Shape(); 
	void SetVertexCnt(int points);
	int GetVertexCnt();
	//순수 가상 함수
	//virtual void ShowShapeInfo() = 0; // virtual 을이용하면 자식클래스는 부모클래스를 사용할 수 있다.
	//가상함수
	virtual void ShowShapeInfo();

private:
	int _points = 0;

};
