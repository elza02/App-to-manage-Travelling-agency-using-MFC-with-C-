#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// Pays dialog

class Pays : public CDialogEx
{
	DECLARE_DYNAMIC(Pays)

public:
	Pays(CWnd* pParent = NULL);   // standard constructor
	virtual ~Pays();

// Dialog Data
	enum { IDD = IDD_PAYS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	BOOL Pays::OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_list_pays;

	void MAJList(CString sequel);
	CString FetchData(CString sequel, CString champs);
	afx_msg void OnLvnItemchangedList3(NMHDR *pNMHDR, LRESULT *pResult);
	CStatic InfoText;
	CEdit CEdit_Pays;
	CButton btn_Ajouter;
	CButton btnSupprimer;
	CEdit CEdit_SuppPays;
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton5();
	void deleteVillageANDLang(CString& vl);
	CString returnCodePays(CString& p);
	CString returnCodeContinent(CString& c);
	void fillComboContinents();
	CComboBox comboCo;
};
