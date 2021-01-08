
// wxMdiView.cpp: CwxMdiView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "wxMdi.h"
#endif

#include "wxMdiDoc.h"
#include "wxMdiView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CwxMdiView

IMPLEMENT_DYNCREATE(CwxMdiView, CEditView)

BEGIN_MESSAGE_MAP(CwxMdiView, CEditView)
END_MESSAGE_MAP()

// CwxMdiView 构造/析构

CwxMdiView::CwxMdiView() noexcept
{
	// TODO: 在此处添加构造代码

}

CwxMdiView::~CwxMdiView()
{
}

BOOL CwxMdiView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	BOOL bPreCreated = CEditView::PreCreateWindow(cs);
	cs.style &= ~(ES_AUTOHSCROLL|WS_HSCROLL);	// 启用换行

	return bPreCreated;
}


// CwxMdiView 诊断

#ifdef _DEBUG
void CwxMdiView::AssertValid() const
{
	CEditView::AssertValid();
}

void CwxMdiView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}

CwxMdiDoc* CwxMdiView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CwxMdiDoc)));
	return (CwxMdiDoc*)m_pDocument;
}
#endif //_DEBUG


// CwxMdiView 消息处理程序
