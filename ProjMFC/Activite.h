#pragma once

#include "afxcmn.h"
#include "afxwin.h"


// Activite dialog

class Activite : public CDialogEx
{
	DECLARE_DYNAMIC(Activite)

public:
	Activite(CWnd* pParent = NULL);   // standard constructor
	virtual ~Activite();

// Dialog Data
	enum { IDD = IDD_ACTIVITE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CString tri_sequel;
	CListCtrl m_list_activite;
	CString getIdVBaseOnName(CString village);
	void actualiserComboFields();
	void editCEDIT();
	void activeInfoCombo();
	void desactiveInfoCombo();
	void MAJList(CString sequel);
	void ComboClicked();
	CComboBox combo1;
	CComboBox combo2;
	CComboBox combo3;
	CComboBox combo4;
	CComboBox combo5;
	
	afx_msg void OnCbnSelchangeACombo();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedActivActualiser();
	afx_msg void SelectItemOnList(NMHDR *pNMHDR, LRESULT *pResult);
	CString m_nomAct;
	CString m_nomVil;
	CString m_nomPay;
	CString m_nomCon;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	CButton buttonAjouter;
	CEdit CEDIT_nomActivite;
	CEdit CEDIT_village;
	CEdit CEDIT_pays;
	CEdit CEDIT_continent;
	CComboBox combo8;
	afx_msg void OnCbnSelchangeCombo5();
	CComboBox comboGratuit;
	afx_msg void OnBnClickedButton5();
};
