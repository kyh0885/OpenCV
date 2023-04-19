// OpenCVAppGUIDlg.cpp: 구현 파일

#include "pch.h"
#include "framework.h"
#include "OpenCVAppGUI.h"
#include "OpenCVAppGUIDlg.h"
#include "afxdialogex.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <ctime>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#define NAME_WINDOW_SRC "srcView" // 첫번째 
#define NAME_WINDOW_Debug "srcDebug"// 두번째 
#define NAME_WINDOW_RESULT "srcResult"// 세번째 
#define WM_ADD_STRING	(WM_USER + 500)

// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// COpenCVAppGUIDlg 대화 상자



COpenCVAppGUIDlg::COpenCVAppGUIDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SAMPLE_OPENCV_APPGUI_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void COpenCVAppGUIDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_LOG, _listBoxlog);
}

BEGIN_MESSAGE_MAP(COpenCVAppGUIDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_LOAD, &COpenCVAppGUIDlg::OnBtnClickedBtnLoad)
	ON_BN_CLICKED(IDC_BTN_SAVE, &COpenCVAppGUIDlg::OnBtnClickedBtnSave)
	ON_BN_CLICKED(IDC_BTN_INSPECTION, &COpenCVAppGUIDlg::OnBnClickedBnInspection)
	ON_BN_CLICKED(IDC_BTN_INSPECTIONCV, &COpenCVAppGUIDlg::OnBnClickedBtnInspectioncv)
	ON_MESSAGE(WM_ADD_STRING, &COpenCVAppGUIDlg::OnAddString)

	END_MESSAGE_MAP()


// COpenCVAppGUIDlg 메시지 처리기

BOOL COpenCVAppGUIDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	//ShowWindow(SW_MAXIMIZE);
	//ShowWindow(SW_MINIMIZE);


	// 여기서 부터 사용자가 정하는 구간이다.
	// openCV -> window handle -> display를 할 수 있도록 함수 구현
	namedWindow(NAME_WINDOW_SRC, WINDOW_AUTOSIZE); // 이름과 크기를 정함
	HWND hWnd = (HWND)cvGetWindowHandle(NAME_WINDOW_SRC); // 가져옴
	HWND hParent = (HWND)FindWindow(NULL, NAME_WINDOW_SRC); // 찾기
	HWND hOrgParent = ::SetParent(hWnd, GetDlgItem(IDC_PICTURE)->m_hWnd); // 설정
	::ShowWindow(hOrgParent, SW_HIDE); // 보여주기 show를 하면 이름이 창에 떠있다.

	namedWindow(NAME_WINDOW_Debug, WINDOW_AUTOSIZE);
	hWnd = (HWND)cvGetWindowHandle(NAME_WINDOW_Debug);
	hParent = (HWND)FindWindow(NULL, NAME_WINDOW_Debug);
	hOrgParent = ::SetParent(hWnd, GetDlgItem(IDC_PICTURE2)->m_hWnd);
	::ShowWindow(hOrgParent, SW_HIDE);


	namedWindow(NAME_WINDOW_RESULT, WINDOW_AUTOSIZE);
	hWnd = (HWND)cvGetWindowHandle(NAME_WINDOW_RESULT);
	hParent = (HWND)FindWindow(NULL, NAME_WINDOW_RESULT);
	hOrgParent = ::SetParent(hWnd, GetDlgItem(IDC_PICTURE3)->m_hWnd);
	::ShowWindow(hOrgParent, SW_HIDE);



	GetDlgItem(IDC_PICTURE)->GetWindowRect(_rtImageView); // 가로세로 크기 설정
	ScreenToClient(_rtImageView); // 좌표계 변경

	GetDlgItem(IDC_PICTURE2)->GetWindowRect(_rtImageView); // 가로세로 크기 설정
	ScreenToClient(_rtImageView);

	GetDlgItem(IDC_PICTURE3)->GetWindowRect(_rtImageView); // 가로세로 크기 설정
	ScreenToClient(_rtImageView);

	_mWndImageView.clear();
	_mWndImageView.insert(pair<int, CRect>(IDC_PICTURE, CRect(0, 0, 0, 0)));
	_mWndImageView.insert(pair<int, CRect>(IDC_PICTURE2, CRect(0, 0, 0, 0)));
	_mWndImageView.insert(pair<int, CRect>(IDC_PICTURE3, CRect(0, 0, 0, 0)));

	for (auto iter = _mWndImageView.begin(); iter != _mWndImageView.end(); iter++) {
		int resID = (iter->first);
		CRect rtImgView;
		GetDlgItem(resID)->GetWindowRect(rtImgView);
		ScreenToClient(rtImgView);
		iter->second = rtImgView;
	}

	_mMatBuff.clear();
	_mInsps.clear();

	AddString("System Log :: Start()");

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}







void COpenCVAppGUIDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.



// 공간을 채우는 역할
void COpenCVAppGUIDlg::OnPaint()
{
	CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

	if (IsIconic())
	{
		//CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{

		//if (!_imageView.IsNull())
		//{
		//	dc.SetStretchBltMode(COLORONCOLOR);
		//	_imageView.Draw(dc, _rtImageView);
		//}
//		DisplayImage(IDC_PICTURE, _DrawImage);


		//CRect rect;
		//::GetWindowRect(GetDlgItem(IDC_PICTURE)->m_hWnd, rect);
		//ScreenToClient(rect);

		CBrush brush(HS_DIAGCROSS, RGB(200, 200, 200));
		//dc.FillRect(CRect(rect.left + 1, rect.top + 1, rect.right, rect.bottom), &brush);

		for (auto iter = _mWndImageView.begin(); iter != _mWndImageView.end(); iter++) {
			CRect rt = iter->second;
			dc.FillRect(rt, &brush);
		}



		if (!_mMatBuff[eImgSrcColor].empty())
		{
			Mat Img = _mMatBuff[eImgSrcColor];
			Mat DrawResize;
			Size size(int(_dNewScale * Img.cols), int(_dNewScale * Img.rows));
			resize(Img, DrawResize, size);

			resizeWindow(NAME_WINDOW_SRC, size.width, size.height); // 여기는 자리 set
			imshow(NAME_WINDOW_SRC, DrawResize);
		}

		if (_bDebugResult)
		{
			if (!_mMatBuff[eImgDebugColor].empty())
			{
				Mat Img = _mMatBuff[eImgDebugColor];
				Mat DrawResize;
				Size size(int(_dNewScale * Img.cols), int(_dNewScale * Img.rows));
				resize(Img, DrawResize, size);

				resizeWindow(NAME_WINDOW_Debug, size.width, size.height);
				imshow(NAME_WINDOW_Debug, DrawResize);
			}
		}

		if (_bShowResult)
		{
			if (!_mMatBuff[eImgDrawColor].empty())
			{
				Mat Img = _mMatBuff[eImgDrawColor];
				Mat DrawResize;
				Size size(int(_dNewScale * Img.cols), int(_dNewScale * Img.rows));
				resize(Img, DrawResize, size);

				resizeWindow(NAME_WINDOW_RESULT, size.width, size.height);
				imshow(NAME_WINDOW_RESULT, DrawResize);
			}
		}
		CDialogEx::OnPaint();
	}
}


// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR COpenCVAppGUIDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void COpenCVAppGUIDlg::OnBtnClickedBtnLoad()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CFileDialog fileDlg(TRUE, NULL, NULL, OFN_READONLY, _T("image file(*.jpg;*.bmp;*.png;)|*.jpg;*.bmp;*.png;|All Files(*.*)|*.*||"));
	if (fileDlg.DoModal() == IDOK)
	{
		CString path = fileDlg.GetPathName();
		string fileName = path;
		_SourceImage = cv::imread(fileName, IMREAD_ANYCOLOR);

		OnAllocateBuffer(_SourceImage.cols, _SourceImage.rows);
		UpdateDispSrc();
		UpdateInspList();
		InvalidateRect(_rtImageView, FALSE);
		AfxMessageBox("Image Loaded");
	}
}


void COpenCVAppGUIDlg::OnBtnClickedBtnSave()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//string fileName = "jetson_clone.bmp";
	//_imageView.Save(fileName.c_str());

	CFileDialog dlgFileSave(FALSE, "*.*", NULL,//화일명 없음
		OFN_FILEMUSTEXIST,
		_T("image file(*.jpg;*.bmp;*.png;)|*.jpg;*.bmp;*.png;|All Files(*.*)|*.*||"), NULL);

	//옵션 선택 부분.
	if (dlgFileSave.DoModal() == IDOK)
	{
		string str = dlgFileSave.GetPathName();
		imwrite(str, _SourceImage);
	}

	AfxMessageBox("Image Saved");
}


void COpenCVAppGUIDlg::UpdateDispSrc()
{
	_bShowResult = false;
	CRect rectSrc;
	::GetWindowRect(GetDlgItem(IDC_PICTURE)->m_hWnd, rectSrc);
	double dScaleX = rectSrc.Width() / (double)_SourceImage.cols;
	double dScaleY = rectSrc.Height() / (double)_SourceImage.rows;
	_dSrcScale = min(dScaleX, dScaleY); 
	_dNewScale = _dSrcScale;
	//_bShowResult = FALSE;
	//防止顯示不同比例圖片時DC殘留
	CWnd* pWnd = GetDlgItem(IDC_PICTURE);
	pWnd->GetClientRect(&rectSrc);//제어 클라이언트 영역의 좌표 얻기
	pWnd->ClientToScreen(rectSrc);//제어 클라이언트 영역에서 대화 영역으로 영역 좌표 변환
	this->ScreenToClient(rectSrc); //다이얼로그 영역의 영역 좌표를 다이얼로그의 클라이언트 영역 좌표로 변환
	InvalidateRect(rectSrc); // 이것을 통하여 업데이트 된다.
	// Rect 는 내가 가지고 있는 영역만
	// 그냥을 화면 전체
	//비율이 다른 사진을 표시할 때 DC 잔여물 방지

	//Scroll Bar


	//Test
	//double d1 = clock ();
	//Mat matResult;
	//matchTemplate (_DrawImage, _matPtrn, matResult, CV_TM_CCORR);
	//double d2 = clock ();

	////From ImageShop
	//matResult.create (_DrawImage.rows - _matPtrn.rows + 1,
	//	_DrawImage.cols - _matPtrn.cols + 1, CV_32FC1);
	//matResult.setTo (0);
	//cv::Mat& matTemplate = _matPtrn;

	//int  t_r_end = matTemplate.rows, t_r = 0;
	//for (int r = 0; r < matResult.rows; r++)
	//{
	//	float* r_matResult = matResult.ptr<float> (r);
	//	uchar* r_source = _DrawImage.ptr<uchar> (r);
	//	uchar* r_template, *r_sub_source;
	//	for (int c = 0; c < matResult.cols; ++c, ++r_matResult, ++r_source)
	//	{
	//		r_template = matTemplate.ptr<uchar> ();
	//		r_sub_source = r_source;
	//		for (t_r = 0; t_r < t_r_end; ++t_r, r_sub_source += _DrawImage.cols, r_template += matTemplate.cols)
	//		{
	//			*r_matResult = *r_matResult + IM_Conv_SIMD (r_template, r_sub_source, matTemplate.cols);
	//		}
	//	}
	//}
	//double d3 = clock ();

	
	//double d = (d3 - d2) / (d2 - d1);
	//CString str; str.Format ("%.3f", d); AfxMessageBox (str);
	//
}




