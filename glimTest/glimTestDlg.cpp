#include "pch.h"
#include "framework.h"
#include "glimTest.h"
#include "glimTestDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif



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

// CglimTestDlg 대화 상자
CglimTestDlg::CglimTestDlg(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_GLIMTEST_DIALOG, pParent),
    m_hIcon(AfxGetApp()->LoadIcon(IDR_MAINFRAME))
{
    //m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CglimTestDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CglimTestDlg, CDialogEx)
    ON_WM_SYSCOMMAND()
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDC_BTN_IMAGE, &CglimTestDlg::OnBnClickedBtnImage)
    ON_BN_CLICKED(IDC_BTN_ACTION1, &CglimTestDlg::OnBnClickedBtnAction1)
    ON_BN_CLICKED(IDC_BTN_ACTION2, &CglimTestDlg::OnBnClickedBtnAction2)
    ON_BN_CLICKED(IDC_BTN_ACTION3, &CglimTestDlg::OnBnClickedBtnAction3)
    ON_BN_CLICKED(IDC_BTN_ACTION4, &CglimTestDlg::OnBnClickedBtnAction4)
END_MESSAGE_MAP()
// CglimTestDlg 메시지 처리기
BOOL CglimTestDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.
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

    // 이 대화 상자의 아이콘을 설정합니다.
    SetIcon(m_hIcon, TRUE);
    SetIcon(m_hIcon, FALSE);

    return TRUE;
}

void CglimTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CglimTestDlg::OnPaint()
{
    if (IsIconic())
    {
        CPaintDC dc(this);
        
        SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);
        
        int cxIcon = GetSystemMetrics(SM_CXICON);
        int cyIcon = GetSystemMetrics(SM_CYICON);
        
        CRect rect;
        GetClientRect(&rect);
        int x = (rect.Width() - cxIcon + 1) / 2;
        int y = (rect.Height() - cyIcon + 1) / 2;
        
        dc.DrawIcon(x, y, m_hIcon);
    }
    else
    {        
        CDialogEx::OnPaint();
    }
}

HCURSOR CglimTestDlg::OnQueryDragIcon()
{
    return static_cast<HCURSOR>(m_hIcon);
}

void CglimTestDlg::OnBnClickedBtnImage()
{
    // 이미지의 너비, 높이, 비트당 픽셀 수(Bits Per Pixel, BPP)를 정의합니다.
    int nWidth = 640;
    int nHeight = 480;
    int nBpp = 8;

    // 이미지를 생성합니다.
    m_image.Create(nWidth, -nHeight, nBpp);

    // 8비트 컬러 이미지를 위한 컬러 테이블을 설정합니다.
    if (nBpp == 8) {
        static RGBQUAD rgb[256];
        for (int i = 0; i < 256; i++)
            rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = i;
        m_image.SetColorTable(0, 256, rgb);
    }

    // 이미지의 픽셀 레이아웃 정보를 가져옵니다.
    int nPitch = m_image.GetPitch();

    // 이미지의 픽셀 데이터에 접근합니다.
    unsigned char* fm = (unsigned char*)m_image.GetBits();

    // 이미지의 모든 픽셀을 흰색(0xff)으로 초기화합니다.
    memset(fm, 0xff, nWidth * nHeight);

    // 이미지를 화면에 업데이트합니다.
    UpdateDisplay();
}

void CglimTestDlg::UpdateDisplay()
{
    // 클라이언트 디바이스 컨텍스트(Client Device Context)를 생성합니다. 이는 화면에 그림을 그리기 위한 것입니다.
    CClientDC dc(this);

    // m_image 객체의 Draw 함수를 호출하여, 이미지를 (0, 0) 위치에 그립니다.
    m_image.Draw(dc, 0, 0);
}

