#pragma once
#include "afxcmn.h"


// Continent dialog

class Continent : public CDialogEx
{
	DECLARE_DYNAMIC(Continent)

public:
	Continent(CWnd* pParent = NULL);   // standard constructor
	virtual ~Continent();

// Dialog Data
	enum { IDD = IDD_CONTINENT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_list_continent;
	void MAJList(CString sequel);
};
