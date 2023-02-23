#include "Kphone.h"

int main() {

	/*Kphone kphone;
	kphone.Send();

	while (true)
	{
		Kphone* pkphone = new Kphone();

		kphone.Numbers();

		if (pkphone != nullptr)
		{
			cout << "통화중 입니다" << endl;

			delete pkphone;
			pkphone = nullptr;
		}
		break;
	}

	kphone.Receive();
	return 1;*/
	{
		// 전화기를 들다
		Kphone* pKphone = new Kphone();
		//전화번호 입력
		//pKphone->Numbers("010-1234-5678");

		//음성인식 
		int* pAudio = new int [11] {
			0, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8};
		int length = 11;
		pKphone->Numbers(pAudio, length);

		//전화 걸기
		pKphone->Send();
		pKphone->cancel();

		//전화기를 내린다
		if (pKphone != nullptr) {
			delete pKphone;
			pKphone = nullptr;
		}

		//전화받기
		pKphone->Receive();
	}
	{
		//전화기를 들다
		Kphone* pKphone = new Kphone();

		//전화 걸기
		pKphone->Receive();
		pKphone->cancel();

		//전화기를 내린다
		if (pKphone != nullptr)
		{
			delete pKphone;
			pKphone = nullptr;
		}
	}

	return 1;
}