void CglimTestDlg::moveRect()
{
    // 회색조의 값을 정의합니다.
    int nGray = 80;

    // 이미지의 너비, 높이, 픽셀 레이아웃 정보를 가져옵니다.
    int nWidth = m_image.GetWidth();
    int nHeight = m_image.GetHeight();
    int nPitch = m_image.GetPitch();

    // 사용자 인터페이스로부터 원의 반지름을 가져옵니다.
    int nRadius = GetDlgItemInt(IDC_INPUT_RADIUS);

    // 시작 위치를 랜덤하게 정합니다.
    int nSttX = rand() % (nWidth - 2 * nRadius);
    int nSttY = rand() % (nHeight - 2 * nRadius);

    // 이미지의 픽셀 데이터에 접근합니다.
    unsigned char* fm = (unsigned char*)m_image.GetBits();

    // 십자가의 크기를 정합니다.
    int nSize = 20;

    // 윈도우를 다시 그립니다.
    RedrawWindow();

    // 이미지의 모든 픽셀을 흰색(0xff)으로 초기화합니다.
    memset(fm, 0xff, nWidth * nHeight);

    // drawCircle 함수를 사용하여 원을 그립니다.
    drawCircle(fm, nSttX, nSttY, nRadius, nGray);

    // drawCross 함수를 사용하여 십자가를 그립니다.
    drawCross(fm, nSttX + nRadius, nSttY + nRadius, nSize, nGray);

    // findCenter 함수를 사용하여 중심점을 찾습니다.
    CPoint ptCenter = findCenter();

    // 중심점에 노란색 원을 그리는 함수를 호출합니다.    
    drawYellowCircle(ptCenter, nRadius);
}

void CglimTestDlg::moveHexa()
{
    // 회색조의 값을 정의합니다.
    int nGray = 80;

    // 이미지의 너비, 높이, 픽셀 레이아웃 정보를 가져옵니다.
    int nWidth = m_image.GetWidth();
    int nHeight = m_image.GetHeight();
    int nPitch = m_image.GetPitch();

    // 사용자 인터페이스로부터 원의 반지름을 가져옵니다.
    int nRadius = GetDlgItemInt(IDC_INPUT_RADIUS);

    // 시작 위치를 랜덤하게 정합니다.
    int nSttX = rand() % (nWidth - 2 * nRadius);
    int nSttY = rand() % (nHeight - 2 * nRadius);

    // 이미지의 픽셀 데이터에 접근합니다.
    unsigned char* fm = (unsigned char*)m_image.GetBits();

    // 윈도우를 다시 그립니다.
    RedrawWindow();

    // 이미지의 모든 픽셀을 흰색(0xff)으로 초기화합니다.
    memset(fm, 0xff, nWidth * nHeight);

    drawHexagon(fm, nSttX, nSttY, nRadius, nGray);
    // findCenter 함수를 사용하여 중심점을 찾습니다.
    CPoint ptCenter = findCenter();
    // 중심점에 노란색 원을 그리는 함수를 호출합니다.    
    drawYellowCircle(ptCenter, nRadius);
}

void CglimTestDlg::moveTri()
{
    // 회색조의 값을 정의합니다.
    int nGray = 80;

    // 이미지의 너비, 높이, 픽셀 레이아웃 정보를 가져옵니다.
    int nWidth = m_image.GetWidth();
    int nHeight = m_image.GetHeight();
    int nPitch = m_image.GetPitch();

    // 사용자 인터페이스로부터 원의 반지름을 가져옵니다.
    int nRadius = GetDlgItemInt(IDC_INPUT_RADIUS);

    // 시작 위치를 랜덤하게 정합니다.
    int nSttX = rand() % (nWidth - 2 * nRadius);
    int nSttY = rand() % (nHeight - 2 * nRadius);

    // 이미지의 픽셀 데이터에 접근합니다.
    unsigned char* fm = (unsigned char*)m_image.GetBits();

    RedrawWindow();

    // 이미지의 모든 픽셀을 흰색(0xff)으로 초기화합니다.
    memset(fm, 0xff, nWidth * nHeight);

    drawTriangle(fm, nSttX, nSttY, nRadius, nGray);

    // findCenter 함수를 사용하여 중심점을 찾습니다.
    CPoint ptCenter = findCenter();

    // 중심점에 노란색 원을 그리는 함수를 호출합니다.    
    drawYellowCircle(ptCenter, nRadius);
}

