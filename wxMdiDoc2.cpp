// wxMdiDoc2.cpp: 实现文件
//

#include "pch.h"
#include "wxMdi.h"
#include "wxMdiDoc2.h"
#include"drawData.h"

// wxMdiDoc2

IMPLEMENT_DYNCREATE(wxMdiDoc2, CDocument)

wxMdiDoc2::wxMdiDoc2()
{
}

BOOL wxMdiDoc2::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

wxMdiDoc2::~wxMdiDoc2()
{
}


BEGIN_MESSAGE_MAP(wxMdiDoc2, CDocument)
END_MESSAGE_MAP()


// wxMdiDoc2 诊断

#ifdef _DEBUG
void wxMdiDoc2::AssertValid() const
{
	CDocument::AssertValid();
}

#ifndef _WIN32_WCE
void wxMdiDoc2::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif
#endif //_DEBUG

#ifndef _WIN32_WCE
// wxMdiDoc2 序列化

void wxMdiDoc2::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO:  在此添加存储代码
		int size = m_data.GetCount();
		ar << size;
		int i;
		for (i = 0; i < size; i++)
		{
			drawData* data = (drawData*)m_data.GetAt(i);
			ar << data->begin.x;
			ar << data->begin.y;
			ar << data->end.x;
			ar << data->end.y;
			ar << data->type;
			ar << data->color;
			ar << data->width;
		}
	}
	else
	{
		// TODO:  在此添加加载代码
		int size;
		ar >> size;
		int i;
		m_data.RemoveAll();
		for (i = 0; i < size; i++)
		{
			drawData* data = new drawData;
			ar >> data->begin.x;
			ar >> data->begin.y;
			ar >> data->end.x;
			ar >> data->end.y;
			ar >> data->type;
			ar >> data->color;
			ar >> data->width;
			m_data.Add(data);
		}
		UpdateAllViews(NULL);
	}
}
#endif


// wxMdiDoc2 命令
