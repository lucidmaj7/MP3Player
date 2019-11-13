
// MP3PlayerDlg.h : header file
//

#pragma once

#include "mmsystem.h"
#include "strmif.h"
#include "control.h"
#include "afxwin.h"

#pragma comment(lib, "strmiids.lib")
// CMP3PlayerDlg dialog
class CMP3PlayerDlg : public CDialogEx
{
// Construction
public:
	CMP3PlayerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MP3PLAYER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();

private:
	HWND m_hPlayer;
public:
	CString m_strFilePath;
	afx_msg void OnBnClickedButtonPlay();
	afx_msg void OnBnClickedButtonStop();

private:
	IGraphBuilder *  pigb;
	IMediaControl *  pimc;
	IMediaEventEx *  pimex;
	IBasicAudio * piba;
	IMediaSeeking * pims;
	bool    ready;
	// Duration of the MP3.
	__int64 duration;
public:
	afx_msg void OnBnClickedButtonPause();
	afx_msg void OnBnClickedButtonLoad();
	CEdit m_CtrlFilePathEdit;
};