void CglimTestDlg::makeSnow()
{
    int nWidth = m_image.GetWidth();
    int nHeight = m_image.GetHeight();
    int nPitch = m_image.GetPitch();

    unsigned char* fm = (unsigned char*)m_image.GetBits();
    RedrawWindow();

    // 각 행마다 메모리 초기화
    memset(fm, 0x50, nWidth * nHeight);

    int snowMaxDensity = GetDlgItemInt(IDC_INPUT_RADIUS);; // 반지름 길이가 여기서는 눈송이 개수
    int snowColor = 0xff; // 8비트 그레이스케일에서 흰색

    for (int k = 0; k < snowMaxDensity; k++) {
        int x = rand() % nWidth;
        int y = rand() % nHeight;
        int snowSize = rand() % 3 + 1; 

        // 눈송이 그리기
        for (int i = -snowSize; i <= snowSize; i++) {
            for (int j = -snowSize; j <= snowSize; j++) {
                if (x + i >= 0 && x + i < nWidth && y + j >= 0 && y + j < nHeight) {
                    fm[(y + j) * nPitch + (x + i)] = snowColor;
                }
            }
        }
    }
    // 화면 갱신
    UpdateDisplay();
}


void CglimTestDlg::OnBnClickedBtnAction1()
{
    moveRect();
}

void CglimTestDlg::OnBnClickedBtnAction2()
{
    moveHexa();
}

void CglimTestDlg::OnBnClickedBtnAction3()
{
    moveTri();
}

void CglimTestDlg::OnBnClickedBtnAction4()
{
    makeSnow();
}

BOOL CglimTestDlg::validImgPos(int x, int y)
{
    // 이미지의 너비와 높이를 가져옵니다.
    int nWidth = m_image.GetWidth();
    int nHeight = m_image.GetHeight();

    // 이미지의 전체 영역을 나타내는 사각형을 정의합니다.
    CRect rect(0, 0, nWidth, nHeight);

    // 주어진 좌표가 이 사각형 내에 있는지 확인합니다.
    return rect.PtInRect(CPoint(x, y));
}

void CglimTestDlg::drawCircle(unsigned char* fm, int x, int y, int nRadius, int nGray)
{
    // DC(Client Device Context)를 생성합니다. 
    CClientDC dc(this);

    // 원의 중심 좌표를 계산합니다.
    int nCenterX = x + nRadius;
    int nCenterY = y + nRadius;

    // 이미지의 픽셀 레이아웃 정보를 가져옵니다.
    int nPitch = m_image.GetPitch();

    // 원을 그리기 위해 반지름만큼의 영역을 순회합니다.
    for (int j = y; j < y + nRadius * 2; j++) {
        for (int i = x; i < x + nRadius * 2; i++) {
            // isInCircle 함수를 사용하여 원 내부에 있는지 확인합니다.
            if (isInCircle(i, j, nCenterX, nCenterY, nRadius))
                fm[j * nPitch + i] = nGray;
        }
    }

    // 이미지를 업데이트합니다.
    UpdateDisplay();
}

void CglimTestDlg::drawHexagon(unsigned char* fm, int x, int y, int nRadius, int nGray)
{
    // DC(Client Device Context)를 생성합니다. 
    CClientDC dc(this);

    // 6각형의 중심 좌표를 계산합니다.
    int nCenterX = x + nRadius;
    int nCenterY = y + nRadius;

    // 이미지의 픽셀 레이아웃 정보를 가져옵니다.
    int nPitch = m_image.GetPitch();
  
    // 6각형의 각 정점을 계산합니다.
    POINT hexPoints[6];
    for (int k = 0; k < 6; k++) {
        hexPoints[k].x = nCenterX + nRadius * cos(k * M_PI / 3);
        hexPoints[k].y = nCenterY + nRadius * sin(k * M_PI / 3);
    }

    // 6각형의 영역을 순회합니다.
    for (int j = y; j < y + nRadius * 2; j++) {
        for (int i = x; i < x + nRadius * 2; i++) {
            // isInHexagon 함수를 사용하여 6각형 내부에 있는지 확인합니다.
            if (isInHexagon(i, j, hexPoints))
                fm[j * nPitch + i] = nGray;
        }
    }

    // 이미지를 업데이트합니다.
    UpdateDisplay();
}

