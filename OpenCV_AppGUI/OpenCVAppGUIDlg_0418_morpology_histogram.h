
// OpenCVAppGUIDlg.h: 헤더 파일
//

#pragma once

#include <iostream>

#define OPENCV_470

#include <opencv2/opencv.hpp>
#ifdef OPENCV_470
#include <opencv2/highgui/highgui_c.h>
#include <opencv2/imgproc/imgproc_c.h>
#include <opencv2/imgproc/types_c.h>
#endif // OPENCV_470


#ifdef _DEBUG
#pragma comment(lib,"opencv_world470d.lib")
#else	//RELEASE
#pragma comment(lib,"opencv_world470.lib")
#endif
using namespace std;
using namespace cv;

// 해당 아이디로 map을 생성
enum { eImgSrcColor = 0, eImgSrcGray, eImgDebugColor, eImgDebugGray, eImgDrawColor, eImgResultColor, eImgBufferMax };

typedef int(*InspMethod)(void*);

// COpenCVAppGUIDlg 대화 상자
class COpenCVAppGUIDlg : public CDialogEx
{
// 생성입니다.
public:
	COpenCVAppGUIDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SAMPLE_OPENCV_APPGUI_DIALOG};
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.




private :
	std::map<string, InspMethod> _mInsps;
	std::map<int, cv::Mat> _mMatBuff; // 이미지가 로딩이 될때 호출된다. (int)key-enum와 (map)value로 
	std::map<int, CRect> _mWndImageView;

	CRect _rtImageView;//image view area
	cv::Mat _SourceImage, _DrawImage;
	CImage _imageView;//image control object

	//sourceBuffer ... Original
	BITMAPINFO* _pBitmapInfo=nullptr; // Bitmap 정보를 담고 있는 구조체.
	bool _bShowResult = false;
	bool _bDebugResult = false;
	double _dSrcScale = 1.0, _dPtrnScale = 1.0, _dNewScale = 1.0;


	vector<cv::Point> _vLinePoints_L;
	vector<cv::Point> _vLinePoints_R;
	vector<cv::Point> _vLinePoints_U;
	vector<cv::Point> _vLinePoints_D;
	cv::Point _pt1, _pt2;

	int x1, x2, y1, y2;
	


public:
	void UpdateDispSrc();
private:
	int OnAllocateBuffer(int cols, int rows);
	int OnInspection(InputArray src, OutputArray dst);
	int OnInspection(Mat src, Mat dst);
	int OnInspection(unsigned char* pSrc, size_t cols, size_t rows, unsigned char* pDst);



	// 추가 구현
	static int CallInspFindcontourSample(void* lpUserData);
	static int CallInspFindShape(void* lpUserData);
	static int CallInspSegmentColor(void* lpUserData);
	static int CallInspMorpology(void* lpUserData);
	static int CallInspHistogram(void* lpUserData);
	static int CallInspHistoEqulization(void* lpUserData);


	int OnInspFindcontourSample();
	int OnInspFindShapes();
	int UpdateInspList();
	int OnInspSegmentColor();
	int OnInspMorpology();
	int OnInspHistogram();
	int OnInspHistoEqulization();

protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	
public:
	afx_msg void OnBtnClickedBtnLoad();
	afx_msg void OnBtnClickedBtnSave();
	afx_msg void OnBnClickedBnInspection();
	afx_msg void OnBnClickedBtnInspectioncv();
	afx_msg LRESULT OnAddString(WPARAM wParam, LPARAM lParam);

	void AddString(LPCTSTR lpszLog);
	CListBox _listBoxlog;

	void DisplayImage(int resDisplayID, Mat srcMat);
	void DrawImage();
	void CreateBitmapInfo(int w, int h, int bpp);	
};
