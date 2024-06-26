// Village.cpp : implementation file
//

#include "stdafx.h"
#include "ProjMFC.h"
#include "Village.h"
#include "afxdialogex.h"
#include <afxdao.h>


// Village dialog

IMPLEMENT_DYNAMIC(Village, CDialogEx)

Village::Village(CWnd* pParent /*=NULL*/)
	: CDialogEx(Village::IDD, pParent)
	, m_nomVillage(_T(""))
	, m_nomContinent(_T(""))
{
	Create(IDD_VILLAGE,pParent);
}

Village::~Village()
{
}

void Village::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST3, m_list_village);
	DDX_Control(pDX, IDC_COMBO2, combo1);
	DDX_Control(pDX, IDC_COMBO3, combo2);
	DDX_Text(pDX, IDC_EDIT1, m_nomVillage);
	DDX_Text(pDX, IDC_EDIT3, m_nomPays);
	DDX_Text(pDX, IDC_EDIT4, m_nomContinent);
	DDX_Control(pDX, IDC_BUTTON3, buttonAjouter);
	DDX_Control(pDX, IDC_EDIT1, CEDIT_Village);
	DDX_Control(pDX, IDC_COMBO5, comboPays);
	DDX_Control(pDX, IDC_EDIT3, CEdit_Pays);
	DDX_Control(pDX, IDC_EDIT4, CEdit_Cntinent);
	DDX_Control(pDX, IDC_COMBO6, comboLang);
}


BEGIN_MESSAGE_MAP(Village, CDialogEx)

	ON_CBN_SELCHANGE(IDC_COMBO2, &Village::ComboClicked)
	ON_CBN_SELCHANGE(IDC_COMBO3, &Village::ComboClicked)
	ON_BN_CLICKED(IDC_ACTIV_ACTUALISER, &Village::OnBnClickedActivActualiser)
	ON_BN_CLICKED(IDC_BUTTON2, &Village::OnBnClickedActivActualiser)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST3, &Village::OnLvnItemchangedList3)
	ON_BN_CLICKED(IDC_BUTTON3, &Village::OnBnClickedAjoute)
	ON_BN_CLICKED(IDC_BUTTON5, &Village::OnBnClickedButton5)
	ON_CBN_SELCHANGE(IDC_COMBO5, &Village::OnCbnSelchangeComboPays)

END_MESSAGE_MAP()


// Village message handlers

