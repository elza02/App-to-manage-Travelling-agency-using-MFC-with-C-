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
}


BEGIN_MESSAGE_MAP(Continent, CDialogEx)
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