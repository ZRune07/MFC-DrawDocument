// wxMdiView2.cpp: 实现文件
//

#include "pch.h"
#include "wxMdi.h"
#include "wxMdiView2.h"
#include "wxMdiDoc2.h"
#include "dlgInput.h"


// wxMdiView2

IMPLEMENT_DYNCREATE(wxMdiView2, CEditView)

wxMdiView2::wxMdiView2()
{

}

wxMdiView2::~wxMdiView2()
{
}

BEGIN_MESSAGE_MAP(wxMdiView2, CEditView)

ON_WM_MOUSEMOVE()
ON_WM_LBUTTONDOWN()
ON_WM_LBUTTONDBLCLK()
ON_WM_LBUTTONUP()
ON_WM_PAINT()
ON_COMMAND(ID_Line, &wxMdiView2::OnLine)
ON_COMMAND(ID_Circle, &wxMdiView2::OnCircle)
ON_COMMAND(ID_Sector, &wxMdiView2::OnSector)
ON_COMMAND(ID_Rectangular, &wxMdiView2::OnRectangular)
ON_COMMAND(ID_color, &wxMdiView2::Oncolor)
ON_COMMAND(ID_widthset, &wxMdiView2::Onwidthset1)

END_MESSAGE_MAP()


void wxMdiView2::OnDraw(CDC* pDC)
{
    // TODO: 在此添加专用代码和/或调用基类
    wxMdiDoc2* pDoc = (wxMdiDoc2*)GetDocument();
    for (int i = 0; i < pDoc->m_data.GetCount(); i++)
    {
        m_drawData = (drawData*)(pDoc->m_data.GetAt(i));
        CPen pen(PS_SOLID, m_drawData->width, m_drawData->color);
        pDC->SelectObject(pen);
        CRect rect(m_drawData->begin, m_drawData->end);
        switch (m_drawData->type)
        {
        case 0:
            pDC->MoveTo(m_drawData->begin);
            pDC->LineTo(m_drawData->end);
            break;
        case 1:
            pDC->Ellipse(rect);
            break;
        case 2:
            pDC->Rectangle(rect);
            break;
        }
    }
}


// wxMdiView2 诊断

#ifdef _DEBUG
void wxMdiView2::AssertValid() const
{
	CEditView::AssertValid();
}

#ifndef _WIN32_WCE
void wxMdiView2::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}
#endif
#endif //_DEBUG

// wxMdiView2 消息处理程序
//计算正圆
CRect completeRect(CPoint o, CPoint e)
{
    double dx = o.x - e.x;
    double dy = o.y - e.y;
    double r = pow(pow(dx, 2) + pow(dy, 2), 0.5);
    CRect rect(o.x - r, o.y - r, o.x + r, o.y + r);
    return rect;
}

//计算三角形外接圆
CRect outsideRect(CPoint o, CPoint e, CPoint e1)
{
    double  x1 = o.x, x2= e.x, x3= e1.x, 
            y1= o.y, y2= e.y, y3= e1.y;
    double  x = 0;
    double  y = 0;
    x = ((y2 - y1) * (y3 * y3 - y1 * y1 + x3 * x3 - x1 * x1) - (y3 - y1) * (y2 * y2 - y1 * y1 + x2 * x2 - x1 * x1)) / 
        (2 * (x3 - x1) * (y2 - y1) - 2 * ((x2 - x1) * (y3 - y1)));
    y = ((x2 - x1) * (x3 * x3 - x1 * x1 + y3 * y3 - y1 * y1) - (x3 - x1) * (x2 * x2 - x1 * x1 + y2 * y2 - y1 * y1)) / 
        (2 * (y3 - y1) * (x2 - x1) - 2 * ((y2 - y1) * (x3 - x1)));
    double r = pow(pow(o.x - x, 2) + pow(o.y - y, 2), 0.5);
    CRect rect(x - r, y - r, x + r, y + r);
    return rect;
}

void wxMdiView2::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CEditView::OnMouseMove(nFlags, point);

    if (Lbrndown&& !TrackStop)
    {
        CClientDC dc(this);
        int oldmode = dc.SetROP2(R2_NOTXORPEN);//获得未设置时的画笔颜色即屏幕当前显示的颜色
        CPen pen(PS_SOLID, lineWidth, m_color), * oldpen;
        oldpen = dc.SelectObject(&pen);
        CRect rect(m_ptOrigin, m_ptEnd);
        CRect rect1(m_ptOrigin, point);
        switch (drawtype)
        {
        case 0:
            dc.MoveTo(m_ptOrigin);
            dc.LineTo(m_ptEnd);
            
            m_ptEnd = point;
            dc.MoveTo(m_ptOrigin);
            dc.LineTo(m_ptEnd);
            break;
        case 1:
            dc.Ellipse(rect);
            dc.Ellipse(rect1);
            m_ptEnd = point;
            break;
        case 2:
            dc.Rectangle(rect);
            dc.Rectangle(rect1);
            m_ptEnd = point;
            break;
        case 3:
            //if (arctag)
            {
                dc.MoveTo(m_ptOrigin);
                dc.LineTo(m_ptEnd);
                m_ptEnd = point;
                dc.MoveTo(m_ptOrigin);
                dc.LineTo(m_ptEnd);
            }
            //else
            {
                //dc.MoveTo(m_ptOrigin);
                //dc.LineTo(m_ptEnd);
                //m_ptEnd = point;
            }
            break;
        }
        dc.SelectObject(oldpen);
        dc.SetROP2(oldmode);
        ReleaseDC(&dc);

    }
}


