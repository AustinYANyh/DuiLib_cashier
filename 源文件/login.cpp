#include "login.h"
#include "mawin.h"
#include "CashierWnd.h"
#include "mysql.h"

using namespace std;

CDuiString LoginWind::GetSkinFolder()
{
	return _T("");
}

CDuiString LoginWind::GetSkinFile()//
{
	return _T("LoginWind.xml");
}

LPCTSTR LoginWind::GetWindowClassName(void) const
{
	return _T("LoginWind");
}

void LoginWind::Notify(TNotifyUI& msg)
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
		else if (msg.pSender->GetName() == _T("btnLogin"))
		{
			LoginWind::Login();
		}
	}
}

std::string StringFromLPCTSTR(LPCTSTR str)
{
#ifdef _UNICODE
	int size_str = WideCharToMultiByte(CP_UTF8, 0, str, -1, 0, 0, NULL, NULL);

	char* point_new_array = new char[size_str];

	WideCharToMultiByte(CP_UTF8, 0, str, -1, point_new_array, size_str, NULL, NULL);

	std::string return_string(point_new_array);
	delete[] point_new_array;
	point_new_array = NULL;
	return return_string;
#else
	return std::string(str);
#endif
}

void LoginWind::Login()
{
	CEditUI* pEditUserName = (CEditUI*)m_PaintManager.FindControl(_T("edtLogin"));
	CDuiString strUsername = pEditUserName->GetText();

	CEditUI* pEditUserPasswoed = (CEditUI*)m_PaintManager.FindControl(_T("edtPassword"));
	CDuiString strUserPassword = pEditUserPasswoed->GetText();

	if (strUsername.IsEmpty())
	{
		MessageBox(m_hWnd, _T("用户名不能为空!"), _T("提示信息"), IDOK);
	}
	if (strUserPassword.IsEmpty())
	{
		MessageBox(m_hWnd, _T("密码不能为空!"), _T("提示信息"), IDOK);
	}

	ShowWindow(false);
	string username = StringFromLPCTSTR(strUsername.GetData());
	string password = StringFromLPCTSTR(strUserPassword.GetData());

	string que = "select * from employee where name = '"
		+ username + "' and password = '"
		+ password + "'";

	//m_MySQL->ConnectMysql("localhost", "root", "123123", "supmarket");
	MySQL mysql;
	mysql.ConnectMysql("localhost", "root", "123123", "supmarket");

	if (mysql.Check(que) == true)
	{

		//管理员
		string que = "select position from employee where name ='" + username + "';";

		vector<vector<string>> vRet = mysql.Select(que);

		if (vRet[0][0]=="管理员")
		{
			MainWd mainWd;

			mainWd.Create(NULL, _T("MainWind"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
			mainWd.CenterWindow();
			mainWd.ShowModal();
		}
		//收银员
		else
		{
			CashierWnd cashierWnd;

			cashierWnd.Create(NULL, _T("CashierWnd"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
			cashierWnd.CenterWindow();
			cashierWnd.ShowModal();
		}
	}
	else
	{
		MessageBox(m_hWnd, _T("用户名或密码不存在!"), _T("提示信息"), NULL);
	}
}