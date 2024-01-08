#pragma once
#include "afxcmn.h"
#include "afxwin.h"

// Village dialog

class Village : public CDialogEx
{
	DECLARE_DYNAMIC(Village)

public:
	Village(CWnd* pParent = NULL);   // standard constructor
	virtual ~Village();

// Dialog Data
	enum { IDD = IDD_VILLAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_list_village;
	CComboBox combo1;
	CComboBox combo2;
	CString m_nomVillage;
	CString m_nomPays;
	CString m_nomContinent;

	void MAJList(CString sequel);
	afx_msg void ComboClicked();

	afx_msg void OnBnClickedActivActualiser();
	afx_msg void OnLvnItemchangedList3(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedAjoute();
	afx_msg void OnBnClickedButton5();
	void fillLangCombo(CString& village);
	CButton buttonAjouter;
	CEdit CEDIT_Village;
	CComboBox comboPays;
	CComboBox comboContinent;
	CEdit CEdit_Pays;
	CEdit CEdit_Cntinent;
	afx_msg void OnCbnSelchangeComboPays();
	void removeDuplicates(CComboBox& comboBox);
	CListCtrl m_list_lang;
	CComboBox comboLang;
	CString returnCodeVBaseOnName(CString& vl);
	int villageExistInVillages(CString& vl);
	int langAssociateWVillage(CString& vl, CString& lang);

};