void COpenCVAppGUIDlg::OnBnClickedBnInspection()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	_bShowResult = false;
	_bDebugResult = false;
	//input
		//OnInspection(InputArray src, OutputArray dst);
	Mat src = _mMatBuff[eImgSrcGray];
	Mat img_canny;

	//fucntion
	Mat dst = _mMatBuff[eImgDebugGray];

	// using pointer to data
	OnInspection(src.data, src.cols, src.rows, dst.data);

	//result & display
	_bShowResult = true;
	_bDebugResult = true;
	dst.copyTo(_mMatBuff[eImgDebugGray]);
	
	cvtColor(_mMatBuff[eImgDebugGray], _mMatBuff[eImgDebugColor], COLOR_GRAY2BGR);
	//Canny(_mMatBuff[eImgDebugColor], img_canny, 150, 255);
	//vector<Vec2f> lines;
	//HoughLines(img_canny, lines, 1, CV_PI /180, 150);
	//Mat img_lane;
	//threshold(img_canny, img_lane, 150, 255, THRESH_MASK);

	//for (size_t i = 0; i < lines.size(); i++)
	//{
	//	float rho = lines[i][0], theta = lines[i][1];
	//	Point pt1, pt2;
	//	double a = cos(theta), b = sin(theta);
	//	double x0 = a * rho, y0 = b * rho;
	//	pt1.x = cvRound(x0 + 1000 * (-b));
	//	pt1.y = cvRound(y0 + 1000 * (a));
	//	pt2.x = cvRound(x0 - 1000 * (-b));
	//	pt2.y = cvRound(y0 - 1000 * (a));
	//	line(_mMatBuff[eImgDebugGray], pt1, pt2, Scalar(0, 0, 255), 2, 8);
	//	line(img_lane, pt1, pt2, Scalar::all(255), 1, 8);
	//}


	Mat draw = _mMatBuff[eImgDrawColor];
	//cv::rectangle(draw, Rect(10, 10, 50, 50), Scalar(0, 0, 255), 3);
	int thickness = 5;
	int lineType = LINE_8;
	int w = 100;
	/*
	line(draw, Point(100, 100), Point(200,100), Scalar(255, 0, 0), thickness, lineType);
	line(draw, Point(200, 100), Point(200, 200), Scalar(0, 255, 0), thickness, lineType);
	line(draw, Point(200, 200), Point(100, 200), Scalar(0, 255, 0), thickness, lineType);
	line(draw, Point(100, 200), Point(100, 100), Scalar(0, 255, 255), thickness, lineType);*/

	//// 가로의 파란색을 위함 (십자모양)
	//line(draw, Point(_pt1.x - 10, _pt1.y), Point(_pt1.x + 10, _pt1.y), Scalar(255, 0, 0), thickness, lineType);
	//line(draw, Point(_pt1.x, _pt1.y - 10), Point(_pt1.x, _pt1.y + 10), Scalar(255, 0, 0), thickness, lineType);
	//line(draw, Point(_pt2.x - 10, _pt2.y), Point(_pt2.x + 10, _pt2.y), Scalar(255, 0, 0), thickness, lineType);
	//line(draw, Point(_pt2.x, _pt2.y - 10), Point(_pt2.x, _pt2.y + 10), Scalar(255, 0, 0), thickness, lineType);
	//// 일직선 모양
	/*line(draw, Point(_pt1.x, _pt1.y), Point(_pt2.x, _pt2.y), Scalar(0, 255, 255), thickness, lineType); */

	// 파란색 -> 점을 찍으면서 줄로 만들음
	for (size_t i = 0; i < _vLinePoints_L.size(); i++)
	{
		line(draw, Point(_vLinePoints_L[i].x, _vLinePoints_L[i].y), Point(_vLinePoints_L[i].x, _vLinePoints_L[i].y), Scalar(255, 255, 0), thickness, lineType);
	}
	for (size_t i = 0; i < _vLinePoints_R.size(); i++)
	{
		line(draw, Point(_vLinePoints_R[i].x, _vLinePoints_R[i].y), Point(_vLinePoints_R[i].x, _vLinePoints_R[i].y), Scalar(0, 0, 255), thickness, lineType);
	}
	for (size_t i = 0; i < _vLinePoints_U.size(); i++)
	{
		line(draw, Point(_vLinePoints_U[i].x, _vLinePoints_U[i].y), Point(_vLinePoints_U[i].x, _vLinePoints_U[i].y), Scalar(0, 255, 0), thickness, lineType);
	}
	for (size_t i = 0; i < _vLinePoints_D.size(); i++)
	{
		line(draw, Point(_vLinePoints_D[i].x, _vLinePoints_D[i].y), Point(_vLinePoints_D[i].x, _vLinePoints_D[i].y), Scalar(0, 255, 255), thickness, lineType);
	}

	draw = _mMatBuff[eImgDebugColor];
	x1 = _vLinePoints_L[3].x;
	x2 = _vLinePoints_R[3].x;
	y1 = _vLinePoints_U[3].y;
	y2 = _vLinePoints_D[3].y;

	//line(draw, Point(0, y1), Point(dst.cols ,y1), Scalar(255, 0, 0), thickness, lineType); //up
	//line(draw, Point(0, y2), Point(dst.cols, y2), Scalar(255, 0, 255), thickness, lineType); //down
	//line(draw, Point(x1, 0), Point(x1, dst.rows), Scalar(0, 0, 255), thickness, lineType); //left
	//line(draw, Point(x2, 0), Point(x2, dst.rows), Scalar(0, 255, 255), thickness, lineType); //right

	line(draw, Point(x1 - 10, y1 - 10), Point(x1 + 10, y1 + 10), Scalar(255, 0, 0), thickness, lineType);// 왼위
	line(draw, Point(x1 + 10, y1 - 10), Point(x1 - 10, y1 + 10), Scalar(255, 0, 0), thickness, lineType);
	line(draw, Point(x2 - 10, y1 - 10), Point(x2 + 10, y1 + 10), Scalar(255, 0, 0), thickness, lineType); 
	line(draw, Point(x2 + 10, y1 - 10), Point(x2 - 10, y1 + 10), Scalar(255, 0, 0), thickness, lineType);
	line(draw, Point(x1 - 10, y2 - 10), Point(x1 + 10, y2 + 10), Scalar(255, 0, 0), thickness, lineType);
	line(draw, Point(x1 + 10, y2 - 10), Point(x1 - 10, y2 + 10), Scalar(255, 0, 0), thickness, lineType);
	line(draw, Point(x2 - 10, y2 - 10), Point(x2 + 10, y2 + 10), Scalar(255, 0, 0), thickness, lineType);
	line(draw, Point(x2 + 10, y2 - 10), Point(x2 - 10, y2 + 10), Scalar(255, 0, 0), thickness, lineType);



	//circle(draw, Point(x1, y1),20, Scalar(255, 0, 0), thickness, lineType);
	//circle(draw, Point(x1, y2), 20, Scalar(0, 255, 0), thickness, lineType);
	//circle(draw, Point(x2, y1), 20, Scalar(0, 0, 255), thickness, lineType);
	//circle(draw, Point(x2, y2), 20, Scalar(255, 255, 0), thickness, lineType);

	Invalidate(FALSE);
}


int COpenCVAppGUIDlg::OnAllocateBuffer(int cols, int rows)

{
	_mMatBuff.clear();

	_mMatBuff.insert(make_pair<int, cv::Mat>(eImgSrcColor, Mat(rows, cols, CV_8UC3)));
	_mMatBuff.insert(make_pair<int, cv::Mat>(eImgSrcGray, Mat(rows, cols, CV_8UC1)));
	_mMatBuff.insert(make_pair<int, cv::Mat>(eImgDebugGray, Mat(rows, cols, CV_8UC1)));
	_mMatBuff.insert(make_pair<int, cv::Mat>(eImgDebugColor, Mat(rows, cols, CV_8UC3)));
	_mMatBuff.insert(make_pair<int, cv::Mat>(eImgDrawColor, Mat(rows, cols, CV_8UC3)));
	_mMatBuff.insert(make_pair<int, cv::Mat>(eImgResultColor, Mat(rows, cols, CV_8UC3)));

	//source to source of map
	//_SourceImage.copyTo(_mMatBuff[eImgSrc]);
	//source to draw of map

	if (_SourceImage.type() == CV_8UC1)
	{
		cvtColor(_SourceImage, _mMatBuff[eImgSrcColor], COLOR_GRAY2BGR);
		_SourceImage.copyTo(_mMatBuff[eImgSrcGray]);
	}
	else
	{
		_SourceImage.copyTo(_mMatBuff[eImgSrcColor]); // 컬러는 그냥 출력
		cvtColor(_SourceImage, _mMatBuff[eImgSrcGray], COLOR_BGR2GRAY); // 그레이로 변경
	}

	Mat vi = _mMatBuff[eImgSrcColor];

	_mMatBuff[eImgSrcColor].copyTo(_mMatBuff[eImgDrawColor]);

	//debug of map ... just create buffer as initilized value
	_mMatBuff[eImgDebugGray] = 0;

	//result of map ... just create buffer as initilized value
	_mMatBuff[eImgResultColor] = 255;

	return 0;
}


int COpenCVAppGUIDlg::UpdateInspList()
{
	_mInsps.insert(make_pair("OnInspFindcontourSample", COpenCVAppGUIDlg::CallInspFindcontourSample));
	_mInsps.insert(make_pair("OnInspFindShape", COpenCVAppGUIDlg::CallInspFindShape));
	_mInsps.insert(make_pair("CallInspSegmentColor", COpenCVAppGUIDlg::CallInspSegmentColor));
	_mInsps.insert(make_pair("OnInspSegmentColor", COpenCVAppGUIDlg::CallInspSegmentColor));
	_mInsps.insert(make_pair("OnInspMorpology", COpenCVAppGUIDlg::CallInspMorpology));
	_mInsps.insert(make_pair("OnInspHistogram", COpenCVAppGUIDlg::CallInspHistogram));
	_mInsps.insert(make_pair("OnInspHistoEqulization", COpenCVAppGUIDlg::CallInspHistoEqulization));
	_mInsps.insert(make_pair("OnInspCorrection", COpenCVAppGUIDlg::CallInspCorrection));
	_mInsps.insert(make_pair("OnInspSearchingContour", COpenCVAppGUIDlg::CallInspSearchingContour));

	return 1;
}



