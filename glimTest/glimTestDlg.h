﻿#pragma once

// CglimTestDlg 대화 상자
class CglimTestDlg : public CDialogEx
{
private:
	CImage m_image;
	BOOL validImgPos(int x, int y);

	// 생성입니다.
public:
	CglimTestDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GLIMTEST_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


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
	afx_msg void OnBnClickedBtnImage();
	afx_msg void OnBnClickedBtnAction1();
	afx_msg void OnBnClickedBtnAction2();
	afx_msg void OnBnClickedBtnAction3();
	afx_msg void OnBnClickedBtnAction4();

	void moveRect();
	void moveHexa();
	void moveTri();
	void makeSnow();

	void UpdateDisplay();
	void drawCircle(unsigned char* fm, int i, int j, int nRadius, int nGray);
	void drawHexagon(unsigned char* fm, int i, int j, int nRadius, int nGray);
	void drawTriangle(unsigned char* fm, int i, int j, int nRadius, int nGray);
	void drawLine(unsigned char* fm, POINT start, POINT end, int color);
	void drawHexagonOutline(unsigned char* fm, int x, int y, int nRadius, int nGray);

	bool isInCircle(int i, int j, int nCenterX, int nCenterY, int nRadius);
	bool isInHexagon(int x, int y, POINT hexPoints[6]);
	bool isInTriangle(int x, int y, POINT triPoints[3]);
	void drawCross(unsigned char* fm, int x, int y, int nSize, int nColor);
	CPoint findCenter();
	void drawYellowCircle(CPoint ptCenter, int nRadius);
	void drawCircleUsingTrig(CDC* pDC, CPoint ptCenter, int nRadius, COLORREF color);
};