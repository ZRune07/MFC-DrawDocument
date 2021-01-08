#pragma once
#include "drawData.h"

// wxMdiView2 视图

class wxMdiView2 : public CEditView
{
	DECLARE_DYNCREATE(wxMdiView2)

protected:
	wxMdiView2();           // 动态创建所使用的受保护的构造函数
	virtual ~wxMdiView2();

public:
	virtual void OnDraw(CDC* pDC);
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	drawData* m_drawData;
	bool Lbrndown=FALSE;//标记左键是否按下
	CPoint m_ptOrigin,m_ptEnd;//标记左键按下时的位置
	CPoint ptStart,ptEnd, ptEnd1;
	bool TrackStop=false;//停止绘图标记
	int drawtype = 0;//设置图形样式
	COLORREF m_color = RGB(255, 0, 0);
	double lineWidth = 2.0;
	bool arctag = true;

	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnChangeDrawType(UINT nID);
	afx_msg void OnLine();
	afx_msg void OnCircle();
	afx_msg void OnSector();
	afx_msg void OnRectangular();
	afx_msg void Oncolor();
	afx_msg void Onwidthset1();
	afx_msg void OnPaint();
};