int COpenCVAppGUIDlg::OnInspection(uchar* pSrc, size_t cols, size_t rows, unsigned char* pDst)
{

	for (size_t i = 0; i < cols * rows; i++)
	{
		if (pSrc[i] > 128) pDst[i] = 255; // white
		else pDst[i] = 0; // black
	}
	_vLinePoints_D.clear();
	_vLinePoints_L.clear();
	_vLinePoints_U.clear();
	_vLinePoints_R.clear();

	_pt1 = cv::Point(0, 0);
	_pt2 = cv::Point(0, 0);
	for (size_t row = 0; row < rows; row++) //왼쪽에서 오른쪽으로
	{
		for (size_t col = 0; col < cols; col++)// 위에서 아래로 
		{
			int index = row * cols + col;
			if (pDst[index] > 100)
			{
				//if (row == 10)
				//{
				//	_pt1 = cv::Point(col, row);
				//}
				//if (row == rows - 10) //뒤에서 10번째
				//{
				//	_pt2 = cv::Point(col, row);
				//}
				_vLinePoints_L.push_back(cv::Point(col, row));
				break;
			}
		}

	}


	for (size_t row = 0; row < rows; row++) 
	{
		for (size_t col = cols-1; col >0; col--)
		{
			int index = row * cols + col;
			if (pDst[index] > 100)
			{
				//if (row == 10)
				//{
				//	_pt1 = cv::Point(col, row);
				//}
				//if (row == rows - 10) //뒤에서 10번째
				//{
				//	_pt2 = cv::Point(col, row);
				//}
				_vLinePoints_R.push_back(cv::Point(col, row));
				break;
			}
		}

	}
	for (size_t col = cols; col > 0; col--)
	{
		for (size_t row = 0; row < rows; row++)
		{
			int index = row * cols + col;
			if (pDst[index] > 100)
			{
				//if (row == 10)
				//{
				//	_pt1 = cv::Point(col, row);
				//}
				//if (row == rows - 10) //뒤에서 10번째
				//{
				//	_pt2 = cv::Point(col, row);
				//}
				_vLinePoints_U.push_back(cv::Point(col, row));
				break;
			}
		}

	}

	for (size_t col = 0; col < cols ; col++)
	{
		for (size_t row = rows-1; row > 0; row--)
		{
			int index = row * cols + col;
			if (pDst[index] > 100)
			{
				//if (row == 10)
				//{
				//	_pt1 = cv::Point(col, row);
				//}
				//if (row == rows - 10) //뒤에서 10번째
				//{
				//	_pt2 = cv::Point(col, row);
				//}
				_vLinePoints_D.push_back(cv::Point(col, row));
				break;
			}
		}

	}
	return 0;
}




void COpenCVAppGUIDlg::OnBnClickedBtnInspectioncv()
{
	//auto f = _mInsps["OnInspFindCircle"];
	//auto f = _mInsps["OnInspFindFaceID"];
	//auto ret = f(this); // int COpenCVAppGUIDlg::OnInspFindShapes()

	//auto f = _mInsps["OnInspFindShape"];
	//auto f = _mInsps["OnInspFindColor"];
	//auto f = _mInsps["OnInspMorpology"];
	//auto f = _mInsps["OnInspHistogram"];
	//auto f = _mInsps["OnInspHistoEqulization"];
	auto f = _mInsps["OnInspSearchingContour"];

	if (f == nullptr) return;
	auto ret = f(this); // int COpenCVAppGUIDlg::OnInspFindShapes()
}

int COpenCVAppGUIDlg::CallInspFindcontourSample(void* lpUserData)
{
	COpenCVAppGUIDlg* pDlg = reinterpret_cast<COpenCVAppGUIDlg*>(lpUserData);
	return pDlg->OnInspFindcontourSample();
}

int COpenCVAppGUIDlg::CallInspFindShape(void* lpUserData)
{
	COpenCVAppGUIDlg* pDlg = reinterpret_cast<COpenCVAppGUIDlg*>(lpUserData);
	return pDlg->OnInspFindShapes();
}

int COpenCVAppGUIDlg::CallInspSegmentColor(void* lpUserData)
{
	COpenCVAppGUIDlg* pDlg = reinterpret_cast<COpenCVAppGUIDlg*>(lpUserData);
	return pDlg->OnInspSegmentColor();
}
int COpenCVAppGUIDlg::CallInspMorpology(void* lpUserData)
{
	COpenCVAppGUIDlg* pDlg = reinterpret_cast<COpenCVAppGUIDlg*>(lpUserData);
	return pDlg->OnInspMorpology();
}

int COpenCVAppGUIDlg::CallInspHistogram(void* lpUserData)
{
	COpenCVAppGUIDlg* pDlg = reinterpret_cast<COpenCVAppGUIDlg*>(lpUserData);
	return pDlg->OnInspHistogram();
}

int COpenCVAppGUIDlg::CallInspHistoEqulization(void* lpUserData)
{
	COpenCVAppGUIDlg* pDlg = reinterpret_cast<COpenCVAppGUIDlg*>(lpUserData);
	return pDlg->OnInspHistoEqulization();
}

int COpenCVAppGUIDlg::CallInspCorrection(void* lpUserData)
{
	COpenCVAppGUIDlg* pDlg = reinterpret_cast<COpenCVAppGUIDlg*>(lpUserData);
	return pDlg->OnInspCorrection();
}

int COpenCVAppGUIDlg::CallInspSearchingContour(void* lpUserData)
{
	COpenCVAppGUIDlg* pDlg = reinterpret_cast<COpenCVAppGUIDlg*>(lpUserData);
	return pDlg->OnInspSearchingContour();
}




