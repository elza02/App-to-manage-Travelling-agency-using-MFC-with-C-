
// ProjMFCDlg.cpp : implementation file
//
#pragma warning(disable : 4995)

#include "stdafx.h"
#include "ProjMFC.h"
#include "ProjMFCDlg.h"
#include "afxdialogex.h"
#include <afxdao.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CProjMFCDlg dialog




CProjMFCDlg::CProjMFCDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CProjMFCDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON11);
	b_exit = AfxGetApp()->LoadIcon(IDI_ICON21);
	b_about = AfxGetApp()->LoadIcon(IDI_ICON10);
	b_home = AfxGetApp()->LoadIcon(IDI_ICON22);
	ActiviteDlg = NULL;
	VillageDlg = NULL;
	PaysDlg = NULL;
	ContinentDlg = NULL;
	
	}

void CProjMFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_About, m_about);
	DDX_Control(pDX, IDC_Home, m_home);
	DDX_Control(pDX, IDC_Exit, m_exit);
	DDX_Control(pDX, IDC_POPO, m_image);
}

BEGIN_MESSAGE_MAP(CProjMFCDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_About, &CProjMFCDlg::OnBnClickedAbout)
	ON_BN_CLICKED(IDC_Exit, &CProjMFCDlg::OnBnClickedExit)
	ON_BN_CLICKED(IDC_ACTIV, &CProjMFCDlg::OnBnClickedActivite)
	ON_BN_CLICKED(IDC_Villages, &CProjMFCDlg::OnBnClickedVillages)
	ON_BN_CLICKED(IDC_Activite, &CProjMFCDlg::OnBnClickedActivite)
	ON_BN_CLICKED(IDC_PAAYS, &CProjMFCDlg::OnBnClickedPayss)
	ON_BN_CLICKED(IDC_Cont, &CProjMFCDlg::OnBnClickedCont)
	ON_BN_CLICKED(IDC_BD2, &CProjMFCDlg::OnBnClickedBd2)
	ON_BN_CLICKED(IDC_Home, &CProjMFCDlg::OnBnClickedHome)
END_MESSAGE_MAP()


// CProjMFCDlg message handlers

BOOL CProjMFCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.
	m_exit.SetIcon(b_exit);
	m_home.SetIcon(b_home);
	m_about.SetIcon(b_about);
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

	//🚩Creation de Base de donnée s'il n'existe pas :
	CFileFind finder; //pour chercher si le fichier DB existe .
	CString lpszFile =L"GestionActivite.mdb";

	BOOL bWorking = finder.FindFile(lpszFile);

	if(!bWorking){
		//If the file isn't there, then create one :)
		CDaoDatabase db;
		CDaoRecordset recset;

		//db.Create(lpszFile); //in case doesn't existe
		//CString creation_table_Continent=L"CREATE TABLE CLIENTS(no_Client AUTOINCREMENT PRIMARY KEY, Nom VARCHAR(30), Prenom VARCHAR(30), Localite VARCHAR(30));";
		CString creation_table_admin = L"CREATE TABLE ADMIN(no_Admin AUTOINCREMENT PRIMARY KEY,NonDuCompte VARCHAR(30),MotDePasse VARCHAR(30));";
		db.Open(lpszFile);
		db.Execute(creation_table_admin);
		db.Close();  //and close the database!
	}else{

	}

	//login page:
	LoginDlg = new CLogin(this);
	
	CRect rc;
	GetDlgItem(IDC_FRAME)->GetWindowRect(rc);
	ScreenToClient(&rc);
	LoginDlg->MoveWindow(rc);

	GetDlgItem(IDC_ACTIV)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_Villages)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_PAAYS)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_Cont)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BD2)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_Home)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_About)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_Exit)->ShowWindow(SW_HIDE);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CProjMFCDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CProjMFCDlg::OnPaint()
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
HCURSOR CProjMFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CProjMFCDlg::OnBnClickedAbout()
{
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();
	// TODO: Add your control notification handler code here
}


void CProjMFCDlg::OnBnClickedExit()
{ 
	OnOK();
	// TODO: Add your control notification handler code here
}

void CProjMFCDlg::ClearLastOpenedDlg(){
	if(VillageDlg != NULL) {
		delete(VillageDlg);
		VillageDlg = NULL;
	}else if(ActiviteDlg != NULL){
		delete(ActiviteDlg);
		ActiviteDlg = NULL;
	}else if(PaysDlg != NULL){
		delete(PaysDlg);
		PaysDlg = NULL;
	}else if(ContinentDlg != NULL){
		delete(ContinentDlg);
		ContinentDlg = NULL;
	}
}
void CProjMFCDlg::OnBnClickedActivite()
{
	// TODO: Add your control notification handler code here
	ClearLastOpenedDlg();
	ActiviteDlg = new Activite(this);
	CRect rc;
	GetDlgItem(IDC_FRAME)->GetWindowRect(rc);
	ScreenToClient(&rc);
	ActiviteDlg->MoveWindow(rc);

}

