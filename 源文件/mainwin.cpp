#define _CRT_SECURE_NO_WARNINGS

#include "commo.h"
#include "mawin.h"
#include "mysql.h"


CDuiString MainWd::GetSkinFolder()
{
	return _T("");
}

CDuiString MainWd::GetSkinFile()
{
	return _T("tese.xml");
}

LPCTSTR MainWd::GetWindowClassName(void) const
{
	return _T("tese");
}

void MainWd::Notify(TNotifyUI& msg)
{
	if (msg.sType == _T("click"))
	{
		if (msg.pSender->GetName() == _T("btnClose"))
		{
			Close();
		}
		else if (msg.pSender->GetName() == _T("btnMin"))
		{
			::SendMessage(m_hWnd, WM_SYSCOMMAND, SC_MINIMIZE, 0);
		}
		else if (msg.pSender->GetName() == _T("btnSELECT"))
		{
			MainWd::SelectEmployee();
		}
		else if (msg.pSender->GetName() == _T("btnINSERT"))
		{
			MainWd::InsertEmployee();
		}
		else if (msg.pSender->GetName() == _T("btnDELETE"))
		{
			MainWd::DeleteEmployee();
		}
	}
	else if (msg.sType == _T("itemselect"))
	{
		if (msg.pSender->GetName() == _T("optEmployee"))
		{

		}
		else if (msg.pSender->GetName() == _T("optGood"))
		{

		}
	}
}


void MainWd::SelectEmployee()
{
	string strSQL = "select * from employee";

	CComboBoxUI* pCombo = (CComboBoxUI*)m_PaintManager.FindControl(_T("comPosition"));
	CDuiString strStyle = pCombo->GetText();

	if (strStyle == _T("��"))
	{
		strSQL += ";";
	}
	else if (strStyle == _T("����"))
	{
		strSQL += " where name='";
		CDuiString strName = ((CEditUI*)m_PaintManager.FindControl(_T("username")))->GetText();

		if (strName.IsEmpty() == true)
		{
			MessageBox(m_hWnd, _T("���������ѯ�û�������!"), _T("��ʾ��Ϣ"), NULL);
			return;
		}

		strSQL += StringFromLPCTSTR(strName);
		strSQL += "';";
	}
	else if (strStyle == _T("�Ա�"))
	{
		strSQL += " where gender='";
		CDuiString strGender = ((CComboBoxUI*)m_PaintManager.FindControl(_T("comboGender")))->GetText();

		if (strGender.IsEmpty() == true)
		{
			MessageBox(m_hWnd, _T("���������ѯ�û����Ա�!"), _T("��ʾ��Ϣ"), NULL);
			return;
		}

		strSQL += StringFromLPCTSTR(strGender);
		strSQL += "';";
	}
	else if (strStyle == _T("н��"))
	{
		strSQL += " where salary='";
		CDuiString strSal = ((CEditUI*)m_PaintManager.FindControl(_T("usersal")))->GetText();

		if (strSal.IsEmpty() == true)
		{
			MessageBox(m_hWnd, _T("���������ѯ�û���н��!"), _T("��ʾ��Ϣ"), NULL);
			return;
		}

		strSQL += StringFromLPCTSTR(strSal);
		strSQL += "';";
	}

	MySQL mysql;
	mysql.ConnectMysql("localhost", "root", "123123", "supmarket");

	vector<vector<string>> vRet = mysql.Select(strSQL);

	if (vRet.empty())
	{
		return;
	}

	CListUI* pListUI = (CListUI*)m_PaintManager.FindControl(_T("ListEmployeeInfo"));
	pListUI->RemoveAll();

	for (size_t i = 0; i < vRet.size(); ++i)
	{
		vector<string>& strItem = vRet[i];
		CListTextElementUI* pData = new CListTextElementUI;

		pData->SetAttribute(_T("align"), _T("center"));

		pListUI->Add(pData);

		//��Ҫ����PLCSTR���͵�
		pData->SetText(0, strItem[1].c_str());
		pData->SetText(1, strItem[2].c_str());
		pData->SetText(2, strItem[3].c_str());
		pData->SetText(3, strItem[5].c_str());
		pData->SetText(4, strItem[6].c_str());
		pData->SetText(5, strItem[7].c_str());
	}
}

void MainWd::InsertEmployee()
{
	//�ӽ����л�ȡԱ������Ϣ
	CDuiString strName=((CEditUI*)m_PaintManager.FindControl(_T("username")))->GetText();
	CDuiString strGender = ((CComboBoxUI*)m_PaintManager.FindControl(_T("comboGender")))->GetText();
	CDuiString strBirthday = ((CEditUI*)m_PaintManager.FindControl(_T("userbirthday")))->GetText();
	CDuiString strPosition = ((CComboBoxUI*)m_PaintManager.FindControl(_T("comboPosition")))->GetText();
	CDuiString strTel = ((CEditUI*)m_PaintManager.FindControl(_T("usertel")))->GetText();
	CDuiString strSal = ((CEditUI*)m_PaintManager.FindControl(_T("usersal")))->GetText();

	CListUI* pListUI = (CListUI*)m_PaintManager.FindControl(_T("ListEmployeeInfo"));
	char sz_count[32] = { 0 };
	_itoa(pListUI->GetCount() + 1, sz_count, 10);
	
	string strSQL = "insert into employee values(";
	strSQL += sz_count;
	strSQL += ",'";
	strSQL += StringFromLPCTSTR(strName);
	strSQL += "','";
	strSQL += StringFromLPCTSTR(strGender);
	strSQL += "','";
	strSQL += StringFromLPCTSTR(strBirthday);
	//��ʼ����123
	strSQL += "','123";
	strSQL += "','";
	strSQL += StringFromLPCTSTR(strPosition);
	strSQL += "','"; 
	strSQL += StringFromLPCTSTR(strTel);
	strSQL += "','";
	strSQL += StringFromLPCTSTR(strSal);
	strSQL += "');";

	//ÿ�ζ�Ҫ��������,��̫����
	MySQL mysql;
	mysql.ConnectMysql("localhost", "root", "123123", "supmarket");
	mysql.Insert(strSQL);

	//��Ա����Ϣ���뵽list��
	CListTextElementUI* pItem = new CListTextElementUI;
	pListUI->Add(pItem);
	pItem->SetText(0, strName);
	pItem->SetText(1, strGender);
	pItem->SetText(2, strBirthday);
	pItem->SetText(3, strPosition);
	pItem->SetText(4, strTel);
	pItem->SetText(5, strSal);

}

void MainWd::DeleteEmployee()
{
	//��ȡ��ǰѡ��
	CListUI* pListUI = (CListUI*)m_PaintManager.FindControl(_T("ListEmployeeInfo"));

	int lineno = pListUI->GetCurSel();
	CListTextElementUI* pRow = (CListTextElementUI*)pListUI->GetItemAt(lineno);

	//�����ݿ�ɾ��Ա����Ϣ
	CDuiString strName = pRow->GetText(0);

	string strSQL = "delete from employee where name='";
	strSQL += StringFromLPCTSTR(strName.GetData());
	strSQL += "';";

	MySQL mysql;
	mysql.ConnectMysql("localhost", "root", "123123", "supmarket");
	mysql.Delete(strSQL);

	//��list�а���Ϣ�Ƴ�
	pListUI->RemoveAt(lineno);
}
