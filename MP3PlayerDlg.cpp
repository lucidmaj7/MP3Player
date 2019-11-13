
// MP3PlayerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MP3Player.h"
#include "MP3PlayerDlg.h"
#include "afxdialogex.h"

#include "uuids.h"
//#pragma comment (lib ,"Vfw32.lib")

#pragma comment(lib, "winmm")
#include <mmsystem.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMP3PlayerDlg dialog



CMP3PlayerDlg::CMP3PlayerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MP3PLAYER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_hPlayer = NULL;
	m_strFilePath = _T("");

	pigb = NULL;
	pimc = NULL;
	pimex = NULL;
	piba = NULL;
	pims = NULL;
	ready = false;
	duration = 0;
}

void CMP3PlayerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_FILE_PATH, m_CtrlFilePathEdit);
}

BEGIN_MESSAGE_MAP(CMP3PlayerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMP3PlayerDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_PLAY, &CMP3PlayerDlg::OnBnClickedButtonPlay)
	ON_BN_CLICKED(IDC_BUTTON_STOP, &CMP3PlayerDlg::OnBnClickedButtonStop)
	ON_BN_CLICKED(IDC_BUTTON_PAUSE, &CMP3PlayerDlg::OnBnClickedButtonPause)
	ON_BN_CLICKED(IDC_BUTTON_LOAD, &CMP3PlayerDlg::OnBnClickedButtonLoad)
END_MESSAGE_MAP()


// CMP3PlayerDlg message handlers

BOOL CMP3PlayerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMP3PlayerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMP3PlayerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMP3PlayerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMP3PlayerDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnOK();
}

//===================================================
//      Play Button 
//===================================================
void CMP3PlayerDlg::OnBnClickedButtonPlay()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	

	if (pimc)
	{
		HRESULT hr = pimc->Run();
	
	}
	else
		AfxMessageBox(_T("File is not loaded"));


}


void CMP3PlayerDlg::OnBnClickedButtonStop()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	HRESULT hr = pimc->Stop();

	
}


void CMP3PlayerDlg::OnBnClickedButtonPause()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	if (pimc)
	{
		HRESULT hr = pimc->Pause();
		
	}

}


void CMP3PlayerDlg::OnBnClickedButtonLoad()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_CtrlFilePathEdit.GetWindowText(m_strFilePath);
	if (m_strFilePath.GetLength() == 0)
	{
		AfxMessageBox(_T("FilePath len 0"));
		return;
	}
	if (SUCCEEDED(CoCreateInstance(CLSID_FilterGraph,
		NULL,
		CLSCTX_INPROC_SERVER,
		IID_IGraphBuilder,
		(void **)&this->pigb)))
	{
		pigb->QueryInterface(IID_IMediaControl, (void **)&pimc);
		pigb->QueryInterface(IID_IMediaEventEx, (void **)&pimex);
		pigb->QueryInterface(IID_IBasicAudio, (void**)&piba);
		pigb->QueryInterface(IID_IMediaSeeking, (void**)&pims);

		HRESULT hr = pigb->RenderFile(m_strFilePath, NULL);
		if (SUCCEEDED(hr))
		{
			ready = true;
			if (pims)
			{
				pims->SetTimeFormat(&TIME_FORMAT_MEDIA_TIME);
				pims->GetDuration(&duration); // returns 10,000,000 for a second.
				duration = duration;
			}
		}
	}
}
