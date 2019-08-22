#include "CashierWnd.h"
#include <string>
#include <iostream>

CashierWnd::CashierWnd()
{
	//m_mysql->ConnectMysql("localhost", "root", "123123", "supmarket");
}


CashierWnd::~CashierWnd()
{
}

#include "mawin.h"


CDuiString CashierWnd::GetSkinFolder()
{
	return _T("");
}

CDuiString CashierWnd::GetSkinFile()
{
	return _T("CashierWnd.xml");
}

LPCTSTR CashierWnd::GetWindowClassName(void) const
{
	return _T("CashierWnd");
}

void CashierWnd::Notify(TNotifyUI& msg)
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
		else if (msg.pSender->GetName() == _T("btn_Select"))
		{
			CashierWnd::SelectGood();
		}
		else if (msg.pSender->GetName() == _T("btn_Add"))
		{
			CashierWnd::AddGoodCount();
		}
		else if (msg.pSender->GetName() == _T("btn_Sub"))
		{
			CashierWnd::SubGoodCount();
		}
		else if (msg.pSender->GetName() == _T("btn_Ok"))
		{
			CashierWnd::InsertGood();
		}
		else if (msg.pSender->GetName() == _T("btn_Yes"))
		{
			CashierWnd::Commit();
		}
		else if (msg.pSender->GetName() == _T("btn_No"))
		{
			CashierWnd::Cancel();
		}
	}
}

void CashierWnd::SelectGood()
{
	//��ȡ��Ʒ����
	CEditUI* pEDGoodname = (CEditUI*)m_PaintManager.FindControl(_T("ediGoodname"));
	CDuiString strGoodname = pEDGoodname->GetText();

	//�������ݿ�sql���
	string strSQL = "select * from goods where GoodsName='";
	strSQL += StringFromLPCTSTR(strGoodname);
	strSQL += "';";

	MySQL mysql;
	mysql.ConnectMysql("localhost", "root", "123123", "supmarket");
	vector<vector<string>> vRet = mysql.Select(strSQL);

	if (vRet.empty())
	{
		MessageBox(m_hWnd, _T("û�и���Ʒ!"), _T("��ʾ��Ϣ"), IDOK);
		return;
	}

	//��ʾ��������ؼ���
	CDuiString strGoodCount = (vRet[0][7]).c_str();
	((CEditUI*)m_PaintManager.FindControl(_T("ediGoodCount")))->SetText(strGoodCount);

	//+-���Ƶ���Ʒ�����༭������
	CEditUI* pedCount = (CEditUI*)m_PaintManager.FindControl(_T("ediCount"));
	pedCount->SetText(0);

	//�Ƿ����Ԥ��ֵ,���ھͱ���
	if (atoi(vRet[0][7].c_str()) < atoi(vRet[0][8].c_str()))
	{
		MessageBox(m_hWnd, _T("��治��,�뼰ʱ����!"), _T("��ʾ��Ϣ"), NULL);
	}
}


void CashierWnd::AddGoodCount()
{
	//����1
	CEditUI* pEDGoodCount = (CEditUI*)m_PaintManager.FindControl(_T("ediGoodCount"));
	CDuiString strGoodCount = pEDGoodCount->GetText();

	int count = 0;
	count = atoi(StringFromLPCTSTR(strGoodCount).c_str());
	--count;
	strGoodCount.Format(_T("%d"), count);
	pEDGoodCount->SetText(strGoodCount);

	//��Ʒ������1
	CEditUI* pECount = (CEditUI*)m_PaintManager.FindControl(_T("ediCount"));
	CDuiString strCount = pECount->GetText();

	count = atoi(StringFromLPCTSTR(strCount).c_str());
	++count;
	strCount.Format(_T("%d"), count);
	pECount->SetText(strCount);
}

void CashierWnd::SubGoodCount()
{
	CEditUI* pECount = (CEditUI*)m_PaintManager.FindControl(_T("ediCount"));
	CDuiString strCount = pECount->GetText();

	if (atoi(StringFromLPCTSTR(strCount).c_str()) <= 0)
	{
		MessageBox(m_hWnd, _T("�������!"), _T("��ʾ��Ϣ"), NULL);
		m_PaintManager.FindControl(_T("ediCount"))->SetText(0);
	}
	else
	{
		//����1
		CEditUI* pEDGoodCount = (CEditUI*)m_PaintManager.FindControl(_T("ediGoodCount"));
		CDuiString strGoodCount = pEDGoodCount->GetText();

		int count = 0;
		count = atoi(StringFromLPCTSTR(strGoodCount).c_str());
		++count;
		strGoodCount.Format(_T("%d"), count);
		pEDGoodCount->SetText(strGoodCount);


		//��Ʒ������1
		count = atoi(StringFromLPCTSTR(strCount).c_str());
		--count;
		strCount.Format(_T("%d"), count);
		pECount->SetText(strCount);
	}
}

