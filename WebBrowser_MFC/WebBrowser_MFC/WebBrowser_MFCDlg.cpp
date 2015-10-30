
// WebBrowser_MFCDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "WebBrowser_MFC.h"
#include "WebBrowser_MFCDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CWebBrowser_MFCDlg �Ի���




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


// CWebBrowser_MFCDlg ��Ϣ�������

BOOL CWebBrowser_MFCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CWebBrowser_MFCDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CWebBrowser_MFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}




void CWebBrowser_MFCDlg::OnBnClickedButton1()
{
	UpdateData(TRUE);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_url != "")
		m_webbrowser.Navigate(m_url, NULL, NULL, NULL, NULL);

	UpdateData(FALSE);
}


void CWebBrowser_MFCDlg::OnBnClickedButton5()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	GUID uid;
	CoCreateGuid(&uid);
	m_webbrowser.Navigate("www.baidu.com", NULL, NULL, NULL, NULL);
}


void CWebBrowser_MFCDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_webbrowser.GoForward();
}


void CWebBrowser_MFCDlg::OnBnClickedButton4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_webbrowser.GoBack();
}


void CWebBrowser_MFCDlg::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	/*Refresh2��һ����������ʾˢ�¼���
	REFRESH_NORMAL ��ͨˢ�£����Ҳ�����HTTP pragma:nocache ��������
	REFRESH_IFEXPIRED ������ҳ��ʧЧʱ�ŷ���ˢ������
	REFRESH_CONTINUE �ڲ�ʹ�ã���Ҫ�ڱ��ʱʹ��
	REFRESH_COMPLETELY ����HTTP pragma:nocache header ��������
	*/
	m_webbrowser.Refresh();
}
BEGIN_EVENTSINK_MAP(CWebBrowser_MFCDlg, CDialogEx)
	ON_EVENT(CWebBrowser_MFCDlg, IDC_EXPLORER1, 273, CWebBrowser_MFCDlg::NewWindow3Explorer1, VTS_PDISPATCH VTS_PBOOL VTS_UI4 VTS_BSTR VTS_BSTR)
END_EVENTSINK_MAP()


void CWebBrowser_MFCDlg::NewWindow3Explorer1(LPDISPATCH* ppDisp, BOOL* Cancel, unsigned long dwFlags, LPCTSTR bstrUrlContext, LPCTSTR bstrUrl)
{
	// TODO: �ڴ˴������Ϣ����������
	*Cancel = TRUE;
	m_webbrowser.Navigate(bstrUrl, &vtMissing, &vtMissing, &vtMissing, &vtMissing);
}
