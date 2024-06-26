// Pays.cpp : implementation file
//

#include "stdafx.h"
#include "ProjMFC.h"
#include "Pays.h"
#include "afxdialogex.h"
#include <afxdao.h>

// Pays dialog

IMPLEMENT_DYNAMIC(Pays, CDialogEx)

Pays::Pays(CWnd* pParent /*=NULL*/)
	: CDialogEx(Pays::IDD, pParent)
{
	Create(IDD_PAYS, pParent);
}

Pays::~Pays()
{
}

void Pays::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST3, m_list_pays);
	DDX_Control(pDX, IDC_TextInfo, InfoText);
	DDX_Control(pDX, IDC_EDIT1, CEdit_Pays);
	DDX_Control(pDX, IDC_BUTTON3, btn_Ajouter);
	DDX_Control(pDX, IDC_BUTTON5, btnSupprimer);
	DDX_Control(pDX, IDC_EDIT2, CEdit_SuppPays);

	DDX_Control(pDX, IDC_COMBO2, comboCo);
}


BEGIN_MESSAGE_MAP(Pays, CDialogEx)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST3, &Pays::OnLvnItemchangedList3)
	ON_BN_CLICKED(IDC_BUTTON3, &Pays::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON5, &Pays::OnBnClickedButton5)
END_MESSAGE_MAP()


// Pays message handlers
BOOL Pays::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CRect rc;
	m_list_pays.GetClientRect(rc);
	//m_list_pays.InsertColumn(0,L"nbrActivite",0,rc.Width()/3);
	//m_list_pays.InsertColumn(0,L"nbrVillages",0,rc.Width()/3);
	m_list_pays.InsertColumn(0,L"Pays",0,rc.Width()/3);
	////🔥🔥🔥The 3 line code below is for selecting entire row instead of selecting only the ID(one colonne) :
	m_list_pays.SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_list_pays.SetItemState(0, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
	m_list_pays.SetFocus();

	CString sequel = L"SELECT Pays.nomPays FROM Pays ;";
	//CString sequel = L"SELECT Pays.nomPays, count(Activites.NomActivite) as nbrActivite,count(Villages.nomVillage) as nbrVillages FROM Activites, proposer, Villages, Pays, Continents WHERE Activites.idActivite = proposer.idActivite AND proposer.codeVillage = Villages.codeVillage AND Villages.codePays = Pays.codePays AND Pays.codeContinent = Continents.codeContinent group by Pays.nomPays;";
	MAJList(sequel);
	CEdit_SuppPays.SetWindowTextW(L"");
	return TRUE;
}

void Pays::MAJList(CString sequel){ 
	CDaoDatabase db; 
	CDaoRecordset recset(&db); 

	COleVariant var;//start Variables
	var.ChangeType(VT_BSTR,NULL);

	m_list_pays.DeleteAllItems();//♻ clear list
	db.Open(L"GestionActivite.mdb");
	recset.Open(AFX_DAO_USE_DEFAULT_TYPE,sequel,NULL);//to retrieve the records for the recordset

	CString str;
	
	int i=0;

	while(!recset.IsEOF())
	{
		//this part of the code should fill up the list + the 3 combo list !
		recset.GetFieldValue(L"nomPays",var);
		str=(LPCWSTR)var.pbstrVal;
		m_list_pays.InsertItem(i ,str ,0 );
		i=i++;
		recset.MoveNext(); 
	}
	recset.Close();
	db.Close();
}

CString Pays::FetchData(CString sequel, CString champs){
	CDaoDatabase db;
	CDaoRecordset recset(&db);
	COleVariant var;
	var.ChangeType(VT_BSTR,NULL);
	db.Open(L"GestionActivite.mdb");
	recset.Open(AFX_DAO_USE_DEFAULT_TYPE,sequel,NULL);//to retrieve the records for the recordset

	CString str;
	int n; 


	recset.GetFieldValue(champs,var);
	if (var.vt == VT_BSTR) {
		// var is a string
		str=(LPCWSTR)var.pbstrVal;
	}else if (var.vt == VT_I4) {
		// var is a number
		n = var.lVal;
		str.Format(_T("%d"), n);
} 
	return str;
}

