// Continent.cpp : implementation file
//

#include "stdafx.h"
#include "ProjMFC.h"
#include "Continent.h"
#include "afxdialogex.h"
#include <afxdao.h>

// Continent dialog

IMPLEMENT_DYNAMIC(Continent, CDialogEx)

Continent::Continent(CWnd* pParent /*=NULL*/)
	: CDialogEx(Continent::IDD, pParent)
{
	Create(IDD_CONTINENT, pParent);
}

Continent::~Continent()
{
}

void Continent::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST3, m_list_continent);
	DDX_Control(pDX, IDC_TextInfo2, InfoText);
}


BEGIN_MESSAGE_MAP(Continent, CDialogEx)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST3, &Continent::OnLvnItemchangedList3)
END_MESSAGE_MAP()


// Continent message handlers
BOOL Continent::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CRect rc;
	m_list_continent.GetClientRect(rc);
	m_list_continent.InsertColumn(0,L"Continent",0,rc.Width());
	/*m_list_continent.InsertColumn(0,L"nbrActivite",0,0);
	m_list_continent.InsertColumn(0,L"nbrVillages",0,0);
	m_list_continent.InsertColumn(0,L"nbrPays",0,0);*/
	////🔥🔥🔥The 3 line code below is for selecting entire row instead of selecting only the ID(one colonne) :
	m_list_continent.SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_list_continent.SetItemState(0, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
	m_list_continent.SetFocus();

	CString sequel = L"SELECT Continents.nomContinent,count(Activites.NomActivite) as nbrActivite,count(Villages.nomVillage) as nbrVillages,count(Pays.nomPays ) as nbrPays FROM Activites, proposer, Villages, Pays, Continents WHERE Activites.idActivite = proposer.idActivite AND proposer.codeVillage = Villages.codeVillage AND Villages.codePays = Pays.codePays AND Pays.codeContinent = Continents.codeContinent group by Continents.nomContinent;";
	MAJList(sequel);
	
	return TRUE;
}

void Continent::MAJList(CString sequel){ 
	CDaoDatabase db; //déclaration de variable base de donnée db : represents a connection to a database.
	CDaoRecordset recset(&db); //the varaible "recset" used to represent a 'set of records' from a database table.

	COleVariant var;//start Variables
	var.ChangeType(VT_BSTR,NULL);

	m_list_continent.DeleteAllItems();//♻ clear list
	db.Open(L"GestionActivite.mdb");
	recset.Open(AFX_DAO_USE_DEFAULT_TYPE,sequel,NULL);//to retrieve the records for the recordset

	CString str;
	
	int i=0;

	while(!recset.IsEOF())
	{
		//this part of the code should fill up the list + the 3 combo list !
		recset.GetFieldValue(L"nomContinent",var);
		str=(LPCWSTR)var.pbstrVal;
		m_list_continent.InsertItem(i ,str ,0 );

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


CString Continent::FetchData(CString sequel, CString champs){
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

void Continent::OnLvnItemchangedList3(NMHDR *pNMHDR, LRESULT *pResult)
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

	CString Continent = m_list_continent.GetItemText(id_item_list,0);
	CString codeContinent = L"select codeContinent from Continents where nomContinent = \""+Continent+"\";";
	codeContinent = FetchData(codeContinent,L"codeContinent");
	//requete pour chercher info :
	CString query0 = L"select count(nomPays) as nbrPays FROM Pays where codeContinent =\""+codeContinent+"\";";
	CString query2 = L"select count(NomActivite) as nbrActvite FROM Activites, proposer, Villages, Pays, Continents WHERE Activites.idActivite = proposer.idActivite AND  proposer.codeVillage = Villages.codeVillage AND Villages.codePays = Pays.codePays AND Pays.codeContinent = Continents.codeContinent AND nomContinent=\""+Continent+"\";";
	
	query0 = FetchData(query0,L"nbrPays");
	query2 = FetchData(query2,L"nbrActvite");
	
	//now display the info:
	
	CString txt3;
txt3.Format(L"Dans le continent %s, il y a %s pays avec %s activité différente.", 
           Continent, 
           (query0 == "1" ? L"UNE" : CString(query0)), 
           (query2 == "1" ? L"UN" : CString(query2)));

	InfoText.SetWindowTextW(txt3);
}