int COpenCVAppGUIDlg::OnInspFindShapes()
{
	Mat src_gray = _mMatBuff[eImgSrcGray];
	int thresh = 20;
	Mat thr_img;
	threshold(src_gray, thr_img, thresh, 255, THRESH_BINARY);
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(thr_img, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);
	vector<int> vCircle_index, vTriangle_index, vRectangle_index;
	Mat drawing = _mMatBuff[eImgDrawColor];

	for (vector<Point>& pts : contours)
	{
		if (contourArea(pts) < 400)
		{
			continue;
		} // 잡음은 무시

		vector<Point> approx;
		approxPolyDP(pts, approx, arcLength(pts, true) * 0.02, true); // 좌표의 갯수 추출 -> 

		int vtc = (int)approx.size();
		if (vtc == 3) // 삼각형
		{
			vTriangle_index.push_back(vtc);
			putText(drawing, "[1]", Point(pts[0].x - 10, pts[0].y - 10), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 255, 255), 1, LINE_8, false);
		}
		else if (vtc == 4) // 사각형
		{
			vRectangle_index.push_back(vtc);
			putText(drawing, "[2]", Point(pts[0].x - 10, pts[0].y - 10), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 0, 255), 1, LINE_8, false);
		}
		else if (vtc > 4) //원
		{
			double len = arcLength(pts, true);
			double area = contourArea(pts);
			double ratio = 4. * CV_PI * area / (len * len); //1에 가까울수록 원에 가깝다.

			if (ratio > 0.8)
			{
				vCircle_index.push_back(vtc);
				putText(drawing, "[3]", Point(pts[0].x - 10, pts[0].y - 10), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 255, 0), 1, LINE_8, false);
			}
		}
	}

	/*drawing = _mMatBuff[eImgDebugColor];

	for (size_t index = 0; index < vTriangle_index.size(); index++)
	{
		Scalar color = Scalar(0, 255, 255);
		drawContours(drawing, contours, vTriangle_index[index], color, -1, LINE_8, hierarchy, 0);
	}
	for (size_t index = 0; index < vRectangle_index.size(); index++)
	{
		Scalar color = Scalar(0, 0, 255);
		drawContours(drawing, contours, vRectangle_index[index], color, -1, LINE_8, hierarchy, 0);
	}
	for (size_t index = 0; index < vCircle_index.size(); index++)
	{
		drawContours(drawing, contours, vCircle_index[index], Scalar(255, 255, 255), CV_FILLED, 8, hierarchy);
	}*/

	_bShowResult = true;
	_bDebugResult = true;

	Invalidate(FALSE);

	return 0;
}


int COpenCVAppGUIDlg::OnInspFindcontourSample()
{

	Mat src_gray = _mMatBuff[eImgSrcGray];
	int thresh = 128;

	RNG rng(12345);

	//Mat canny_output;
	//Canny(src_gray, canny_output, thresh, thresh * 2);

	Mat thr_img;
	threshold(src_gray, thr_img, thresh, 255, THRESH_BINARY);

	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	findContours(thr_img, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);

	//canny_output.copyTo(_mMatBuff[eImgDebugGray]);
	cvtColor(_mMatBuff[eImgDebugGray], _mMatBuff[eImgDebugColor], COLOR_GRAY2BGR);
	Mat drawing = _mMatBuff[eImgDebugColor];

	for (size_t i = 0; i < contours.size(); i++)
	{
		Scalar color = Scalar(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));
		drawContours(drawing, contours, (int)i, color, 2, LINE_8, hierarchy, 0);
	}
	drawing = _mMatBuff[eImgDrawColor];

	for (size_t i = 0; i < contours.size(); i++)
	{
		Scalar color = Scalar(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));
		drawContours(drawing, contours, (int)i, color, 2, LINE_8, hierarchy, 0);
	}

	int thickness = 5;
	int lineType = LINE_8;
	for (size_t i = 0; i < contours.size(); i++)
	{
		for (size_t k = 0; k < contours[i].size(); k++)
		{
			Point pt = contours[i][k];
			drawing = _mMatBuff[eImgDrawColor];
			line(drawing, Point(pt.x - 10, pt.y - 10), Point(pt.x + 10, pt.y + 10), Scalar(255, 255, 0), thickness, lineType);
			line(drawing, Point(pt.x + 10, pt.y - 10), Point(pt.x - 10, pt.y + 10), Scalar(255, 255, 0), thickness, lineType);
			drawing = _mMatBuff[eImgDebugColor];
			line(drawing, Point(pt.x - 10, pt.y - 10), Point(pt.x + 10, pt.y + 10), Scalar(255, 255, 0), thickness, lineType);
			line(drawing, Point(pt.x + 10, pt.y - 10), Point(pt.x - 10, pt.y + 10), Scalar(255, 255, 0), thickness, lineType);
		}
	}
	//imshow("Contours", drawing);
	_bShowResult = true;
	_bDebugResult = true;
	Invalidate(FALSE);

	return 0;
}


void COpenCVAppGUIDlg::AddString(LPCTSTR lpszLog)
{
	SendMessage(WM_ADD_STRING, 0, (LPARAM)lpszLog);
}


LRESULT COpenCVAppGUIDlg::OnAddString(WPARAM wParam, LPARAM lParam)
{
	if (!GetSafeHwnd()) return 0;

	if (_listBoxlog.GetCount() > 500)
	{
		_listBoxlog.ResetContent();
	}

	LPCTSTR lpszLog = reinterpret_cast <LPCTSTR> (lParam);
	SYSTEMTIME t;
	GetLocalTime(&t);
	CString nStrMsg = _T("");
	nStrMsg += lpszLog;
	int nIdx = _listBoxlog.AddString(nStrMsg);
	_listBoxlog.SetTopIndex(_listBoxlog.GetCount() - 1);

	stringstream ssTime;
	time_t const now_c = time(NULL);
	//ssTime << put_time(localtime(&now_c), "%a %d %b %Y - %I_%M_%S%p");
	ssTime << put_time(localtime(&now_c), "%a %d %b %Y-%I_%M");
	string time_c = ssTime.str();

	ofstream file;
	string fileName;
	fileName += "log";
	fileName += ssTime.str();
	fileName += ".txt";

	file.open(fileName, ios::out | ios::app);
	file << nStrMsg << endl;
	file.close();

	return 0;
}


int COpenCVAppGUIDlg::OnInspSegmentColor()
{
	Mat src_color = _mMatBuff[eImgSrcColor];

	Mat src_hsv;
	// Convert from BGR to HSV colorspace
	cvtColor(src_color, src_hsv, COLOR_BGR2HSV);

	const int max_value_H = 360 / 2;
	const int max_value = 255;
	int low_H = 0, low_S = 0, low_V = 0;
	int high_H = max_value_H, high_S = max_value, high_V = max_value;

	// Detect the object based on HSV Range Values
	Mat src_hsv_threshold_red, src_hsv_threshold_green, src_hsv_threshold_blue;

	low_H = 160; high_H = 180;
	inRange(src_hsv, Scalar(low_H, low_S, low_V), Scalar(high_H, high_S, high_V), src_hsv_threshold_red);
	low_H = 20; high_H = 60;
	inRange(src_hsv, Scalar(low_H, low_S, low_V), Scalar(high_H, high_S, high_V), src_hsv_threshold_green);
	low_H = 80; high_H = 110;
	inRange(src_hsv, Scalar(low_H, low_S, low_V), Scalar(high_H, high_S, high_V), src_hsv_threshold_blue);

	cvtColor(src_hsv_threshold_blue, _mMatBuff[eImgDebugColor], COLOR_GRAY2BGR);


	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	findContours(src_hsv_threshold_blue, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);

	Mat drawing = _mMatBuff[eImgDebugColor];

	for (size_t i = 0; i < contours.size(); i++)
	{
		RotatedRect rt = minAreaRect(contours[i]);
		double area = contourArea(contours[i]);
		double perimeter = arcLength(contours[i], true);
		double circularity = 4 * CV_PI * area / (perimeter * perimeter);
		ostringstream ss;
		ss << std::fixed;
		ss << "[";
		ss << to_string(i + 1);
		ss << "]";
		ss << " area = ";
		ss << std::setprecision(3) << area;
		ss << " perimeter = ";
		ss << std::setprecision(3) << perimeter;
		ss << " circularity = ";
		ss << std::setprecision(3) << circularity;
		string ssTxt = ss.str();
		AddString(ssTxt.c_str());


		ostringstream tag;
		tag << "[";
		tag << to_string(i + 1);
		tag << "]";
		putText(drawing, tag.str(), rt.boundingRect().tl(), CV_FONT_HERSHEY_TRIPLEX, 0.6, Scalar(255, 255, 255));
	}

	_bShowResult = true;
	_bDebugResult = true;
	Invalidate(FALSE);

	return 0;
}

