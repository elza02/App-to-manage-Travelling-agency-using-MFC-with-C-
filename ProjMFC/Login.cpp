// Login.cpp : implementation file
//

#include "stdafx.h"
#include "ProjMFC.h"
#include "Login.h"
#include "afxdialogex.h"
#include "ProjMFCDlg.h"
#include <afxdao.h>

// CLogin dialog

IMPLEMENT_DYNAMIC(CLogin, CDialogEx)

CLogin::CLogin(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLogin::IDD, pParent)
{
	Create(IDD_LOGIN, pParent);
}

CLogin::~CLogin()
{
}

void CLogin::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CLogin, CDialogEx)
	ON_BN_CLICKED(IDC_LOGIN, &CLogin::OnBnClickedLogin)
END_MESSAGE_MAP()


// CLogin message handlers
BOOL CLogin::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	return TRUE;
}

bool CLogin::Authentifier(){
	CString ndc,mdp;
	GetDlgItem(IDC_NDC)->GetWindowText(ndc);
	GetDlgItem(IDC_MDP)->GetWindowText(mdp);

	CString lpszFile =L"GestionActivite.mdb";

	//If the file isn't there, then create one :)
	CDaoDatabase db;
	CDaoRecordset recset(&db);
	db.Open(lpszFile);
	//db.Create(lpszFile); //in case doesn't existe
	//CString creation_table_Continent=L"CREATE TABLE CLIENTS(no_Client AUTOINCREMENT PRIMARY KEY, Nom VARCHAR(30), Prenom VARCHAR(30), Localite VARCHAR(30));";
	CString sequel = L"Select * from ADMIN where NonDuCompte=\""+ndc+"\" AND MotDePasse=\""+mdp+"\" ;";
	recset.Open(AFX_DAO_USE_DEFAULT_TYPE,sequel,NULL);
	if (!recset.IsEOF())
	{
		//user exist in DB:
		//AfxMessageBox(L"Vous etes connecté, bienvenue !");
		//get fenetre
		HWND hWnd = ::FindWindow(NULL, _T("ProjMFC"));
		CProjMFCDlg* mainDlg = (CProjMFCDlg*)CWnd::FromHandle(hWnd);
		mainDlg->AfterLogin();
		//CProjMFCApp* app = (CProjMFCApp*)AfxGetApp();
		//CProjMFCDlg* pDlg = app->getL
		
	}else{
		//user isn't existing:
		AfxMessageBox(L"Les infos que vous avez saisi sont fausses.");
	}
	db.Close();  //and close the database!

	return FALSE;
}

void CLogin::OnBnClickedLogin()
{
	// TODO: Add your control notification handler code here
	Authentifier();
}
BOOL CLogin::PreTranslateMessage(MSG* pMsg)
{
    if (pMsg->message == WM_KEYDOWN)
    {
        if (pMsg->wParam == VK_RETURN)
        {
            // Simulate a button click
            OnBnClickedLogin();
            return TRUE; // Mark the message as handled
        }
    }

    return CDialog::PreTranslateMessage(pMsg);
}