BOOL Village::OnInitDialog()
{

	CDialogEx::OnInitDialog();
	CRect rc;
	m_list_village.GetClientRect(rc);
	m_list_village.InsertColumn(0,L"Continent",0,rc.Width()/3);
	m_list_village.InsertColumn(0,L"Pays",0,rc.Width()/3);
	m_list_village.InsertColumn(0,L"Village",0,rc.Width()/3);
	//The 3 line code below is for selecting entire row instead of selecting only the ID(one colonne) :
	m_list_village.SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_list_village.SetItemState(0, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
	m_list_village.SetFocus();

	CString sequel = L"SELECT DISTINCT Villages.nomVillage,Pays.nomPays,Continents.nomContinent FROM Villages, Pays, Continents WHERE Villages.codePays = Pays.codePays AND Pays.codeContinent = Continents.codeContinent;";
	MAJList(sequel);

	return TRUE;
}

void Village::MAJList(CString sequel){ 
	CDaoDatabase db; //déclaration de variable base de donnée db : represents a connection to a database.
	CDaoRecordset recset(&db); //the varaible "recset" used to represent a 'set of records' from a database table.

	COleVariant var;//start Variables
	var.ChangeType(VT_BSTR,NULL);

	m_list_village.DeleteAllItems();//♻ clear list
	db.Open(L"GestionActivite.mdb");
	recset.Open(AFX_DAO_USE_DEFAULT_TYPE,sequel,NULL);//to retrieve the records for the recordset

	CString nomActivite,nomVillage,Pays,Continent;
	int i=0;

	while(!recset.IsEOF())
	{
		//this part of the code should fill up the list + the 3 combo list !
		recset.GetFieldValue(L"nomVillage",var);
		nomActivite=(LPCWSTR)var.pbstrVal;
		m_list_village.InsertItem(i ,nomActivite ,0 );
		//if(combo1.FindStringExact(0,nomActivite)==CB_ERR){ 
		//	combo1.AddString(nomActivite);
		//}

		recset.GetFieldValue(L"nomPays",var);
		nomVillage=(LPCWSTR)var.pbstrVal;
		m_list_village.SetItemText(i,1,nomVillage);
		if(combo1.FindStringExact(0,nomVillage)==CB_ERR){ 
			combo1.AddString(nomVillage);
		}

		recset.GetFieldValue(L"nomContinent",var);
		Pays=(LPCWSTR)var.pbstrVal;
		m_list_village.SetItemText(i,2,Pays);
		if(combo2.FindStringExact(0,Pays)==CB_ERR){ //🚩 pour n'avoir pas 2 fois meme chaine dans la combo.
			combo2.AddString(Pays);
			//combo6.AddString(Pays);
		}
		

		i=i++;
		recset.MoveNext(); 
	}
	recset.Close();
	db.Close();
}

void Village::ComboClicked(){
	// for all the combo boxes : ses variables vont contenir la "chaine" selectionner pour l'utiliser dans la requet de tri.
	CString selectedTextCombo1 ;
	CString selectedTextCombo2 ;

	int ind1 = combo1.GetCurSel();  //Il retourne le numero de la ligne selectionné (commencant de 0 et non pas 1) , pour recuperer apres la chaine voulu .
	int ind2 = combo2.GetCurSel();

	CString temp; // ou mettre les valeur string selectionner 

	if ( ind1 != CB_ERR ){          //equivalent de dire "if "combo1" selected". By default, CB_ERR is a varaible that equals to -1 , CB_ERR = -1  .
		
		combo1.GetLBText(ind1,temp);  //then take its string.
		selectedTextCombo1 = CString(" AND Pays.nomPays =\"")+temp+CString("\"");
		temp.Empty(); //vider la varaible
	}
	if ( ind2 != CB_ERR ){
		combo2.GetLBText(ind2,temp);
		selectedTextCombo2 = CString(" AND Continents.nomContinent =\"")+temp+CString("\"");
		temp.Empty();
	}
	
	//now the request : 
	CString sequel = L"SELECT Villages.nomVillage,Pays.nomPays,Continents.nomContinent" 
		+ CString(L" FROM Villages, Pays, Continents")
		+ CString(L" WHERE Villages.codePays = Pays.codePays AND Pays.nomPays")+selectedTextCombo1
		+ CString(L" AND ")
		+ CString(L" Pays.codeContinent = Continents.codeContinent AND Continents.nomContinent ")+selectedTextCombo2;
	MAJList(sequel);

}

void Village::OnBnClickedActivActualiser()
{
	// TODO: Add your control notification handler code here
	/*SetDlgItemText(IDC_nomPayEdit ,L" ");
	SetDlgItemText(IDC_nomConEdit ,L" ");
	SetDlgItemText(IDC_nomActEdit ,L" ");
	SetDlgItemText(IDC_nomVilEdit ,L" ");*/

	combo1.ResetContent();
	combo2.ResetContent();

	CString sequel = L"SELECT DISTINCT Villages.nomVillage,Pays.nomPays,Continents.nomContinent FROM Villages, Pays, Continents WHERE Villages.codePays = Pays.codePays AND Pays.codeContinent = Continents.codeContinent;";
	MAJList(sequel);
}

void Village::OnLvnItemchangedList3(NMHDR *pNMHDR, LRESULT *pResult)
{
	//This fonction is a message when you double click on list , it put the selected thing in the dialogues :

	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	NMHDR x(*pNMHDR);
	
	// TODO: Add your control notification handler code here
	*pResult = 0;
	
	int id_item_list = pNMLV->iItem; //id selected item
	//CString id_champ = m_list.GetItemText(p,0); //id⚡⚡⚡💀💀 (use it later)
	//m_nomAct = m_list_activite.GetItemText(id_item_list,1);
	//m_nomVil = m_list_activite.GetItemText(id_item_list,2);
	//GetDlgItemText = m_list.GetItemText(id_item_list,3);
	SetDlgItemText(IDC_EDIT1 ,m_list_village.GetItemText(id_item_list,0));
	SetDlgItemText(IDC_EDIT3 ,m_list_village.GetItemText(id_item_list,1));
	SetDlgItemText(IDC_EDIT4 ,m_list_village.GetItemText(id_item_list,2));
	CString village;
	CEDIT_Village.GetWindowTextW(village);
	fillLangCombo(village);
	
}

void Village::fillLangCombo(CString& village) {
    CDaoDatabase db;
    CDaoRecordset recset(&db);
	comboLang.ResetContent();
    try {
        db.Open(L"GestionActivite.mdb");

        COleVariant var; // start Variables
        var.ChangeType(VT_BSTR, NULL);

        CString nmla, queryL;

        queryL.Format(L"SELECT langues.nomLangue FROM langues, villages, parler WHERE langues.nomLangue = parler.nomLangue AND villages.codeVillage = parler.codeVillages AND villages.nomVillage ='%s'", village);

        recset.Open(AFX_DAO_USE_DEFAULT_TYPE, queryL, NULL); // to retrieve the records for the recordset

        while (!recset.IsEOF()) {
            recset.GetFieldValue(L"nomLangue", var);
            nmla = (LPCWSTR)var.pbstrVal;
            comboLang.AddString(nmla);
            recset.MoveNext();
        }

        recset.Close();
        db.Close();
    }
    catch (CDaoException* e) {
        // Handle exceptions here
        e->ReportError();
        e->Delete();
    }
}

void Village::OnBnClickedAjoute()//ajouter
{
	
	CString ajouter = L"Ajouter",sauvegarder = L"Sauvegarder",str;
	
	buttonAjouter.GetWindowText(str);
	if(str.Compare(ajouter) == 0){
		buttonAjouter.SetWindowText(sauvegarder);
		CEDIT_Village.EnableWindow(TRUE);
		
		CEdit_Pays.ShowWindow(SW_HIDE);
	
		comboPays.ShowWindow(SW_SHOW);
		CDaoDatabase db;
		CDaoRecordset recset(&db);
		CString query_pays = L"select nomPays from pays";
		COleVariant var;
		var.ChangeType(VT_BSTR,NULL);
		db.Open(L"GestionActivite.mdb");
		recset.Open(AFX_DAO_USE_DEFAULT_TYPE,query_pays,NULL);		
		CString nmpays;
		while(!recset.IsEOF()){
			recset.GetFieldValue(L"nomPays",var);
			nmpays=(LPCWSTR)var.pbstrVal;
			comboPays.AddString(nmpays);
			recset.MoveNext();
		}	
		recset.Close();
		
		CString query_lang = L"select nomLangue from langues";
		recset.Open(AFX_DAO_USE_DEFAULT_TYPE,query_lang,NULL);		
		CString nmlang;

		while(!recset.IsEOF()){
			recset.GetFieldValue(L"nomLangue",var);
			nmlang=(LPCWSTR)var.pbstrVal;
			comboLang.AddString(nmlang);
			recset.MoveNext();
	
		}	
		recset.Close();
		db.Close();
		removeDuplicates(comboLang);

		
	}
	else{
		buttonAjouter.SetWindowText(ajouter);
		CEdit_Pays.ShowWindow(SW_SHOW);
		//CEdit_Cntinent.ShowWindow(SW_SHOW);
		comboPays.ShowWindow(SW_HIDE);			
		CString vl,pa,co,lang,query1,query2,query3,codeP,codeV;
		CEDIT_Village.GetWindowTextW(vl);
		codeV = vl.Left(3).MakeUpper();
		int index1 = comboPays.GetCurSel();
		comboPays.GetLBText(index1,pa);
		CEdit_Cntinent.GetWindowTextW(co);
		int index = comboLang.GetCurSel(); 
		comboLang.GetLBText(index,lang);
		query1.Format(L"select codePays from pays where nomPays = '%s'",pa);
		CDaoDatabase db;
		CDaoRecordset recset(&db);
		COleVariant var;//start Variables
		var.ChangeType(VT_BSTR,NULL);
		db.Open(L"GestionActivite.mdb");
		recset.Open(AFX_DAO_USE_DEFAULT_TYPE,query1,NULL);//to retrieve the records for the recordset	
		while(!recset.IsEOF()){
			recset.GetFieldValue(L"codePays",var);
			codeP=(LPCWSTR)var.pbstrVal;
			recset.MoveNext();
		}	
		recset.Close();
		
		query2.Format(L"insert into villages values('%s','%s','%s')",codeV,vl,codeP);
		query3.Format(L"insert into parler values('%s','%s')",lang,codeV);
		try{
			if (villageExistInVillages(vl) == 1){
				if(langAssociateWVillage(vl,lang) == 1){
					AfxMessageBox(L"le village est deja exist et la langue et deja associé a lui!", MB_OK | MB_ICONWARNING);
				}
				else {
					db.Execute(query3);
					AfxMessageBox(L"Nouvelle langue est associé au village!", MB_OK | MB_ICONINFORMATION);
				}}
			else{
				db.Execute(query2);
				db.Execute(query3);
				AfxMessageBox(L"le village est ajouté avec succes!", MB_OK | MB_ICONINFORMATION);

			}
		}catch(CDaoException* e){
			
		}
		db.Close();
		CEDIT_Village.EnableWindow(FALSE);
		comboLang.ResetContent();
		CEDIT_Village.SetWindowTextW(L"");
		CEdit_Pays.SetWindowTextW(L"");
		CEdit_Cntinent.SetWindowTextW(L"");

	}
}

void Village::removeDuplicates(CComboBox& comboBox) {
    int itemCount = comboBox.GetCount();
    
    for (int i = 0; i < itemCount - 1; ++i) {
        CString currentItem;
        comboBox.GetLBText(i, currentItem);

        for (int j = i + 1; j < itemCount; ) {
            CString nextItem;
            comboBox.GetLBText(j, nextItem);

            if (currentItem.CompareNoCase(nextItem) == 0) {
                // Supprimer l'élément en double
                comboBox.DeleteString(j);
                itemCount = comboBox.GetCount(); // Met à jour le nombre d'éléments
            } else {
                ++j;
            }
        }
    }
}

void Village::OnBnClickedButton5()//delete
{

	CDaoDatabase db;
	CDaoRecordset recset(&db);
	CString vl,querySupp,queryCodeV,querySuppFromParler,querySuppFromProposer,cdeV;
	CEDIT_Village.GetWindowTextW(vl);
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
	querySuppFromProposer.Format(L"delete from proposer where codeVillage = '%s'",cdeV);
	db.Execute(querySupp);
	db.Execute(querySuppFromProposer);
	db.Execute(querySuppFromParler);
	db.Close();
}

void Village::OnCbnSelchangeComboPays()
{
	CDaoDatabase db;
	CDaoRecordset recset(&db);
	CString paysSel,queryC,queryL;
	int index = comboPays.GetCurSel();//gratuit champ 
	comboPays.GetLBText(index,paysSel);
	queryC.Format(L"select nomContinent from continents where codeContinent in (select codeContinent from pays where nomPays = '%s')",paysSel);
	COleVariant var;//start Variables
	var.ChangeType(VT_BSTR,NULL);
	db.Open(L"GestionActivite.mdb");
	recset.Open(AFX_DAO_USE_DEFAULT_TYPE,queryC,NULL);//to retrieve the records for the recordset		
	CString nmco,nmla;
	while(!recset.IsEOF()){
		recset.GetFieldValue(L"nomContinent",var);
		nmco=(LPCWSTR)var.pbstrVal;
		CEdit_Cntinent.SetWindowTextW(nmco);
		recset.MoveNext();
		}	
	recset.Close();
	db.Close();
	// TODO: Add your control notification handler code here
}

int Village::villageExistInVillages(CString& vl){
	CDaoDatabase db;
	CDaoRecordset recset(&db);
	CString query = L"select nomVillage from villages",nomV;
	COleVariant var;//start Variables
	var.ChangeType(VT_BSTR,NULL);
	db.Open(L"GestionActivite.mdb");
	recset.Open(AFX_DAO_USE_DEFAULT_TYPE,query,NULL);//to retrieve the records for the recordset
	while(!recset.IsEOF()){
		recset.GetFieldValue(L"nomVillage",var);
		nomV = (LPCWSTR)var.pbstrVal;
		if (nomV == vl) return 1;
		recset.MoveNext();
	}
	recset.Close();
	db.Close();
	return 0;
}
CString Village::returnCodeVBaseOnName(CString& vl){
	CDaoDatabase db;
	CDaoRecordset recset(&db);
	CString query,codeV;
	query.Format(L"select codeVillage from villages where nomVillage = '%s'",vl);
	COleVariant var;//start Variables
	var.ChangeType(VT_BSTR,NULL);
	db.Open(L"GestionActivite.mdb");
	recset.Open(AFX_DAO_USE_DEFAULT_TYPE,query,NULL);//to retrieve the records for the recordset
	while(!recset.IsEOF()){
		recset.GetFieldValue(L"codeVillage",var);
		codeV = (LPCWSTR)var.pbstrVal;
		recset.MoveNext();
	}
	recset.Close();
	db.Close();
	return codeV;
}
int Village::langAssociateWVillage(CString& vl, CString& lang){
	CDaoDatabase db;
	CDaoRecordset recset(&db);
	CString codeV = returnCodeVBaseOnName(vl);
	CString query = L"select nomLangue,codeVillages from parler",nmL,cdV;
	COleVariant var;//start Variables
	var.ChangeType(VT_BSTR,NULL);
	db.Open(L"GestionActivite.mdb");
	recset.Open(AFX_DAO_USE_DEFAULT_TYPE,query,NULL);//to retrieve the records for the recordset
	while(!recset.IsEOF()){
		recset.GetFieldValue(L"codeVillages",var);
		cdV = (LPCWSTR)var.pbstrVal;
		recset.GetFieldValue(L"nomLangue",var);
		nmL = (LPCWSTR)var.pbstrVal;
		if (codeV == cdV && nmL == lang) return 1;
		recset.MoveNext();
	}
	recset.Close();
	db.Close();
	return 0;
}