int COpenCVAppGUIDlg::OnInspMorpology()
{
	/*Mat src_color = _mMatBuff[eImgSrcColor];
	Mat src_hsv;
	cvtColor(src_color, src_hsv, COLOR_BGR2HSV);*/

	Mat src_gray = _mMatBuff[eImgSrcGray]; // 그레이로 변환
	Mat src_invert = ~src_gray; // 그레이 색을 invert
	const int max_value_H = 360 / 2;
	const int max_value = 255;
	int low_H = 0, low_S = 0, low_V = 0;
	int high_H = max_value_H, high_S = max_value, high_V = max_value;
	Mat src_hsv_threshold_red, src_hsv_threshold_green, src_hsv_threshold_blue;
	low_H = 80; high_H = 110;
	inRange(src_invert, Scalar(low_H, low_S, low_V), Scalar(high_H, high_S, high_V), src_hsv_threshold_blue);

	//Erosion...침식
	int kernel_type = MORPH_RECT;// 사각형 모양의 구조요소 

	int kernel_size = 1;
	Mat element = getStructuringElement(kernel_type,
		Size(2 * kernel_size + 1, 2 * kernel_size + 1),
		Point(kernel_size, kernel_size));
	Mat src_erode;
	erode(src_invert, src_erode, element);
	//Dialation...팽창
	Mat diff = src_invert - src_erode;
	Mat res;
	threshold(src_erode, res, 100, 255, ThresholdTypes::THRESH_BINARY);
	Mat src_final;
	erode(res, src_final, element); // input, output
	erode(src_final, src_erode, element);

	dilate(src_erode, src_final, Mat());
	dilate(src_final, src_erode, Mat()); // 최종 파일은 src_erode
	


	// findcontour 시작
	int thresh = 128;
	RNG rng(12345);

	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	findContours(src_erode, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);

	cvtColor(_mMatBuff[eImgDebugGray], _mMatBuff[eImgDebugColor], COLOR_GRAY2BGR);
	Mat drawing = _mMatBuff[eImgDebugColor];

	for (size_t i = 0; i < contours.size(); i++)
	{
		RotatedRect rt = minAreaRect(contours[i]);
		double area = contourArea(contours[i]);
		double perimeter = arcLength(contours[i], true);
		double circularity = 4 * CV_PI * area / (perimeter * perimeter);
		ostringstream ss;
		ss << std::fixed;
		ss << "[";
		ss << to_string(i + 1);
		ss << "]";
		ss << " area = ";
		ss << std::setprecision(3) << area;
		ss << " perimeter = ";
		ss << std::setprecision(3) << perimeter;
		ss << " circularity = ";
		ss << std::setprecision(3) << circularity;
		string ssTxt = ss.str();
		AddString(ssTxt.c_str());

		Scalar color = Scalar(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));
		drawContours(drawing, contours, (int)i, color, 2, LINE_8, hierarchy, 0);
		ostringstream tag;
		tag << "[";
		tag << to_string(i + 1);
		tag << "]";
		putText(drawing, tag.str(), rt.boundingRect().tl(), CV_FONT_HERSHEY_TRIPLEX, 0.6, Scalar(255, 255, 255));
	}


	_bShowResult = true;
	_bDebugResult = true;

	Invalidate(FALSE);

	return 0;
}

int COpenCVAppGUIDlg::OnInspHistogram()
{
	
	Mat src_gray = _mMatBuff[eImgSrcGray]; 

	int hist[256] = { 0, };
	for (size_t row = 0; row < src_gray.rows; row++)
	{
		for (size_t col = 0; col < src_gray.cols; col++)
		{
			int index = row * src_gray.cols + col;
			int data = src_gray.data[index];
			hist[data]++;
		}
	}



	cvtColor(src_gray, _mMatBuff[eImgDebugColor], COLOR_GRAY2BGR);
	Mat drawing = _mMatBuff[eImgDebugColor];
	for (size_t i = 0; i < 256; i++)
	{
		line(drawing, Point(0, i*2), Point(hist[i]/7, i*2), Scalar(0, 255, 255), 2, LINE_8);
	}


	_bShowResult = true;
	_bDebugResult = true;

	Invalidate(FALSE);
	return 0;
}

