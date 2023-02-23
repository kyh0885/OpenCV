#include "Kphone.h"

Kphone::Kphone()
	:strNumber("000-000-0000")
	,isConnected(false)
{
	cout << "Kphone::Ctor" << endl;
}

Kphone::~Kphone()
{
	cout << "Kphone::Dtor" << endl;

}

int Kphone::Send( )
{
	/*cout << "전화번호를 입력하세요 : " << endl;
	return 0;*/
	if (isConnected == true)
	{
		cout << "on the phone" << endl;
		return -1;
	}

	if (isConnected == true)
	{
		cout << "on the phone" << endl;
		return -1;
	}

	cout << "calling" << endl;
	cout << "linked" << endl;
	isConnected = true;
	cout << "communication start" << endl;
	cout << "communication end" << endl;

	return 0;
}

int Kphone::cancel()
{
	cout << "cancel button activated" << endl;
	cout << "communication finish" << endl;
	isConnected = false;
	return 0;
}

int Kphone::Receive()
{	
	if (isConnected == true)
	{
		cout << "on the phone" << endl;
		return -1;
	}
	cout << "linked" << endl;
	isConnected = true;
	cout << "communication start" << endl;
	/*cout << Kphone::strNumber << "에게 전화가 왔습니다. 받으시겠습니까? " << endl;
	char sym;
	cin >> sym;
	if (sym == 'Y') cout << "통화중" << endl;
	else if (sym == 'N') cout << "통화가 취소되었습니다." << endl;
	return 0;*/
}

int Kphone::Numbers(String _strNumber)
{
	/*cin >> Kphone::strNumber;
	cout << Kphone::strNumber << "으로 전화거는 중" << endl;
	return 0;*/

	strNumber = _strNumber;
	return 0;
}

int Kphone::Numbers(int* pAudioData, int length) //음성인식으로 변경 
{
	//pAudioData 분석
	//음성인식 알고리즘 넣어줘
	string number = "010-1234-5678";
	strNumber = number;
	//결과로 문자를 반환
	return 0;
}
