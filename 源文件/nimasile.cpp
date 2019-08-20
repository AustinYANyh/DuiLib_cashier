#include "commo.h"
#include "mawin.h"
#include "login.h"

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	//CPaintManagerUI::SetInstance(hInstance);

	//MainWd duiFrame;

	//duiFrame.Create(NULL, _T("DUIMainFrame"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);

	//duiFrame.ShowModal();


	CPaintManagerUI::SetInstance(hInstance);

	LoginWind loginWind;

	loginWind.Create(NULL, _T("LoginWind"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);

	loginWind.CenterWindow();

	loginWind.ShowModal();


	return 0;
}