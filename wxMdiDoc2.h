﻿#pragma once

// wxMdiDoc2 文档

class wxMdiDoc2 : public CDocument
{
	DECLARE_DYNCREATE(wxMdiDoc2)

public:
	wxMdiDoc2();
	virtual ~wxMdiDoc2();
#ifndef _WIN32_WCE
	virtual void Serialize(CArchive& ar);   // 为文档 I/O 重写
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual BOOL OnNewDocument();

	DECLARE_MESSAGE_MAP()
public:
	CPtrArray m_data;
};
