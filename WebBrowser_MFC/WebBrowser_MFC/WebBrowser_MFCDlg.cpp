
// WebBrowser_MFCDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "WebBrowser_MFC.h"
#include "WebBrowser_MFCDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CWebBrowser_MFCDlg 对话框




CWebBrowser_MFCDlg::CWebBrowser_MFCDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CWebBrowser_MFCDlg::IDD, pParent)
	, m_url(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWebBrowser_MFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EXPLORER1, m_webbrowser);
	DDX_Text(pDX, IDC_EDIT1, m_url);
}

BEGIN_MESSAGE_MAP(CWebBrowser_MFCDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CWebBrowser_MFCDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON5, &CWebBrowser_MFCDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON2, &CWebBrowser_MFCDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON4, &CWebBrowser_MFCDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON3, &CWebBrowser_MFCDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CWebBrowser_MFCDlg 消息处理程序

BOOL CWebBrowser_MFCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CWebBrowser_MFCDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CWebBrowser_MFCDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CWebBrowser_MFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}




void CWebBrowser_MFCDlg::OnBnClickedButton1()
{
	UpdateData(TRUE);
	// TODO: 在此添加控件通知处理程序代码
	if (m_url != "")
		m_webbrowser.Navigate(m_url, NULL, NULL, NULL, NULL);

	UpdateData(FALSE);
}


void CWebBrowser_MFCDlg::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	GUID uid;
	CoCreateGuid(&uid);
	m_webbrowser.Navigate("www.baidu.com", NULL, NULL, NULL, NULL);
}


void CWebBrowser_MFCDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	m_webbrowser.GoForward();
}


void CWebBrowser_MFCDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	m_webbrowser.GoBack();
}


void CWebBrowser_MFCDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	/*Refresh2带一个参数，表示刷新级别
	REFRESH_NORMAL 普通刷新，并且不发送HTTP pragma:nocache 到服务器
	REFRESH_IFEXPIRED 仅仅当页面失效时才发送刷新请求
	REFRESH_CONTINUE 内部使用，不要在编程时使用
	REFRESH_COMPLETELY 发送HTTP pragma:nocache header 到服务器
	*/
	m_webbrowser.Refresh();
}
BEGIN_EVENTSINK_MAP(CWebBrowser_MFCDlg, CDialogEx)
	ON_EVENT(CWebBrowser_MFCDlg, IDC_EXPLORER1, 273, CWebBrowser_MFCDlg::NewWindow3Explorer1, VTS_PDISPATCH VTS_PBOOL VTS_UI4 VTS_BSTR VTS_BSTR)
END_EVENTSINK_MAP()


void CWebBrowser_MFCDlg::NewWindow3Explorer1(LPDISPATCH* ppDisp, BOOL* Cancel, unsigned long dwFlags, LPCTSTR bstrUrlContext, LPCTSTR bstrUrl)
{
	// TODO: 在此处添加消息处理程序代码
	*Cancel = TRUE;
	m_webbrowser.Navigate(bstrUrl, &vtMissing, &vtMissing, &vtMissing, &vtMissing);
}
