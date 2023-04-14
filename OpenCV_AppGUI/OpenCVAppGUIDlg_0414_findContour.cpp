
// OpenCVAppGUIDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "OpenCVAppGUI.h"
#include "OpenCVAppGUIDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#define NAME_WINDOW_SRC "srcView" // 첫번째 
#define NAME_WINDOW_Debug "srcDebug"// 두번째 
#define NAME_WINDOW_RESULT "srcResult"// 세번째 



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
}

BEGIN_MESSAGE_MAP(COpenCVAppGUIDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_LOAD, &COpenCVAppGUIDlg::OnBtnClickedBtnLoad)
	ON_BN_CLICKED(IDC_BTN_SAVE, &COpenCVAppGUIDlg::OnBtnClickedBtnSave)
	ON_BN_CLICKED(IDC_BTN_INSPECTION, &COpenCVAppGUIDlg::OnBnClickedBnInspection)
	ON_BN_CLICKED(IDC_BTN_INSPECTIONCV, &COpenCVAppGUIDlg::OnBnClickedBtnInspectioncv)
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







int COpenCVAppGUIDlg::OnInspection(InputArray src, OutputArray dst)
{

	return 0;
}

int COpenCVAppGUIDlg::OnInspection(Mat src, Mat dst)
{
	return 0;
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
	
	Mat src_gray = _mMatBuff[eImgSrcGray];
	int thresh = 20;
	RNG rng(12345);


	Mat thr_img;
	threshold(src_gray, thr_img,thresh,255, THRESH_BINARY);
	//Canny(src_gray, canny_output, thresh, thresh * 2);
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(thr_img, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);
//	Mat drawing = Mat::zeros(canny_output.size(), CV_8UC3);


	Mat drawing= _mMatBuff[eImgDebugColor];
//	canny_output.copyTo(_mMatBuff[eImgDebugGray]);
	cvtColor(_mMatBuff[eImgDebugGray], _mMatBuff[eImgDebugColor], COLOR_GRAY2BGR);
	for (size_t i = 0; i < contours.size(); i++)
	{
		Scalar color = Scalar(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));
		drawContours(drawing, contours, (int)i, color, -1, LINE_8, hierarchy, 0);
	}
	//for (size_t i = 0; i < contours.size(); i++)
	//{
	//	Scalar c((255, 0, 0), (0,255,0) ,(0,0,255));
	//	drawContours(drawing, contours, (int)i, c, 5, LINE_8, hierarchy, 0);
	//	// 이미지, 전체 백터, 인덱스 번호, 컬러, thickness, 외각선 타입)
	//}

	//Scalar c(0, 0, 255);
	//drawContours(drawing, contours, (int)0, c, 5, LINE_8, hierarchy, 0);
	//Scalar c1(0, 255, 0);
	//drawContours(drawing, contours, (int)1, c1, 5, LINE_8, hierarchy, 0);
	//Scalar c2(255,0, 0);
	//drawContours(drawing, contours, (int)2, c2, 5, LINE_8, hierarchy, 0);


	drawing = _mMatBuff[eImgDrawColor];
	for (size_t i = 0; i < contours.size(); i++)
	{
		Scalar color = Scalar(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));
		drawContours(drawing, contours, (int)i, color, 5, LINE_8, hierarchy, 0);
	}


	_bShowResult = true;
	_bDebugResult = true;
	Invalidate(FALSE);
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
int COpenCVAppGUIDlg::OnInspFindShapes()
{
	Mat src_gray = _mMatBuff[eImgSrcGray];
	int thresh = 50;

	RNG rng(12345);

	Mat thr_img;
	threshold(src_gray, thr_img, thresh, 255, THRESH_BINARY);

	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	findContours(thr_img, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);

	int circle_index = 0, triangle_index = 0, rectangle_index = 0;
	for (size_t i = 0; i < contours.size(); i++)
	{
		if (contours[i].size() >= 100 && contours[i].size() <= 150)
		{
			circle_index = i;
			continue;
		}
		else if (contours[i].size() == 4)
		{
			rectangle_index = i;
			continue;
		}
		else if (contours[i].size() >= 150)
		{
			triangle_index = i;
			continue;
		}

	}

	cvtColor(_mMatBuff[eImgDebugGray], _mMatBuff[eImgDebugColor], COLOR_GRAY2BGR);
	Mat drawing = _mMatBuff[eImgDebugColor];
	drawing = _mMatBuff[eImgDrawColor];

	drawContours(drawing, contours, (int)circle_index, Scalar(0, 0, 255), 2, LINE_8, hierarchy, 0);
	drawContours(drawing, contours, (int)rectangle_index, Scalar(255, 0, 0), 2, LINE_8, hierarchy, 0);
	drawContours(drawing, contours, (int)triangle_index, Scalar(0, 255, 0), 2, LINE_8, hierarchy, 0);

	Mat mask = _mMatBuff[eImgDrawColor].clone();
	mask = 0;
	drawContours(mask, contours, circle_index, Scalar(255, 255, 255), CV_FILLED, 8, hierarchy);
	drawing = drawing & mask;

	//imshow("Contours", drawing);
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