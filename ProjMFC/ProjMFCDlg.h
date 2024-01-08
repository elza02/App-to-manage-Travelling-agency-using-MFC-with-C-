
// ProjMFCDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "Activite.h"
#include "Village.h"
#include "Continent.h"
#include "Pays.h"

// CProjMFCDlg dialog
class CProjMFCDlg : public CDialogEx
{
// Construction
public:
	CProjMFCDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_PROJMFC_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon,b_exit,b_about,b_home;
	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	Activite * ActiviteDlg;
	Village * VillageDlg;
	Pays* PaysDlg;
	Continent* ContinentDlg;
	CButton m_about;
	CButton m_home;
	CButton m_exit;
	afx_msg void OnBnClickedAbout();
	afx_msg void OnBnClickedExit();
	void ClearLastOpenedDlg();
	CStatic m_image;
	afx_msg void OnBnClickedVillages();
	afx_msg void OnBnClickedActivite();
	afx_msg void OnBnClickedPayss();
	afx_msg void OnBnClickedCont();
};