void CglimTestDlg::drawTriangle(unsigned char* fm, int x, int y, int nRadius, int nGray)
{
    // DC(Client Device Context)를 생성합니다. 
    CClientDC dc(this);

    // 삼각형의 중심 좌표를 계산합니다.
    int nCenterX = x + nRadius;
    int nCenterY = y + nRadius;

    // 이미지의 픽셀 레이아웃 정보를 가져옵니다.
    int nPitch = m_image.GetPitch();

    POINT triPoints[3];
    for (int k = 0; k < 3; k++) {
        triPoints[k].x = nCenterX + nRadius * cos(k * 2 * M_PI / 3);
        triPoints[k].y = nCenterY + nRadius * sin(k * 2 * M_PI / 3);
    }

    for (int j = y; j < y + nRadius * 2; j++) {
        for (int i = x; i < x + nRadius * 2; i++) {
            // isInTriangle 함수를 사용하여 삼각형 내부에 있는지 확인합니다.
            if (isInTriangle(i, j, triPoints))
                fm[j * nPitch + i] = nGray;
        }
    }

    // 이미지를 업데이트합니다.
    UpdateDisplay();
}

bool CglimTestDlg::isInCircle(int i, int j, int nCenterX, int nCenterY, int nRadius)
{
    // 반환할 값의 초기값을 false로 설정합니다.
    bool bRet = false;

    // 주어진 점과 원의 중심점 사이의 x축 및 y축 거리를 계산합니다.
    double dX = i - nCenterX;
    double dY = j - nCenterY;

    // 점과 중심점 사이의 거리의 제곱을 계산합니다.
    double dDist = dX * dX + dY * dY;

    // 점이 원의 테두리 근처에 있는지 확인합니다.
    // 이 조건은 원의 내부뿐만 아니라 특정 두께를 가진 원의 가장자리를 포함합니다.
    if (dDist <= nRadius * nRadius && dDist >= (nRadius - 5) * (nRadius - 5)) {
        bRet = true;
    }

    // 결과를 반환합니다.
    return bRet;
}

bool CglimTestDlg::isInHexagon(int x, int y, POINT hexPoints[6]) {
    int positive = 0;
    int negative = 0;
    // 6각형을 구성하는 각 선분에 대해 테스트
    for (int i = 0; i < 6; i++) {
        int j = (i + 1) % 6;
        int crossProduct = (hexPoints[j].x - hexPoints[i].x) * (y - hexPoints[i].y) -
            (hexPoints[j].y - hexPoints[i].y) * (x - hexPoints[i].x);

        if (crossProduct > 0) {
            positive++;
        } else if (crossProduct < 0) {
            negative++;
        } else {
            return false;
        }
    }
    // 모든 교차곱의 부호가 동일하면 내부에 있는 것으로 판단
    return positive == 0 || negative == 0;
}

bool CglimTestDlg::isInTriangle(int x, int y, POINT triPoints[3]) {
    int positive = 0;
    int negative = 0;
    //삼각형을 구성하는 각 선분에 대해 테스트
    for (int i = 0; i < 3; i++) {
        int j = (i + 1) % 3;
        int crossProduct = (triPoints[j].x - triPoints[i].x) * (y - triPoints[i].y) -
            (triPoints[j].y - triPoints[i].y) * (x - triPoints[i].x);

        if (crossProduct > 0)
        {
            positive++;
        }
        else if (crossProduct < 0)
        {
            negative++;
        }
        else
        {
            return false;
        }
    }
    // 모든 교차곱의 부호가 동일하면 내부에 있는 것으로 판단
    return positive == 0 || negative == 0;
}