void Pays::OnLvnItemchangedList3(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	NMHDR x(*pNMHDR);
	
	// TODO: Add your control notification handler code here
	*pResult = 0;
	
	int id_item_list = pNMLV->iItem;
	CString Pays = m_list_pays.GetItemText(id_item_list,0);
	CString codePays = L"select codePays from Pays where nomPays = \""+Pays+"\";";
	codePays = FetchData(codePays,L"codePays");
	//requete pour chercher info :
	CString query1 = L"select count(nomvillage) as nbrVillage FROM Villages where codePays =\""+codePays+"\";";
	CString query2 = L"select count(NomActivite) as nbrActvite FROM Activites, proposer, Villages, Pays WHERE Activites.idActivite = proposer.idActivite AND  proposer.codeVillage = Villages.codeVillage AND Villages.codePays = Pays.codePays AND nomPays=\""+Pays+"\";";

	query1 = FetchData(query1,L"nbrVillage");
	query2 = FetchData(query2,L"nbrActvite");

	//now display the info:
	CString txt3;
	txt3.Format(L"   Dans %s, vous avez %s activité différente dans %s village différent.", 
           Pays, 
           (query1 == "1" ? L"une" : CString(query1)), 
           (query2 == "1" ? L"un" : CString(query2)));

	InfoText.SetWindowTextW(txt3);
	SetDlgItemText(IDC_EDIT2 ,m_list_pays.GetItemText(id_item_list,0));
}

//btn ajouter
void Pays::OnBnClickedButton3()
{
	CString ajouter = L"Ajouter";
	CString sauvegarder = L"Sauvegarder";
	
	CString str;
	btn_Ajouter.GetWindowText(str);
	if(str.Compare(ajouter) == 0){
		btn_Ajouter.SetWindowText(sauvegarder);
		CEdit_Pays.ShowWindow(SW_SHOW);
		comboCo.ShowWindow(SW_SHOW);
		fillComboContinents();
	}
	else{
		comboCo.ShowWindow(SW_HIDE);

		CString query,strCo,codeP,pays;
		CEdit_Pays.GetWindowText(pays);
		codeP = str.Left(3).MakeUpper();
		int index = comboCo.GetCurSel();
		comboCo.GetLBText(index,strCo);
		query.Format(L"insert into Pays values('%s','%s','%s')",codeP,pays,returnCodeContinent(strCo));
		CDaoDatabase db;
		CDaoRecordset recset(&db);
		COleVariant var;//start Variables
		var.ChangeType(VT_BSTR,NULL);
		db.Open(L"GestionActivite.mdb");
		db.Execute(query);
		AfxMessageBox(L"le pays est ajouté avec succes!", MB_OK | MB_ICONINFORMATION);
		btn_Ajouter.SetWindowText(ajouter);
		CEdit_Pays.ShowWindow(SW_HIDE);
			}
}

//Supprression
void Pays::OnBnClickedButton5()
{
	
	CString str;
	CEdit_SuppPays.GetWindowTextW(str);
	if(str == L""){
		AfxMessageBox(L"Choisit une pays a supprimer!", MB_OK | MB_ICONWARNING);
	}
	else{
		CString querySuppP,queryNameV;
		querySuppP.Format(L"delete from pays where nomPays = '%s'",str);
		queryNameV.Format(L"select nomVillage from villages where codePays = '%s'",returnCodePays(str));
		CDaoDatabase db;
		CDaoRecordset recset(&db);
		COleVariant var;//start Variables
		var.ChangeType(VT_BSTR,NULL);
		db.Open(L"GestionActivite.mdb");
		CString cdeV;
		recset.Open(AFX_DAO_USE_DEFAULT_TYPE,queryNameV,NULL);//to retrieve the records for the recordset
		while(!recset.IsEOF()){
			recset.GetFieldValue(L"nomVillage",var);
			cdeV=(LPCWSTR)var.pbstrVal;
			deleteVillageANDLang(cdeV);
			recset.MoveNext();
		}
		recset.Close();
		db.Close();
		AfxMessageBox(L"le pays est supprimé avec succes!", MB_OK | MB_ICONINFORMATION);
		}
}

