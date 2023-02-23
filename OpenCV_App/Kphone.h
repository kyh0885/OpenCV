#pragma once
#include "common.h"

class Kphone
{
public:
	Kphone();
	~Kphone();
	
	int Send();
	int Receive();
	int Numbers(String _strNumber); //입력식의 코드이면 virtual 추가
	int cancel();
	int Numbers(int* pAudioData, int length);
private:

	std::string strNumber;
	bool isConnected;
};