void CglimTestDlg::drawCross(unsigned char* fm, int x, int y, int nSize, int nColor)
{
    // 이미지의 픽셀 레이아웃 및 크기 정보를 가져옵니다.
    int nPitch = m_image.GetPitch();
    int nWidth = m_image.GetWidth();
    int nHeight = m_image.GetHeight();

    // 십자가의 가로선을 그립니다.
    for (int i = x - nSize / 2; i < x + nSize / 2; i++) {
        // 그리는 위치가 이미지 범위 내인지 확인합니다.
        if (i >= 0 && i < nWidth) {
            fm[y * nPitch + i] = nColor;
        }
    }

    // 십자가의 세로선을 그립니다.
    for (int j = y - nSize / 2; j < y + nSize / 2; j++) {
        // 그리는 위치가 이미지 범위 내인지 확인합니다.
        if (j >= 0 && j < nHeight) {
            fm[j * nPitch + x] = nColor;
        }
    }

    // 이미지를 업데이트합니다.
    UpdateDisplay();
}

CPoint CglimTestDlg::findCenter()
{
    // 이미지의 픽셀 데이터에 접근하기 위해 포인터를 얻습니다.
    unsigned char* fm = (unsigned char*)m_image.GetBits();

    // 이미지의 너비와 높이를 가져옵니다.
    int nWidth = m_image.GetWidth();
    int nHeight = m_image.GetHeight();

    // 이미지의 한 줄(행)의 길이를 픽셀로 가져옵니다. 이는 이미지의 메모리 레이아웃을 위해 사용됩니다.
    int nPitch = m_image.GetPitch();

    // 이미지의 전체 영역을 나타내는 사각형을 생성합니다.
    CRect rect(0, 0, nWidth, nHeight);

    // 중심점의 X, Y 좌표와 픽셀의 수를 누적할 변수들을 초기화합니다.
    int nSumX = 0;
    int nSumY = 0;
    int nCount = 1;

    // 이미지의 모든 픽셀을 순회합니다.
    for (int j = rect.top; j < rect.bottom; j++)
    {
        for (int i = rect.left; i < rect.right; i++)
        {
            // 특정 조건(여기서는 픽셀 값이 0xff가 아닐 때)을 만족하는 픽셀의 좌표를 누적합니다.
            if (fm[j * nPitch + i] != 0xff)
            {
                nSumX += i;
                nSumY += j;
                nCount++;
            }
        }
    }

    // 누적된 좌표의 평균을 계산하여 중심점의 좌표를 구합니다.
    int nCenterX = nSumX / nCount;
    int nCenterY = nSumY / nCount;

    // 중심점을 반환합니다.
    return CPoint(nCenterX, nCenterY);
}

void CglimTestDlg::drawYellowCircle(CPoint ptCenter, int nRadius)
{
    CClientDC dc(this);
    drawCircleUsingTrig(&dc, ptCenter, nRadius, RGB(0xff, 0xff, 0x00));
}

void CglimTestDlg::drawCircleUsingTrig(CDC* pDC, CPoint ptCenter, int nRadius, COLORREF color)
{
    CPen pen;
    pen.CreatePen(PS_SOLID, 1, color); 
    CPen* pOldPen = pDC->SelectObject(&pen);

    // 0도부터 360도까지 각도를 변경하면서 원의 점을 계산합니다.
    for (double theta = 0; theta < 2 * M_PI; theta += 0.01) //theta 값으로 수치를 조정합니다.
    {
        int x = ptCenter.x + static_cast<int>((nRadius+10) * cos(theta));
        int y = ptCenter.y + static_cast<int>((nRadius+10) * sin(theta));

        pDC->SetPixel(x, y, color); // 계산된 위치에 픽셀을 그립니다.
    }

    pDC->SelectObject(pOldPen);
}