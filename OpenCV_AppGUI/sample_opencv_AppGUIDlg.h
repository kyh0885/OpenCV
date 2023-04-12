
// sample_opencv_AppGUIDlg.h: 헤더 파일
//

#pragma once

#include <iostream>
#include <stdio.h>
#include<vector>
#include<string>
#include<memory> 
#include<algorithm>
#include <opencv2/opencv.hpp>

#ifdef _DEBUG
#pragma comment(lib, "opencv_world470d.lib")
#else 
#pragma comment(lib, "opencv_world470.lib")
#endif
using namespace std;


// CsampleopencvAppGUIDlg 대화 상자
class CsampleopencvAppGUIDlg : public CDialogEx
{
// 생성입니다.
public:
	CsampleopencvAppGUIDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SAMPLE_OPENCV_APPGUI_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.

	CRect _rtImageView;
	CImage _imageView;

// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	
	afx_msg void OnBnClickedBtnLoad();
	afx_msg void OnBnClickedStaticSave();
	afx_msg void OnBnClickedResult();
	afx_msg void OnStnClickedPicture2();
};