void CProjMFCDlg::OnBnClickedVillages()
{
	ClearLastOpenedDlg();
	VillageDlg = new Village(this);
	CRect rc;
	GetDlgItem(IDC_FRAME)->GetWindowRect(rc);
	ScreenToClient(&rc);
	VillageDlg->MoveWindow(rc);
}

void CProjMFCDlg::OnBnClickedPayss()
{
	// TODO: Add your control notification handler code here
	ClearLastOpenedDlg();
	PaysDlg = new Pays(this);
	CRect rc;
	GetDlgItem(IDC_FRAME)->GetWindowRect(rc);
	ScreenToClient(&rc);
	PaysDlg->MoveWindow(rc);
}


void CProjMFCDlg::OnBnClickedCont()
{
	// TODO: Add your control notification handler code here
	ClearLastOpenedDlg();
	ContinentDlg = new Continent(this);
	CRect rc;
	GetDlgItem(IDC_FRAME)->GetWindowRect(rc);
	ScreenToClient(&rc);
	ContinentDlg->MoveWindow(rc);
}

void CProjMFCDlg::AfterLogin()
{
	GetDlgItem(IDC_ACTIV)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_Villages)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_PAAYS)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_Cont)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BD2)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_Home)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_Exit)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_About)->ShowWindow(SW_SHOW);

	delete(LoginDlg);
	OnBnClickedActivite();
}


void CProjMFCDlg::OnBnClickedBd2()
{
	CString lpszFile =L"GestionActivite.mdb";
	CDaoDatabase db;
	db.Create(lpszFile);
	CString createLangues;

	createLangues.Format(_T("CREATE TABLE Langues(nomLangue VARCHAR(50) PRIMARY KEY);"));


	// CREATE TABLE Continents
	CString createContinents;
	createContinents.Format(_T("CREATE TABLE Continents(codeContinent VARCHAR(5) PRIMARY KEY, nomContinent VARCHAR(50) NOT NULL);"));

	// CREATE TABLE Activites
	CString createActivites;
	createActivites.Format(_T("CREATE TABLE Activites(idActivite INT AUTOINCREMENT PRIMARY KEY, NomActivite VARCHAR(50) NOT NULL UNIQUE);"));

	// CREATE TABLE Pays
	CString createPays;
	createPays.Format(_T("CREATE TABLE Pays(codePays VARCHAR(3) PRIMARY KEY, nomPays VARCHAR(50) NOT NULL UNIQUE, codeContinent VARCHAR(5) NOT NULL, FOREIGN KEY		(codeContinent) REFERENCES Continents(codeContinent));"));

	// CREATE TABLE Villages
	CString createVillages;
	createVillages.Format(_T("CREATE TABLE Villages(codeVillage VARCHAR(5) PRIMARY KEY, nomVillage VARCHAR(50) NOT NULL, codePays VARCHAR(3) NOT NULL, FOREIGN KEY		(codePays) REFERENCES Pays(codePays));"));
    
	// CREATE TABLE parler
	CString createParler;
	createParler.Format(_T("CREATE TABLE parler(nomLangue VARCHAR(50), codeVillage VARCHAR(5), PRIMARY KEY(nomLangue, codeVillage), FOREIGN KEY(nomLangue) 			REFERENCES Langues(nomLangue), FOREIGN KEY(codeVillage) REFERENCES Villages(codeVillage));"));
	// CREATE TABLE proposer
	CString createProposer;
	createProposer.Format(_T("CREATE TABLE proposer(codeVillage VARCHAR(5), idActivite INT, gratuite BYTE NOT NULL, PRIMARY KEY(codeVillage, idActivite), FOREIGN 		KEY(codeVillage) REFERENCES Villages(codeVillage), FOREIGN KEY(idActivite) REFERENCES Activites(idActivite));"));

    // Concaténer toutes les commandes dans un seul CString
    CString createStatements;
    createStatements = createLangues + _T("\n") +
                       createContinents + _T("\n") +
                       createActivites + _T("\n") +
                       createPays + _T("\n") +
                       createVillages + _T("\n") +
                       createParler + _T("\n") +
                       createProposer;

	db.Execute(createStatements);
	AfxMessageBox(L"la base de donné est cree en succes!", MB_OK | MB_ICONINFORMATION);
}


void CProjMFCDlg::OnBnClickedHome()
{
		GetDlgItem(IDC_ACTIV)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_Villages)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_PAAYS)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_Cont)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BD2)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_Home)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_About)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_Exit)->ShowWindow(SW_HIDE);
	ClearLastOpenedDlg();
	LoginDlg = new CLogin(this);
	CRect rc;
	GetDlgItem(IDC_FRAME)->GetWindowRect(rc);
	ScreenToClient(&rc);
	LoginDlg->MoveWindow(rc);

}