void Pays::deleteVillageANDLang(CString& vl)
{

	CDaoDatabase db;
	CDaoRecordset recset(&db);
	CString querySupp,queryCodeV,querySuppFromParler,cdeV;
	querySupp.Format(L"delete from villages where nomVillage = '%s' ",vl);
	queryCodeV.Format(L"select codeVillage from villages where nomVillage = '%s'",vl);
		
	COleVariant var;//start Variables
	var.ChangeType(VT_BSTR,NULL);
	db.Open(L"GestionActivite.mdb");
	recset.Open(AFX_DAO_USE_DEFAULT_TYPE,queryCodeV,NULL);//to retrieve the records for the recordset
	while(!recset.IsEOF()){
		recset.GetFieldValue(L"codeVillage",var);
		cdeV=(LPCWSTR)var.pbstrVal;
		recset.MoveNext();
	}
	recset.Close();
	querySuppFromParler.Format(L"delete from parler where codeVillages = '%s'",cdeV);
	db.Execute(querySupp);
	db.Execute(querySuppFromParler);
	db.Close();
}
CString Pays::returnCodePays(CString& p){
	CDaoDatabase db;
	CDaoRecordset recset(&db);
	COleVariant var;//start Variables
	var.ChangeType(VT_BSTR,NULL);
	db.Open(L"GestionActivite.mdb");
	CString query,cdeP;
	query.Format(L"select codePays from pays where nomPays = '%s'",p);
	recset.Open(AFX_DAO_USE_DEFAULT_TYPE,query,NULL);//to retrieve the records for the recordset
	while(!recset.IsEOF()){
		recset.GetFieldValue(L"codePays",var);
		cdeP=(LPCWSTR)var.pbstrVal;
		recset.MoveNext();
	}
	recset.Close();
	db.Close();
	return cdeP;
}
CString Pays::returnCodeContinent(CString& c){
	CDaoDatabase db;
	CDaoRecordset recset(&db);
	COleVariant var;//start Variables
	var.ChangeType(VT_BSTR,NULL);
	db.Open(L"GestionActivite.mdb");
	CString query,cdeP;
	query.Format(L"select codeContinent from continents where nomContinent = '%s'",c);
	recset.Open(AFX_DAO_USE_DEFAULT_TYPE,query,NULL);//to retrieve the records for the recordset
	while(!recset.IsEOF()){
		recset.GetFieldValue(L"codeContinent",var);
		cdeP=(LPCWSTR)var.pbstrVal;
		recset.MoveNext();
	}
	recset.Close();
	db.Close();
	return cdeP;
}
void Pays::fillComboContinents(){
		CDaoDatabase db;
		CDaoRecordset recset(&db);
		COleVariant var;//start Variables
		var.ChangeType(VT_BSTR,NULL);
		db.Open(L"GestionActivite.mdb");
		
		CString query = L"select nomContinent from continents;",Pays;
		recset.Open(AFX_DAO_USE_DEFAULT_TYPE,query,NULL);//to retrieve the records for the recordset
		while(!recset.IsEOF()){
			recset.GetFieldValue(L"nomContinent",var);
			Pays=(LPCWSTR)var.pbstrVal;
			if(comboCo.FindStringExact(0,Pays)==CB_ERR){ //🚩 pour n'avoir pas 2 fois meme chaine dans la combo.
				comboCo.AddString(Pays);
				}
			recset.MoveNext();
		}
		recset.Close();
		db.Close();
}