int COpenCVAppGUIDlg::OnInspHistoEqulization()
{
	_bDebugResult = _bShowResult = false;

	Mat src_gray = _mMatBuff[eImgSrcGray];

	const int histo_max = 256;
	int histo[histo_max] = { 0, };
	int cumulative_freq[histo_max] = { 0, };
	int new_gray_value[histo_max] = { 0, };
	//get histogram :: 히스토그램
	for (size_t i = 0; i < src_gray.cols * src_gray.rows; i++) histo[src_gray.data[i]]++;

	//get cumulative frequence :: 누적분포
	cumulative_freq[0] = histo[0];
	//for (size_t i = 1; i < histo_max; i++) cumulative_freq[i]=histo[i] + cumulative_freq[i-1];

	//get new value
	int acc = 0;
	for (size_t i = 0; i < histo_max; i++)
	{
		acc += histo[i];
		cumulative_freq[i] = acc;
		//new_gray_value[i] = round((((float)cumulative_freq[i]) * 255) / src_gray.cols * src_gray.rows);
		new_gray_value[i] = round((((float)acc) * 255) / (src_gray.cols * src_gray.rows));
	}

	//drawing...histo debug color area
	int thickness = 1;
	int lineType = LINE_8;

	cvtColor(_mMatBuff[eImgSrcGray], _mMatBuff[eImgDebugColor], ColorConversionCodes::COLOR_GRAY2BGR);

	Mat debug_draw = _mMatBuff[eImgDebugColor];
	//draw   |------>
	bool view_horizontal = false;
	bool view_vertical = true;
	if (view_horizontal)
	{
		for (size_t row = 0; row < histo_max; row++)
		{
			line(debug_draw, Point(0, row * 2), Point(histo[row] / 10, row * 2), Scalar(255, 0, 255), thickness, lineType);
		}
	}

	if (view_vertical)
	{
		int height = src_gray.rows;
		for (size_t col = 0; col < histo_max; col++)
		{
			//draw histo
			Point pt1 = Point(col * 2, height - 1);//start
			Point pt2 = Point(col * 2, height - 1 - histo[col] / 10);//end
			line(debug_draw, pt1, pt2, Scalar(0, 255, 128), thickness, lineType);
		}


		// Equalization start with red line
		int max_cumulate = cumulative_freq[histo_max - 1];
		for (size_t col = 0; col < histo_max; col++)
		{
			if (col == 0)
			{
				int scaled_v = (cumulative_freq[col] / max_cumulate) * height;
				Point pt1 = Point(col * 2, scaled_v);//start
				Point pt2 = Point(col * 2, scaled_v);//end
				line(debug_draw, pt1, pt2, Scalar(0, 0, 255), thickness, lineType);
				continue;
			}
			//draw cumulate
			int scaled_v1 = (cumulative_freq[col - 1] * 1.0 / max_cumulate) * height;
			int scaled_v2 = (cumulative_freq[col] * 1.0 / max_cumulate) * height;
			Point pt1 = Point(col * 2, height - scaled_v1);//start
			Point pt2 = Point(col * 2, height - scaled_v2);//end
			line(debug_draw, pt1, pt2, Scalar(0, 0, 255), thickness, lineType);

		}
	}



	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	Mat src_gray_histoEqual = _mMatBuff[eImgSrcGray].clone();
	for (size_t i = 0; i < src_gray.cols * src_gray.rows; i++)
	{
		src_gray_histoEqual.data[i] = new_gray_value[src_gray.data[i]];
	}
	cvtColor(src_gray_histoEqual, _mMatBuff[eImgDrawColor], ColorConversionCodes::COLOR_GRAY2BGR);



	//get histogram :: 히스토그램
	for (size_t i = 0; i < src_gray.cols * src_gray.rows; i++) histo[src_gray_histoEqual.data[i]]++;

	//get cumulative frequence :: 누적분포
	cumulative_freq[0] = histo[0];
	//for (size_t i = 1; i < histo_max; i++) cumulative_freq[i]=histo[i] + cumulative_freq[i-1];

	//get new value
	acc = 0;
	for (size_t i = 0; i < histo_max; i++)
	{
		acc += histo[i];
		cumulative_freq[i] = acc;
		//new_gray_value[i] = round((((float)cumulative_freq[i]) * 255) / src_gray.cols * src_gray.rows);
		new_gray_value[i] = round((((float)acc) * 255) / (src_gray.cols * src_gray.rows));
	}

	//drawing...histo debug color area
	thickness = 1;
	lineType = LINE_8;


	Mat color_draw = _mMatBuff[eImgDrawColor];
	//draw   |------>
	view_horizontal = false;
	view_vertical = true;
	if (view_horizontal)
	{
		for (size_t row = 0; row < histo_max; row++)
		{
			line(color_draw, Point(0, row * 2), Point(histo[row] / 10, row * 2), Scalar(255, 0, 255), thickness, lineType);
		}
	}

	// color draw 안에 히스토 그래프 시작

	if (view_vertical)
	{
		int height = src_gray.rows;
		for (size_t col = 0; col < histo_max; col++)
		{
			//draw histo
			Point pt1 = Point(col * 2, height - 1);//start
			Point pt2 = Point(col * 2, height - 1 - histo[col] / 13);//end
			line(color_draw, pt1, pt2, Scalar(0, 255, 128), thickness, lineType);
		}

		int max_cumulate = cumulative_freq[histo_max - 1];
		for (size_t col = 0; col < histo_max; col++)
		{
			if (col == 0)
			{
				int scaled_v = (cumulative_freq[col] / max_cumulate) * height;
				Point pt1 = Point(col * 2, scaled_v);//start
				Point pt2 = Point(col * 2, scaled_v);//end
				line(color_draw, pt1, pt2, Scalar(0, 0, 255), thickness, lineType);
				continue;
			}
			//draw cumulate
			int scaled_v1 = (cumulative_freq[col - 1] * 1.0 / max_cumulate) * height;
			int scaled_v2 = (cumulative_freq[col] * 1.0 / max_cumulate) * height;
			Point pt1 = Point(col * 2, height - scaled_v1);//start
			Point pt2 = Point(col * 2, height - scaled_v2);//end
			line(color_draw, pt1, pt2, Scalar(0, 0, 255), thickness, lineType);

		}
	}

	_bDebugResult = _bShowResult = true;

	Invalidate(FALSE);
	return 0;
}

int COpenCVAppGUIDlg::OnInspCorrection()
{
	_bDebugResult = _bShowResult = false;
	double minV, maxV;
	Mat src_gray = _mMatBuff[eImgSrcGray];//얕은복사...주소값이 같다


	Mat src_Color = _mMatBuff[eImgSrcColor];
	OnDrawHistogram(src_gray, src_Color);

	putText(src_Color, string("Original"), Point(10, 50), CV_FONT_HERSHEY_TRIPLEX, 0.6, Scalar(0, 255, 255));

	string msg = "";

	msg = "[ Left ] Original Histogram";
	cv::minMaxLoc(src_gray, &minV, &maxV);
	msg += format("  min Value = {:0.3f}", minV);
	msg += format("  max Value = {:0.3f}", maxV);

	AddString(msg.c_str());

	//1.각 픽셀 밝기를 + 30 만큼 증가하시오
	//새로운 이미지 버퍼를 생성
	Mat src_gray_add = cv::Mat(src_gray.size(), src_gray.type()/*CV_8UC1*/);
	src_gray_add = 0;
	//초기값이 0인 버퍼가 생성

	//src_gray_add = src_gray.clone();//깊은복사...주소값이 달라짐. 데이타는 같다


	int add_value = 30;
	uchar* pData = src_gray.data;//원본
	for (size_t row = 0; row < src_gray.rows; row++)
	{
		for (size_t col = 0; col < src_gray.cols; col++)
		{
			uchar* pDataAdd = src_gray_add.data;//목적
			pDataAdd[row * src_gray.cols + col] = pData[row * src_gray.cols + col];
			//1   =   1
			if (pDataAdd[row * src_gray.cols + col] + add_value > 255)
				pDataAdd[row * src_gray.cols + col] = 255;
			else
				pDataAdd[row * src_gray.cols + col] += add_value;//255보다 크다?  256->1 300->45
			//a = b
			//a += 30
			//uchar ... 용량...0~255 [256] 
		}
	}

	for (size_t i = 0; i < src_gray.total(); i++)
	{
		uchar* pDataAdd = src_gray_add.data;//목적
		pDataAdd[i] = pData[i];
		if (pDataAdd[i] + add_value > 255)
			pDataAdd[i] = 255;
		else
			pDataAdd[i] += add_value;//255보다 크다?  256->1 300->45
	}

	Mat src_gray_matrix_add = cv::Mat(src_gray.size(), src_gray.type()/*CV_8UC1*/);
	//src_gray.copyTo(src_gray_matrix_add);
	//src_gray_matrix_add += add_value;
	src_gray_matrix_add = src_gray * 1 + add_value;

	Mat debugColor = _mMatBuff[eImgDebugColor];
	cvtColor(src_gray_matrix_add, debugColor, COLOR_GRAY2BGR);
	OnDrawHistogram(src_gray_matrix_add, debugColor);
	putText(debugColor, string("Math Add + 30"), Point(10, 50), CV_FONT_HERSHEY_TRIPLEX, 0.6, Scalar(0, 255, 255));

	msg = "";
	msg = "[ Center ] Add 30 Histogram";
	cv::minMaxLoc(src_gray_matrix_add, &minV, &maxV);
	msg += format("  min Value = {:0.3f}", minV);
	msg += format("  max Value = {:0.3f}", maxV);

	AddString(msg.c_str());


	//2.각 픽셀 밝기를 1.5배만큼 증가하시오
	//3.각 픽셀 밝기를 1.24배하고 20만큼 증가하시오
	Mat src_gray_matrix_op = cv::Mat(src_gray.size(), src_gray.type()/*CV_8UC1*/);
	double a = 1.24;
	int b = 20;
	src_gray_matrix_op = src_gray * a + b;



	//Gamma Correction
	// LUT : Look Up Table
	//int histo[256] = { 0, };
	int LUT[256] = { 0, };
	// .... 0 -> LUT[0] -> 10
	// .... 2 -> LUT[2] -> 12
	//수식변환공식의 생략 ... LUT
	//𝑠 = 255×(𝑟 / 255)^𝛾
	double gamma = 0.4;
	for (size_t i = 0; i < 256; i++)
	{
		LUT[i] = std::pow(i / 255.0, gamma) * 255.0;
	}


	// 
	// 
	//Mat src_gray_gamma = cv::Mat(src_gray.size(), src_gray.type()/*CV_8UC1*/);
	//src_gray_gamma = 0;

	Mat src_gray_gamma = cv::Mat::zeros(src_gray.size(), src_gray.type()/*CV_8UC1*/);
	for (size_t i = 0; i < src_gray.total(); i++)
	{
		uchar* pDataGamma = src_gray_gamma.data;//목적
		pDataGamma[i] = LUT[pData[i]];
	}


	Mat drawColor = _mMatBuff[eImgDrawColor];
	cvtColor(src_gray_gamma, drawColor, COLOR_GRAY2BGR);
	OnDrawHistogram(src_gray_gamma, drawColor);
	putText(drawColor, string("Gamma r 0.4"), Point(10, 50), CV_FONT_HERSHEY_TRIPLEX, 0.6, Scalar(0, 255, 255));

	msg = "";
	msg = "[ Right ] gamma 0.4 Histogram";
	cv::minMaxLoc(src_gray_gamma, &minV, &maxV);
	msg += format("  min Value = {:0.3f}", minV);
	msg += format("  max Value = {:0.3f}", maxV);

	AddString(msg.c_str());

	_bDebugResult = _bShowResult = true;

	Invalidate(FALSE);
	return 0;
}

