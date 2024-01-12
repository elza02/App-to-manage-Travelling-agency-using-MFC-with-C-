#pragma once


// CLogin dialog

class CLogin : public CDialogEx
{
	DECLARE_DYNAMIC(CLogin)

public:
	CLogin(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLogin();

// Dialog Data
	enum { IDD = IDD_LOGIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	BOOL OnInitDialog();
	bool Authentifier();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedLogin();
	BOOL PreTranslateMessage(MSG* pMsg);
};
