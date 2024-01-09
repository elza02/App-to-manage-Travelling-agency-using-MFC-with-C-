#pragma once
#include "afxcmn.h"
#include "afxwin.h"


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
	afx_msg void OnLvnItemchangedList3(NMHDR *pNMHDR, LRESULT *pResult);
	CString FetchData(CString sequel, CString champs);
	CStatic InfoText;
};
