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
}


BEGIN_MESSAGE_MAP(Pays, CDialogEx)
END_MESSAGE_MAP()


// Pays message handlers
BOOL Pays::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CRect rc;
	m_list_pays.GetClientRect(rc);
	m_list_pays.InsertColumn(0,L"Pays",0,rc.Width());
	/*m_list_continent.InsertColumn(0,L"nbrActivite",0,0);
	m_list_continent.InsertColumn(0,L"nbrVillages",0,0);
	m_list_continent.InsertColumn(0,L"nbrPays",0,0);*/
	////🔥🔥🔥The 3 line code below is for selecting entire row instead of selecting only the ID(one colonne) :
	m_list_pays.SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_list_pays.SetItemState(0, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
	m_list_pays.SetFocus();

	CString sequel = L"SELECT Pays.nomPays,count(Activites.NomActivite) as nbrActivite,count(Villages.nomVillage) as nbrVillages,count(Continents.nomContinent)as nbrContinents FROM Activites, proposer, Villages, Pays, Continents WHERE Activites.idActivite = proposer.idActivite AND proposer.codeVillage = Villages.codeVillage AND Villages.codePays = Pays.codePays AND Pays.codeContinent = Continents.codeContinent group by Pays.nomPays;";
	MAJList(sequel);
	
	return TRUE;
}

void Pays::MAJList(CString sequel){ 
	CDaoDatabase db; //déclaration de variable base de donnée db : represents a connection to a database.
	CDaoRecordset recset(&db); //the varaible "recset" used to represent a 'set of records' from a database table.

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