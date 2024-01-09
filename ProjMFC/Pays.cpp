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
}


BEGIN_MESSAGE_MAP(Pays, CDialogEx)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST3, &Pays::OnLvnItemchangedList3)
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

	CString sequel = L"SELECT Pays.nomPays, count(Activites.NomActivite) as nbrActivite,count(Villages.nomVillage) as nbrVillages FROM Activites, proposer, Villages, Pays, Continents WHERE Activites.idActivite = proposer.idActivite AND proposer.codeVillage = Villages.codeVillage AND Villages.codePays = Pays.codePays AND Pays.codeContinent = Continents.codeContinent group by Pays.nomPays;";
	MAJList(sequel);
	
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

		//recset.GetFieldValue(L"nbrActivite",var);
		//str=(LPCWSTR)var.pbstrVal;
		//m_list_continent.SetItemText(i,1,str);

		//recset.GetFieldValue(L"nbrVillages",var);
		//str=(LPCWSTR)var.pbstrVal;
		//m_list_continent.SetItemText(i,2,str);		

		//recset.GetFieldValue(L"nbrPays",var);
		//str=(LPCWSTR)var.pbstrVal;
		//m_list_continent.SetItemText(i,3,str);

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
	
	int id_item_list = pNMLV->iItem; //id selected item
	//CString id_champ = m_list.GetItemText(p,0); //id⚡⚡⚡💀💀 (use it later)
	//m_nomAct = m_list_activite.GetItemText(id_item_list,1);
	//m_nomVil = m_list_activite.GetItemText(id_item_list,2);
	//GetDlgItemText = m_list.GetItemText(id_item_list,3);

	CString Pays = m_list_pays.GetItemText(id_item_list,0);
	CString codePays = L"select codePays from Pays where nomPays = \""+Pays+"\";";
	codePays = FetchData(codePays,L"codePays");
	//requete pour chercher info :
	CString query1 = L"select count(nomvillage) as nbrVillage FROM Villages where codePays =\""+codePays+"\";";
	CString query2 = L"select count(NomActivite) as nbrActvite FROM Activites, proposer, Villages, Pays WHERE Activites.idActivite = proposer.idActivite AND  proposer.codeVillage = Villages.codeVillage AND Villages.codePays = Pays.codePays AND nomPays=\""+Pays+"\";";
	
	/*codePays = FetchData(codePays,L"codePays");*/
	query1 = FetchData(query1,L"nbrVillage");
	query2 = FetchData(query2,L"nbrActvite");
	
	//now display the info:
	
	CString txt3;
txt3.Format(L"   Dans %s, vous avez %s activité différente dans %s village différent.", 
           Pays, 
           (query1 == "1" ? L"UNE" : CString(query1)), 
           (query2 == "1" ? L"UN" : CString(query2)));

	InfoText.SetWindowTextW(txt3);
}
