// dlgInput.cpp: 实现文件
//

#include "pch.h"
#include "wxMdi.h"
#include "dlgInput.h"
#include "afxdialogex.h"


// dlgInput 对话框

IMPLEMENT_DYNAMIC(dlgInput, CDialogEx)

dlgInput::dlgInput(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
	, widthStr(_T(""))
{

}

dlgInput::~dlgInput()
{
}

void dlgInput::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, widthStr);
}


BEGIN_MESSAGE_MAP(dlgInput, CDialogEx)
END_MESSAGE_MAP()


// dlgInput 消息处理程序
