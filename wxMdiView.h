
// wxMdiView.h: CwxMdiView 类的接口
//

#pragma once


class CwxMdiView : public CEditView
{
protected: // 仅从序列化创建
	CwxMdiView() noexcept;
	DECLARE_DYNCREATE(CwxMdiView)

// 特性
public:
	CwxMdiDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 实现
public:
	virtual ~CwxMdiView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // wxMdiView.cpp 中的调试版本
inline CwxMdiDoc* CwxMdiView::GetDocument() const
   { return reinterpret_cast<CwxMdiDoc*>(m_pDocument); }
#endif