void CashierWnd::InsertGood()
{
	//��ȡ���Ƽ���Ʒ����
	CEditUI* pEDGoodname = (CEditUI*)m_PaintManager.FindControl(_T("ediGoodname"));
	CDuiString strGoodname = pEDGoodname->GetText();

	CEditUI* pECount = (CEditUI*)m_PaintManager.FindControl(_T("ediCount"));
	CDuiString strCount = pECount->GetText();

	//��ȡ�۸�ͼ�����λ
	string strSQL = "select Price,Unit from goods where GoodsName='";
	strSQL += StringFromLPCTSTR(strGoodname);
	strSQL += "';";

	MySQL mysql;
	mysql.ConnectMysql("localhost", "root", "123123", "supmarket");
	vector<vector<string>> vRet = mysql.Select(strSQL);

	//ͳ�Ƽ۸�
	//atofת��Ϊdouble����
	int count = atoi(StringFromLPCTSTR(strCount).c_str());

	//�ַ��������ݱ������ansicII
	double price = atof((vRet[0][0]).c_str());

	price = count*price;
	CDuiString strPrice;
	strPrice.Format(_T("%lf"), price);

	//���С�ڵ�ǰ��Ʒ����,����ʧ��
	CEditUI* pEDGoodCount = (CEditUI*)m_PaintManager.FindControl(_T("ediGoodCount"));
	CDuiString strGoodCount = pEDGoodCount->GetText();

	if (atoi(StringFromLPCTSTR(strCount).c_str()) > atoi(StringFromLPCTSTR(strGoodCount).c_str()))
	{
		MessageBox(m_hWnd, _T("��治��,����ʧ��!"), _T("��ʾ��Ϣ"), NULL);
		pECount->SetText(0);
	}
	else
	{

		//���µ�list��
		CListTextElementUI* pItem = new CListTextElementUI;
		CListUI* pList = (CListUI*)m_PaintManager.FindControl(_T("ListGoodInfo"));

		pList->Add(pItem);
		pItem->SetText(0, strGoodname);
		pItem->SetText(1, vRet[0][0].c_str());
		pItem->SetText(2, strCount);
		pItem->SetText(3, (vRet[0][1]).c_str());
		pItem->SetText(4, strPrice);

		//��ձ༭��
		m_PaintManager.FindControl(_T("ediGoodname"))->SetText("");
		m_PaintManager.FindControl(_T("ediGoodCount"))->SetText("");
		m_PaintManager.FindControl(_T("ediCount"))->SetText(0);
	}
}

void CashierWnd::Commit()
{
	//ͳ���ܼ�
	double TotalPrice = 0;

	CListUI* pList = (CListUI*)m_PaintManager.FindControl(_T("ListGoodInfo"));
	int lineno = pList->GetCount();

	CDuiString strPrice;

	for (size_t i = 0; i < lineno; ++i)
	{
		CListTextElementUI* pItem = (CListTextElementUI*)pList->GetItemAt(i);
		strPrice = pItem->GetText(4);
		TotalPrice += atof(StringFromLPCTSTR(strPrice).c_str());
	}

	strPrice.Format(_T("%.02lf"), TotalPrice);
	m_PaintManager.FindControl(_T("ediTotal"))->SetText(strPrice);

	//�������ݿ�
	for (size_t i = 0; i < lineno; ++i)
	{
		CListTextElementUI* pItem = (CListTextElementUI*)pList->GetItemAt(i);
		CDuiString strCount = pItem->GetText(2);
		CDuiString strGoodName = pItem->GetText(0);

		//��ѯԭ�ȿ��
		string strSQL = "select Inventory from goods where GoodsName='";
		strSQL += StringFromLPCTSTR(strGoodName);
		strSQL += "';";

		MySQL mysql;
		mysql.ConnectMysql("localhost", "root", "123123", "supmarket");

		vector<vector<string>> vRet = mysql.Select(strSQL);
		string Inventory = vRet[0][0];
		
		//���¿��
		int inventory = atoi(Inventory.c_str()) - atoi((StringFromLPCTSTR(strCount).c_str()));
		Inventory = to_string(inventory);
		string strupSQL = "update goods set Inventory='";
		strupSQL += Inventory;
		strupSQL += "' where GoodsName='"; 
		strupSQL += StringFromLPCTSTR(strGoodName);
		strupSQL += "';";


		mysql.Update(strupSQL);
	}

	pList->RemoveAll();

	//���뱾�ε����ۼ�¼
}

void CashierWnd::Cancel()
{
	//���list������Ʒ
	CListTextElementUI* pItem = new CListTextElementUI;
	CListUI* pList = (CListUI*)m_PaintManager.FindControl(_T("ListGoodInfo"));

	pList->RemoveAll();
}