void wxMdiView2::OnLButtonDown(UINT nFlags, CPoint point)
{
    // TODO: 在此添加消息处理程序代码和/或调用默认值
    CEditView::OnLButtonDown(nFlags, point);
    CWnd* pWnd = this;
    CDC* pDC = pWnd->GetDC();
    if (Lbrndown && !TrackStop)
    {
        wxMdiDoc2* pDoc = (wxMdiDoc2*)GetDocument();
        m_drawData->end = point;
        m_drawData->type = drawtype;
        m_drawData->color = m_color;
        m_drawData->width = lineWidth;
        CClientDC dc(this);
        CPen pen(PS_SOLID, lineWidth, m_color);
        dc.SelectObject(pen);
        pDC->SelectObject(&pen);
        CRect rect(m_drawData->begin, m_drawData->end);
        switch (drawtype)
        {
        case 0:
            dc.MoveTo(m_drawData->begin);
            dc.LineTo(m_drawData->end);
            break;
        case 1:
            dc.Ellipse(rect);
            break;
        case 2:
            dc.Rectangle(rect);
            break;
        case 3:
            //dc.MoveTo(m_drawData->begin);
            //dc.LineTo(m_drawData->end);
            if (arctag)
            {
                m_drawData->End = point;
                dc.MoveTo(m_drawData->End);
                dc.LineTo(m_drawData->Start);
                arctag = !arctag;
            }
            else {
                dc.MoveTo(m_drawData->End);
                dc.LineTo(m_drawData->Start);
                dc.MoveTo(m_drawData->Start);
                dc.LineTo(point);
                m_drawData->End1 = point;
                rect = outsideRect(m_drawData->Start, m_drawData->End, m_drawData->End1);
                dc.Arc(&rect, m_drawData->End, m_drawData->End1);
                arctag = !arctag;
                TrackStop = !TrackStop;
            }
            break;
        }
        
        pDoc->m_data.Add(m_drawData);
        if (drawtype != 3|| arctag) {
            m_drawData = new drawData;
            m_drawData->begin = m_ptOrigin = m_ptEnd = point; }
        else
        {
            m_ptEnd = point;
        }
    }
}


void wxMdiView2::OnLButtonDblClk(UINT nFlags, CPoint point)
{
    // TODO: 在此添加消息处理程序代码和/或调用默认值

    CEditView::OnLButtonDblClk(nFlags, point);
    
    Lbrndown = true;//开始绘图
    TrackStop = !TrackStop;
    if (!TrackStop)
    {
        m_drawData = new drawData;
        m_drawData->Start = m_drawData->begin = point;
    }
    m_ptOrigin = m_ptEnd = point;
}


void wxMdiView2::OnLButtonUp(UINT nFlags, CPoint point)
{
    // TODO: 在此添加消息处理程序代码和/或调用默认值

    CEditView::OnLButtonUp(nFlags, point);
}


void wxMdiView2::OnLine()
{
    // TODO: 在此添加命令处理程序代码
    drawtype = 0;
}


void wxMdiView2::OnCircle()
{
    // TODO: 在此添加命令处理程序代码
    drawtype = 1;
}


void wxMdiView2::OnSector()
{
    // TODO: 在此添加命令处理程序代码
    drawtype = 3;
}


void wxMdiView2::OnRectangular()
{
    // TODO: 在此添加命令处理程序代码
    drawtype = 2;
}


void wxMdiView2::Oncolor()
{
    // TODO: 在此添加命令处理程序代码
    CColorDialog colorDialog;
    if (colorDialog.DoModal() == IDOK)
    {
        m_color = colorDialog.GetColor();
    }
}


void wxMdiView2::Onwidthset1()
{
    // TODO: 在此添加命令处理程序代码
    dlgInput dlgin;
    if (dlgin.DoModal() == IDOK)
    {
        lineWidth = _wtof(dlgin.widthStr.GetBuffer());
    }
}


void wxMdiView2::OnPaint()
{
    CPaintDC dc(this); // device context for painting
                       // TODO: 在此处添加消息处理程序代码
                       // 不为绘图消息调用 CEditView::OnPaint()
    wxMdiDoc2* pDoc = (wxMdiDoc2*)GetDocument();
    for (int i = 0; i < pDoc->m_data.GetCount(); i++)
    {
        m_drawData = (drawData*)(pDoc->m_data.GetAt(i));
        CPen pen(PS_SOLID, m_drawData->width, m_drawData->color);
        dc.SelectObject(pen);
        CRect rect(m_drawData->begin, m_drawData->end);
        switch (m_drawData->type)
        {
        case 0:
            dc.MoveTo(m_drawData->begin);
            dc.LineTo(m_drawData->end);
            break;
        case 1:
            dc.Ellipse(rect);
            break;
        case 2:
            dc.Rectangle(rect);
            break;
        case 3:
                dc.MoveTo(m_drawData->End);
                dc.LineTo(m_drawData->Start);
                dc.LineTo(m_drawData->End1);
                rect = outsideRect(m_drawData->Start, m_drawData->End, m_drawData->End1);
                dc.Arc(&rect, m_drawData->End, m_drawData->End1);
            break;
        }
    }
}
