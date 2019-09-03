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
			//Close();
			PostQuitMessage(0);
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
	else if (msg.sType == _T("selectchanged"))
	{
#if 0
		CDuiString    strName = msg.pSender->GetName();
		CTabLayoutUI* pControl = static_cast<CTabLayoutUI*>(m_PaintManager.FindControl(_T("tabTest")));

		if (strName == _T("optEmployee"))
		{
			pControl->SelectItem(0);
		}
		else if (strName == _T("optGood"))
		{
			pControl->SelectItem(1);
		}
#endif
	}

	__super::Notify(msg);
}



void MainWd::SelectEmployee()
{
	string strSQL = "select * from employee";

	CComboBoxUI* pCombo = (CComboBoxUI*)m_PaintManager.FindControl(_T("comPosition"));
	CDuiString strStyle = pCombo->GetText();

	if (strStyle == _T("无"))
	{
		strSQL += ";";
	}
	else if (strStyle == _T("姓名"))
	{
		strSQL += " where name='";
		CDuiString strName = ((CEditUI*)m_PaintManager.FindControl(_T("username")))->GetText();

		if (strName.IsEmpty() == true)
		{
			MessageBox(m_hWnd, _T("请输入待查询用户的姓名!"), _T("提示信息"), NULL);
			return;
		}

		strSQL += StringFromLPCTSTR(strName);
		strSQL += "';";
	}
	else if (strStyle == _T("性别"))
	{
		strSQL += " where gender='";
		CDuiString strGender = ((CComboBoxUI*)m_PaintManager.FindControl(_T("comboGender")))->GetText();

		if (strGender.IsEmpty() == true)
		{
			MessageBox(m_hWnd, _T("请输入待查询用户的性别!"), _T("提示信息"), NULL);
			return;
		}

		strSQL += StringFromLPCTSTR(strGender);
		strSQL += "';";
	}
	else if (strStyle == _T("薪资"))
	{
		strSQL += " where salary='";
		CDuiString strSal = ((CEditUI*)m_PaintManager.FindControl(_T("usersal")))->GetText();

		if (strSal.IsEmpty() == true)
		{
			MessageBox(m_hWnd, _T("请输入待查询用户的薪资!"), _T("提示信息"), NULL);
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

		//需要的是PLCSTR类型的
		pData->SetText(0, strItem[1].c_str());
		pData->SetText(1, strItem[2].c_str());
		pData->SetText(2, strItem[3].c_str());
		pData->SetText(3, strItem[5].c_str());
		pData->SetText(4, strItem[6].c_str());
		pData->SetText(5, strItem[7].c_str());
	}

	//查询结束后,清空所有编辑框
	m_PaintManager.FindControl(_T("username"))->SetText("");
	m_PaintManager.FindControl(_T("userbirthday"))->SetText("");
	m_PaintManager.FindControl(_T("usertel"))->SetText("");
	m_PaintManager.FindControl(_T("usersal"))->SetText("");
}

void MainWd::InsertEmployee()
{
	//从界面中获取员工的信息
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
	//初始密码123
	strSQL += "','123";
	strSQL += "','";
	strSQL += StringFromLPCTSTR(strPosition);
	strSQL += "','"; 
	strSQL += StringFromLPCTSTR(strTel);
	strSQL += "','";
	strSQL += StringFromLPCTSTR(strSal);
	strSQL += "');";

	//每次都要重新连接,不太合适
	MySQL mysql;
	mysql.ConnectMysql("localhost", "root", "123123", "supmarket");
	mysql.Insert(strSQL);

	//将员工信息插入到list中
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
	//获取当前选中
	CListUI* pListUI = (CListUI*)m_PaintManager.FindControl(_T("ListEmployeeInfo"));

	int lineno = pListUI->GetCurSel();
	CListTextElementUI* pRow = (CListTextElementUI*)pListUI->GetItemAt(lineno);

	//从数据库删除员工信息
	CDuiString strName = pRow->GetText(0);

	string strSQL = "delete from employee where name='";
	strSQL += StringFromLPCTSTR(strName.GetData());
	strSQL += "';";

	MySQL mysql;
	mysql.ConnectMysql("localhost", "root", "123123", "supmarket");
	mysql.Delete(strSQL);

	//从list中把信息移除
	pListUI->RemoveAt(lineno);
}
