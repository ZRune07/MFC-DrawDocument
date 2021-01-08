#pragma once


// dlgInput 对话框

class dlgInput : public CDialogEx
{
	DECLARE_DYNAMIC(dlgInput)

public:
	dlgInput(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~dlgInput();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString widthStr;
};