int COpenCVAppGUIDlg::OnInspSearchingContour()
{
	//아래 사각형의 Contour를 구하시오
	vector<vector<Point>> Contours;
	vector<Point> Contour;
	Contours.clear();
	Contour.clear();

	const int cols = 10;
	const int rows = 10;
	uchar buff[rows * cols] = {
		0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,
		0,0,0,1,1,1,1,0,0,0,
		0,0,0,1,1,1,1,0,0,0,
		0,0,0,1,1,1,1,0,0,0,
		0,0,0,1,1,1,1,0,0,0,
		0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,
	};

	uchar buff_label[rows * cols] = {
		0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,
	};
	Mat bufImg = Mat(rows, cols, CV_8UC1, buff);
	Mat bufLabel = Mat(rows, cols, CV_8UC1, buff_label);
	bufImg *= 255;


	int label = 0;
	Point ptStart(0, 0);
	bool bStart = false;
	bool bFind = false;

	Contour.clear();
	bFind = false;
	for (size_t row = 0; row < rows; row++)
	{
		for (size_t col = 0; col < cols; col++)
		{
			int index = (row)*cols + (col);
			if (bufImg.data[index] == 255 && bufLabel.data[index] == 0)
			{
				bFind = true;
				bufLabel.data[index] = 255;
				ptStart = Point(col, row);
				Contour.push_back(ptStart);
			}
			if (bFind)
			{
				break;
			}
		}
		if (bFind)
		{
			break;
		}

	}

	//enum eDIR {eEE, eEN,eNN, eWN, eWW, eWS, eSS, eES, eDirMax};
	enum eDIR { eEE, eES, eSS, eWS, eWW, eWN, eNN, eEN, eDirMax };
	vector<Point> vDir(eDirMax);
	vDir[(int)eEE] = Point(1, 0);
	vDir[(int)eEN] = Point(1, -1);
	vDir[(int)eNN] = Point(0, -1);
	vDir[(int)eWN] = Point(-1, -1);
	vDir[(int)eWW] = Point(-1, 0);
	vDir[(int)eWS] = Point(-1, 1);
	vDir[(int)eSS] = Point(0, 1);
	vDir[(int)eES] = Point(1, 1);

	int dir = eEE;
	Point ptCur = ptStart;

	do
	{
		bFind = false;
		Point ptNext = ptCur + vDir[dir];
		if (ptStart == ptNext)
			break;
		//search cross
		if (bufImg.data[(ptNext.y) * cols + (ptNext.x)] == 255 &&
			bufLabel.data[(ptNext.y) * cols + (ptNext.x)] != 255)
		{
			bufLabel.data[(ptNext.y) * cols + (ptNext.x)] = 255;
			bFind = true;
			Contour.push_back(ptNext);
		}
		else
		{
			dir++;
		}
		if (bFind)
		{
			ptCur = ptNext;
			//dir = eEE;
		}


	} while (true);

	for (size_t i = 1; i < Contour.size(); i++)
	{
		Point pre = Contour[i - 1];
		Point cur = Contour[i];
		double diff_pre = sqrt((pre.x - cur.x) * (pre.x - cur.x) + (pre.y - cur.y) * (pre.y - cur.y));
		if (diff_pre == 1 && pre.y == cur.y)
		{
			Contour.erase(Contour.begin() + i);
		}
		if (diff_pre == 1 && pre.x == cur.x)
		{
			Contour.erase(Contour.begin() + i);
		}
	}

	Contours.push_back(Contour);

	for (auto& contour : Contours)
	{
		for (auto& iter : contour)
		{
			string msg = "";
			msg = "x, y = ";
			msg += format("{:d}, {:d}", iter.x, iter.y);
			AddString(msg.c_str());
		}
	}
	return 0;
}
int COpenCVAppGUIDlg::OnDrawHistogram(const Mat& src_gray, Mat& draw_color)
{
	const int histo_max = 256;
	int histo[histo_max] = { 0, };

	//get histogram :: 히스토그램
	for (size_t i = 0; i < src_gray.cols * src_gray.rows; i++) histo[src_gray.data[i]]++;

	//drawing...histo debug color area
	double thickness = 1;
	int lineType = LINE_8;

	Mat color_draw = draw_color;
	//draw   |------>
	int height = src_gray.rows;
	for (size_t col = 0; col < histo_max; col++)
	{
		//draw histo
		Point pt1 = Point(col * 2, height - 1);//start
		Point pt2 = Point(col * 2, height - 1 - histo[col] / 10);//end
		line(color_draw, pt1, pt2, Scalar(0, 255, 128), thickness, lineType);
	}

	return 1;
}